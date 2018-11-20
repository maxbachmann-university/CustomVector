/** @file */
/*! \mainpage TFE17-2 Test
 *
 * \section Introduction
 *
 * This Project is part of a series by Christian Ege in the informatics lesson of the DHBW Ravensburg Campus Friedrichshafen.
 * The tasks are worked out together in a team up to 3 People. In this Case Felix Bandle, Maximilian Bachmann and Florian Vetter worked together for the solution.
 * The deadline for the project is set on the 30. october 2018.
 *
 * \section Vector
 *
 * The class Vector provides the ability of soraging different items in a vector. So you have a list where you can push data of different types to the end or pop them up.
 * It's also possible to get and change the size or copie a vector. Data can be called up from a specific position in the vector and all of it's items can be cleared.
 *
 * \section Benchmark
 * 
 * The class Benchmark is used for measuring the runtime of any code. It also calculates the minimal, maximal and mean runtime and the standard deviation.
 * Afterwards all values are written to a .csv file.
 * 
 * For pop_back and push_back the slow Push/pop back function is a lot slower than the stl::vector and the custom vectors intelligent functions.
 * The reason is that both the stl:: vector and the intelligent custom vector do not just increase/lower the size of the array to the size that
 * is currently needed, but increase it by a lot more. This has the advantage that the vector does not has to be copied for each push_back/pop_back 
 * which makes the a lot faster. On the other hand the std::vector and the custom intelligent vector have a bigger heap usage.
 * The [] operator has the same implementation for the custom intelligent vector and the custom slow vector and so they have the same speed.
 * 
 * According to the current plot the custom vector's [] operator is appears to be slightly faster than the one used by the std::vector. 
 * However running the benchmark multiple times it often changes which one is faster and so they should be around as fast. The custom vectors 
 * pus_back and pop_back methods however are constantly faster than the same functions of the std::vector. Possibly the std::vector does not increase the capacity
 * as much as the custom vector or has a few more tasks to make it safer to use.
 * 
 * The plots of the results can be found in images/.
 * 
 * 
 * 
 * \section Catch2
 * 
 * This header file is used for testing our code.
 * 
 * Catch2 stands for C++ Automated Test Cases in a Header and is a multi-paradigm test framework for C++. 
 * which also supports Objective-C (and maybe C). 
 * It is primarily distributed as a single header file, although certain extensions may require additional headers.
 * 
 * Source: https://github.com/catchorg/Catch2
 *  
 */

 //Includes
#include"vector/Vector.hpp"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"


/**
 * @brief       Vector.cpp contains the code for testing all fuctions.
   @details     With this .cpp file the class Vector is tested by a scenario with the included catch2.hpp.  
   @author      Felix Bandle <bandle.felix@it.dhbw-ravensburg.de>
   @author      Maximilian Bachmann <bachmann.maxim-tfe17@it.dhbw-ravensburg.de>
   @author      Florian Vetter <vetter.florian-tfe17@it.dhbw-ravensburg.de>
 * @version     1.2                 (current version number of program)
 * @since       1.1          (the version of the package this class was first added to)
 */


SCENARIO( "assignment", "[vector]" ) {
    GIVEN("A vector with some items"){
        Vector<int> v (5);
        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() == 10 );
        
        WHEN("the copy constructor is called") {
            Vector<int> v2 (v);
            THEN( "They are the same but not in the same position" ) {
                for (size_t i=0;i < v.size();++i){
                  REQUIRE( v[i] == v2[i] );
                }
                REQUIRE(v.size() == v2.size());
                REQUIRE(v.capacity() == v2.capacity());
                REQUIRE(v.begin() != v2.begin());
            }
        }
        WHEN("the assignmen operator is called"){
            Vector<int> v2;
            v2 = v;
            THEN( "They are the same but not in the same position" ) {
                for (size_t i=0;i < v.size();++i){
                  REQUIRE( v[i] == v2[i] );
                }
                REQUIRE(v.size() == v2.size());
                REQUIRE(v.capacity() == v2.capacity());
                REQUIRE(v.begin() != v2.begin());
            }

        }
    }
}

