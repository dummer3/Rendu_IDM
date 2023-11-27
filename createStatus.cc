/*************************************************/ 
/*        GENERATE STATUS FOR OUR RNG            */ 
/*************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include "CLHEP/Random/MTwistEngine.h"

// Operator to concatanate a string and a number
std::string operator+(const std::string& string_in, const int& number_in)
{
    std::ostringstream ss ;
    ss << string_in << number_in;
    return ss.str();
}

int main()
{
// Create the Random Number Generator (here, Mercene Twister)
CLHEP::MTwistEngine * mtRng = new CLHEP::MTwistEngine();

for(int status_nbr = 0; status_nbr < 10; status_nbr++)
{
    mtRng->saveStatus(operator+("./status/status_",status_nbr).c_str());

    // loop to move the status
    for(int _ = 0; _ < 2000000000; _++)
        mtRng->flat();
}

//Free the space we allowed for the generator
delete mtRng;
return 0;
}

// TO EXECUTE IT
// CLHEP_DIR=/home/local.isima.fr/thcliquot/shared/ZZ3/IDM/tp5/Random/
// g++ -o piSimu piSimu.cc -I $CLHEP_DIR/include -L $CLHEP_DIR/lib -lCLHEP-Random-2.1.0.0 -static
