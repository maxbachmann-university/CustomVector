/** @file */
#include <iostream>
#include <vector>
#include "vector/Vector.hpp"
#include "benchmark/Benchmark.hpp"
#include <string>


/**
 * @brief       Main for checking the runtime of Std, own and slow own vector.
 * @details     With for loops several methods are executed and the runtime is measured with the Benchmark class.
 * @author      Maximilian Bachmann <bachmann.maxim-tfe17@it.dhbw-ravensburg.de>
 * @author      Felix Bandle <bandle.felix-tfe17@it.dhbw-ravensburg.de>
 * @author      Florian Vetter <vetter.florian-tfe17@it.dhbw-ravensburg.de>
 * @version     1.0
 * @since       1.2
 */

int main()
{
    int value = 100;
    Benchmark benchmark("Benchmark_Output");
    std::vector<std::string> PushBack;
    std::vector<std::string> PopBack;
    std::vector<std::string> Operator;
    std::vector<std::string> PushBackCustom;
    std::vector<std::string> PopBackCustom;
    std::vector<std::string> OperatorCustom;

    //************************************************
    //Test own vector class
    //push_back()
   for(int i = 0; i < 100; ++i){
        Vector<int> vector;
        benchmark.Start();
        for(size_t m = 0; m < 1'000'000; ++m){
            vector.push_back(value);
        }
        benchmark.Stop();
    }
    benchmark.calculate("push_back");
    PushBack.push_back("push_back");
    PushBackCustom.push_back("push_back");


    //pop_back()
    for(int i = 0; i < 100; ++i){
        Vector<int> vector(1'000'000);
        benchmark.Start();
        for(size_t m = 0; m < 1'000'000; ++m){
            vector.pop_back();
        }
        benchmark.Stop();
    }
    benchmark.calculate("pop_back");
    PopBack.push_back("pop_back");
    PopBackCustom.push_back("pop_back");

    //Operator
    
    for(int i = 0; i < 100; ++i){
        Vector<int> vector(1); 
        benchmark.Start();
        for(size_t m = 0; m < 1'000'000; ++m){
            vector[1] = value;
        }
        benchmark.Stop();
    }
    benchmark.calculate("operator");
    Operator.push_back("operator");
    OperatorCustom.push_back("operator");

    //************************************************



    //************************************************
    //Test own vector class with slow methods
    //push_back_slow()
    for(int i = 0; i < 100; ++i){
        int value = 100;
        Vector<int> vector;
        benchmark.Start();
        for(size_t m = 0; m < 10'000; ++m){
            vector.push_back_slow(value);
        }
        benchmark.Stop();
    }
    benchmark.calculate("push_back_slow");
    PushBackCustom.push_back("push_back_slow");

    //pop_back_slow()
    for(int i = 0; i < 100; ++i){
        Vector<int> vector(10'000);
        benchmark.Start();
        for(size_t m = 0; m < 10'000; ++m){
            vector.pop_back_slow();
        }
        benchmark.Stop();
    }
    benchmark.calculate("pop_back_slow");
    PopBackCustom.push_back("pop_back_slow");

    //Operator
    for(int i = 0; i < 100; ++i){
        Vector<int> vector(1); 
        benchmark.Start();
        for(size_t m = 0; m < 1'000'000; ++m){
            vector[1] = value;
        }
        benchmark.Stop();
    }
    benchmark.calculate("operator_slow");
    OperatorCustom.push_back("operator_slow");

    //************************************************


    //************************************************
    //Test Std vector class

    //push_back()
   for(int i = 0; i < 100; ++i){
        std::vector<int> vector;
        benchmark.Start();
        for(size_t m = 0; m < 1'000'000; ++m){
            vector.push_back(value);
        }
        benchmark.Stop();
    }
    benchmark.calculate("std_push_back");
    PushBack.push_back("std_push_back");

    //pop_back()
    for(int i = 0; i < 100; ++i){
        std::vector<int> vector(1'000'000);
        benchmark.Start();
        for(size_t m = 0; m < 1'000'000; ++m){
            vector.pop_back();
        }
        benchmark.Stop();
    }
    benchmark.calculate("std_pop_back");
    PopBack.push_back("std_pop_back");

    //Operator
    
    for(int i = 0; i < 100; ++i){
        std::vector<int> vector(1); 
        benchmark.Start();
        for(size_t m = 0; m < 1'000'000; ++m){
            vector[1] = value;
        }
        benchmark.Stop();
    }
    benchmark.calculate("std_operator");
    Operator.push_back("std_operator");

    //************************************************

    benchmark.epsPlot(PushBack, "PushBack");
    benchmark.epsPlot(PopBack, "PopBack");
    benchmark.epsPlot(Operator, "Operator");
    benchmark.epsPlot(PushBackCustom, "PushBackCustom");
    benchmark.epsPlot(PopBackCustom, "PopBackCustom");
    benchmark.epsPlot(OperatorCustom, "OperatorCustom");

	return 0;
}