SCENARIO( "items can be added/removed", "[vector]" ) {

    GIVEN( "A vector with some items" ) {
        Vector<int> v (5);
        
        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
        
        WHEN( "one value is pushed_back" ) {
            v.push_back(10);
            
            THEN( "the size and capacity change" ) {
                REQUIRE( v.size() == 6 );
                REQUIRE( v.capacity() >= 10 );
				REQUIRE( v[5] == 10 );
            }
        }
        WHEN( "values can be directly inserted" ) {
            v[5] = 3;
            
            THEN( "the size changes but not capacity" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() >= 10 );
				REQUIRE( v[5] == 3 );
            }
        }
        WHEN( "values can be accessed with []" ) {
            int x = v[0];
            
            THEN( "the variable is v[0]" ) {
				REQUIRE( x == 0 );
            }
        }
        WHEN( "one pop_back" ) {
            v.pop_back();
            
            THEN( "size changed capacity stayed the same since capacity < 4*size" ) {
                REQUIRE( v.size() == 4 );
                REQUIRE( v.capacity() == 10 );
            }
        }
		WHEN( "pop_back until capacity gets reduced" ) {
            for (size_t i = v.capacity(); i < (v.size() * 4 -1) ; --i ){
                v.pop_back();
            }
            THEN( "capacity changed since capacity >= 4*size" ) {
				REQUIRE( v.size() == 2 );
                REQUIRE( v.capacity() == 5 );
            }
        }

        WHEN( "pop_back empty vector" ) {
            v.resize(0);
            v.pop_back();
            THEN( "size stays the same" ) {
				REQUIRE( v.size() == 0 );
            }
        }

        WHEN( "at in size" ) {
            auto test = v.at( 0 );
            
            THEN( "value is 0 by default" ) {
                REQUIRE( test == 0 );
            }
        }

		WHEN( "at out of range" ) {
            REQUIRE_THROWS_AS(v.at( 5 ),std::out_of_range);
        }

		WHEN( "vector gets cleared" ) {
			v.clear();
            THEN( "exception gets thrown" ) {
                REQUIRE( v.size() == 0);
				REQUIRE( v.capacity() == 10);
            }
        }
    }
}

SCENARIO( "vectors can be sized and resized", "[vector]" ) {

    GIVEN( "A vector with some items" ) {
        Vector<int> v (5);
        
        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
		REQUIRE( v[4] == 0 );
        
        WHEN( "the size is increased" ) {
            v.resize( 10 );
            
            THEN( "the size and capacity change" ) {
                REQUIRE( v.size() == 10 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
        WHEN( "the size is reduced" ) {
            v.resize( 0 );
            
            THEN( "the size changes but not capacity" ) {
                REQUIRE( v.size() == 0 );
                REQUIRE( v.capacity() >= 5 );
            }
        }
        WHEN( "more capacity is reserved" ) {
            v.reserve( 10 );
            
            THEN( "the capacity changes but not the size" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
        WHEN( "less capacity is reserved" ) {
            v.reserve( 0 );
            
            THEN( "neither size nor capacity are changed" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() >= 5 );
            }
        }
		 WHEN( "shrink capacity to size" ) {
            v.shrink_to_fit();
            
            THEN( "capacity changed to size" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() == 5 );
            }
        }
	
    }
}

SCENARIO( "items can be added/removed slow", "[vector]" ) {

    GIVEN( "A vector with some items" ) {
        Vector<int> v (5);
            
        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
            
        WHEN( "one value is pushed_back_slow" ) {
            v.push_back_slow(10);
                
            THEN( "the size and capacity change" ) {
                REQUIRE( v.size() == 6 );
                REQUIRE( v.capacity() == 6 );
                REQUIRE( v[5] == 10 );
            }
        }

        WHEN( "one pop_back" ) {
            v.pop_back_slow();
                
            THEN( "size changed capacity stayed the same since capacity < 4*size" ) {
                REQUIRE( v.size() == 4 );
                REQUIRE( v.capacity() == 4 );
            }
        }

        WHEN( "pop_back vector size 1" ) {
            v.resize(1);
            v.pop_back_slow();
            THEN( "capacity stays the same" ) {
				REQUIRE( v.size() == 0 );
                REQUIRE( v.capacity() == 1 );
            }
        }

        WHEN( "pop_back empty vector" ) {
            v.resize(0);
            v.pop_back_slow();
            THEN( "size stays the same" ) {
				REQUIRE( v.size() == 0 );
                REQUIRE( v.capacity() == 1 );
            }
        }
    }
}