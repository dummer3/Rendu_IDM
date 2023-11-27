/*************************************************/ 
/*          PI SIMULATION WITH THREADS           */ 
/*************************************************/

#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <future>
#include <chrono>
#include "CLHEP/Random/MTwistEngine.h"

// Type definition for syntax lisibility
using chrono_time = std::chrono::time_point<std::chrono::high_resolution_clock>;
using chrono_duration = std::chrono::duration<long>;

// Operator to concatanate a string and a number
std::string operator+(const std::string& string_in, const int& number_in)
{
    std::ostringstream ss ;
    ss << string_in << number_in;
    return ss.str();
}

double pi(int nbrExperiment_in, std::string status_in)
{
    // Create the Random Number Generator (here, Mercene Twister)
    CLHEP::MTwistEngine * mtRng = new CLHEP::MTwistEngine();
    mtRng->restoreStatus(status_in.c_str()); 
    double x,y;
    int total = 0;
    for(int i = 0;i<nbrExperiment_in; i++)
    {
        x= mtRng->flat();
        y= mtRng->flat();

        // if the point in inside the quarter circle
        if(x*x+y*y <= 1)
            total++;
    }

    //Free the space we allowed for the generator
    delete mtRng;
    return total*4.0/nbrExperiment_in;
}


int main()
{
  
    std::future<double> futures[10];
    double piEstimation = 0; 

    chrono_time start = std::chrono::high_resolution_clock::now();
    
    //Repeat the experiment 10 times
    for(int status_nbr=0; status_nbr<10; status_nbr++)
        futures[status_nbr] = std::async(std::launch::async,pi,1000000000,operator+("./status/status_",status_nbr)); 
    

    for (unsigned status_nbr = 0; status_nbr<10; ++status_nbr)
        piEstimation += futures[status_nbr].get();

    chrono_time end = std::chrono::high_resolution_clock::now();    
    chrono_duration duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout << "estimation de PI: " << piEstimation/10 << std::endl
              << "it takes " << duration.count()/60 << "m" << duration.count()%60 << "s" << std::endl ;

    return 0;
}