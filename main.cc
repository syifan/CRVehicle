#include <cstdlib>
#include <vector>
#include <iostream>

#include "Timer.h"
#include "Vehicle.h"
#include "Setting.h"
#include "Environment.h"

void generateVehicles(std::vector<Vehicle> & vehicles);

int main(int argc, char **argv){
	Setting::parseCommandLineOptions(argc, argv);
	while(Timer::advance()){
		Environment::process();
	}
	return 0;
}


