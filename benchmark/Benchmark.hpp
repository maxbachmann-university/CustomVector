/** @file */
//Includes
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <math.h>
#include <vector>
#ifndef BENCHMARK_H
#define BENCHMARK_H

/**
 * @brief       Class for Testing the time, needed for operating.
 * @details     This class measures the runtime of any function and pushes it to m_data.
 *              It writes the result(minimal, maximal,mean and standard deviation) in a .csv file.
 * @author      Maximilian Bachmann <bachmann.maxim-tfe17@it.dhbw-ravensburg.de>
 * @author      Felix Bandle <bandle.felix-tfe17@it.dhbw-ravensburg.de>
 * @author      Florian Vetter <vetter.florian-tfe17@it.dhbw-ravensburg.de>
 * @version     1.0
 * @since       1.2 
 */
class Benchmark {


private:

std::vector<double> m_data;  //!< Vector for saving the runtimes.
std::ofstream m_output;   //!< Output stream for the output file.
std::chrono::steady_clock::time_point m_start;   //!< Variable for the start time.

double Max();
double Min();
double Mean();
double Deviation();
void saveData(std::string dataname);

public:

void Start();
void Stop();
void calculate(std::string dataname);
Benchmark(std::string filename);
~Benchmark();
void epsPlot(std::vector<std::string> filenames, std::string filename);

};
#endif //BENCHMARK_H