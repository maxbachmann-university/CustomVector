#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <iostream>
#include <string>

class gnuplot{
public:
    gnuplot(bool& error);
    ~gnuplot();
    void operator () (const std::string& command);
protected:
    FILE *gnuplotpipe;
};

gnuplot::gnuplot(bool& error){
    gnuplotpipe = popen("gnuplot -persist","w");
    if (!gnuplotpipe){
        error = false;
    }
}
gnuplot::~gnuplot(){
    fprintf(gnuplotpipe, "exit \n");
    pclose(gnuplotpipe);
}
void gnuplot::operator()(const std::string& command){
    fprintf(gnuplotpipe, "%s\n", command.c_str());
    fflush(gnuplotpipe);
}


#endif //GNUPLOT_H