#include <cstdlib>
#include <vector>
#include <iostream>

#include "Timer.h"
#include "Vehicle.h"
#include "Environment.h"

void generateVehicles(std::vector<Vehicle> & vehicles);

int main(){
	while(Timer::advance()){
		Environment::process();
	}
	return 0;
}


