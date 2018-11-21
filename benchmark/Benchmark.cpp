/** @file */
//Includes
#include "Benchmark.hpp"
#include "gnuplot.h"
#include <sstream>


/**
 * Constructor of Benchmark.
 * <p>
 * Constructor defines the output stream and initializes the start variable.
 * </p>
 *
 */
Benchmark::Benchmark(const std::string& filename)
{
    m_output = std::ofstream(filename + ".csv");
    m_output << "\"identifier\";\"max time\";\"min time\";\"mean time\";\"standard deviation\"\n";
	m_start = std::chrono::steady_clock::now();
}

/**
 * Destructor of Benchmark.
 * 
 */
Benchmark::~Benchmark() {};

/**
 * Method for taking the start time.
 * 
 */
void Benchmark::Start()
{
    m_start = std::chrono::steady_clock::now();
}

/**
 * Method for taking the stop time in nanoseconds and push it to m_data.
 * 
 */
void Benchmark::Stop()
{
    std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - m_start;
	double nanoseconds = static_cast<double>(time.count()) 
	    * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
    m_data.push_back(nanoseconds);
}

/**
 * Returns the maximum of m_data.
 *
 * @return   double max      maximal value for calculating.
 */
double Benchmark::Max() const
{
	double max = m_data[0];
	for (double const& value : m_data){
		if (value > max){
			max = value;
		}
	}
	return max;
}

/**
 * Returns the minimum of m_data.
 *
 * @return   double min      minimal value for calculating.
 */
double Benchmark::Min() const
{
	double min = m_data[0];
	for (double const& value : m_data){
		if (value < min){
			min = value;
		}
	}
	return min;
}

/**
 * Returns the mean of m_data.
 *
 * @return   double mean      mean value for calculating.
 */
double Benchmark::Mean() const
{
	double mean = m_data[0];
	for (double const& value : m_data){
		mean += value;
	}
	mean /= m_data.size();
	return mean;
}

/**
 * Returns the standard deviation of m_data.
 *
 * @return   double deviation      standard deviation for calculating.
 */
double Benchmark::Deviation() const
{
    double mean = Mean();
    double deviation = 0;
	for (double const& value : m_data){
		deviation += pow(value-mean, 2);
	}
	deviation /= m_data.size();
	return deviation;
}

/**
 * Method for calculating a summary.
 * <p>
 * This Method creates a summary in a .csv file for all values.
 * </p>
 *
 * @param   std::string  Identifier for the data.
 */
void Benchmark::calculate(const std::string& dataname)
{
	saveData(dataname);

	if (!m_output.is_open()){
		std::cerr << "Can't open Benchmark_Output.csv!"
			<< std::endl;
	}else{
        //*****************************************************
        //write data to file Benchmark_Output.csv
		
        m_output << "\""
				<< dataname << "\";\""
                << Max() << "\";\""
                << Min() << "\";\""
                << Mean() << "\";\""
                << Deviation() << "\"\n";

        //*****************************************************
        m_data.clear();
	}
}

/**
 * Method for saving all the times for a graph
 * <p>
 * This Method creates a .dat file that includes all measured values
 * </p>
 *
 * @param   std::string  Identifier for the data.
 */
void Benchmark::saveData(const std::string& dataname) const{
	auto output = std::ofstream("data/" + dataname + ".dat");
	if (!output.is_open()){
		std::cerr << "can't open data/" << dataname << ".dat" << std::endl;
	}else{
        for (size_t i = 0; i< m_data.size();++i){
			output << i << " " << m_data[i] << "\n";
		}
	}
}

/**
 * Method for creating a svg plot of the .dat files
 * <p>
 * uses the gunplot.hpp library to create a svg plot
 * </p>
 *
 * @param   std::string  filename.
 * @param   std::vector<std::string>  filenames of .dat files.
 */
void Benchmark::epsPlot(const std::vector<std::string>& filenames, const std::string& filename) const{
	bool GnuPlot = true;
	gnuplot p(GnuPlot);
	if (GnuPlot){
		p("set terminal eps noenhanced");
		p("set output \"images/"+ filename + ".eps \" ");
		p("set key title \"curves\" center");
		p("set key left top vertical Left reverse enhanced autotitle nobox");
		p("set key noinvert samplen 1 spacing 1 width 0 height 0 ");
		p("set style increment default");
		p("set style data lines");
		p("set title \"Transparent filled curves\" ");
		std::string plot = "plot ";
		if (filenames.size()){
			for (size_t i = 0; i<(filenames.size()-1); ++i){
				plot += "'./data/" + filenames[i] + ".dat' using 1:2 title \"" + filenames[i] + "\", ";
			}
			plot += "'./data/" + filenames.back() + ".dat' using 1:2 title \"" + filenames.back();
		}
		p(plot);
	}
}