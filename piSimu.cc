#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <chrono>
#include "CLHEP/Random/MTwistEngine.h"

using chrono_time = std::chrono::time_point<std::chrono::high_resolution_clock>;
using chrono_duration = std::chrono::duration<long>;

// Operator to concatanate a string and a number
std::string operator+(const std::string& s, const int& i)
{
    std::ostringstream ss ;
    ss << s << i;
    return ss.str();
}

double pi(CLHEP::MTwistEngine* mtRng_in, int nbrExperiment_in)
{
    double x,y;
    int total = 0;
    for(int _ = 0;_<nbrExperiment_in; _++)
    {
        x= mtRng_in->flat();
        y= mtRng_in->flat();

        // if the point in inside the quarter circle
        if(x*x+y*y <= 1)
            total++;
    }

    return total*4.0/nbrExperiment_in;
}



int main()
{
    double piEstimation = 0;
    // Create the Random Number Generator (here, Mercene Twister)
    CLHEP::MTwistEngine * mtRng = new CLHEP::MTwistEngine();

    chrono_time start = std::chrono::high_resolution_clock::now();
    //Repeat the experiment 10 times
    for(int status_nbr = 0; status_nbr < 10; status_nbr++)
    {
        mtRng->restoreStatus(operator+("./status/status_",status_nbr).c_str()); 
        piEstimation += pi(mtRng,1000000000);  
    }
    
    chrono_time end = std::chrono::high_resolution_clock::now();
    chrono_duration duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout << "estimation de PI: " << piEstimation/10 << std::endl
              << "it takes " << duration.count()/60 << "m" << duration.count()%60 << "s" << std::endl ;

    //Free the space we allowed for the generator
    delete mtRng;
    return 0;
}