#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "CLHEP/Random/MTwistEngine.h"


// Operator to concatanate a string and a number
std::string operator+(const std::string& string_in, const int& number_in)
{
    std::ostringstream ss ;
    ss << string_in << number_in;
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


int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        std::cerr << "You need to enter a file name containing a status" << std::endl;
        exit(-1);
    }

    // Create the Random Number Generator (here, Mercene Twister)
    CLHEP::MTwistEngine * mtRng = new CLHEP::MTwistEngine();

    //Repeat the experiment 10 times
    mtRng->restoreStatus(argv[1]); 
    std::cout << pi(mtRng,1000000000) << std::endl;  

    //Free the space we allowed for the generator
    delete mtRng;
    return 0;
}