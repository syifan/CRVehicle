#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "Timer.h"
#include "Logger.h" 
#include "Setting.h"
#include "Vehicle.h"

#include "Environment.h"

Environment& Environment::getInstance(){
	static Environment instance;
	return instance;
}

Environment::Environment(){
	Setting& s = Setting::getInstance();
	for(uint i=0; i<s.baseStationLocation.size(); i++){
		BaseStation bs(
			s.baseStationLocation[i], 
			s.baseStationBasicCoverage,
			s.baseStationExtendCoverage
		);
		this->baseStations.push_back(bs);
	}
}

void Environment::process(){
	Environment& e = Environment::getInstance();
	e.channelOccupied = false;
	e.generatePoissonVehicles(e.vehicles);
	for(uint i = 0; i<e.vehicles.size(); i++){
		Vehicle& v = e.vehicles[i];
		v.move();
		if(Setting::read().Algorithm.compare("PaperWithIA")==0){
			v.paperAlgorithmWithIA();
		}else if(Setting::read().Algorithm.compare("PaperWithoutIA")==0){
			v.paperAlgorithm();
		}else if(Setting::read().Algorithm.compare("PureQuery")==0){
			v.pureQueryAlgorithm();
		}else if(Setting::read().Algorithm.compare("CSMA")==0){
			v.CSMACA();
		}
	}
}

void Environment::generatePoissonVehicles(std::vector<Vehicle> & vehicles){
	//Expected vehicles per second
	double lambda = Setting::read().lambda;
	double threshold = lambda*Timer::getTimeStep();
	double r = ((double)rand())/((double)RAND_MAX);
	if(r<threshold){
		Environment & e = Environment::getInstance();
		e.generateOneVehicle(vehicles);
	}

}

void Environment::generateOneVehicle(std::vector<Vehicle> & vehicles){
	static long id = 0;
	double meanSpeedInMeterPerSecond = Setting::read().speed;
	double speedRange = Setting::read().speedRange;
	//A random number uniformly distributed (0, 1];
	double r = ((double)rand())/((double)RAND_MAX);
	//A random speed generated as uniformly distributed in +-10% mean speed
	double speed = r*(meanSpeedInMeterPerSecond*speedRange*2.0) 
					+ (1-speedRange)*meanSpeedInMeterPerSecond;
	//generate a vehicle	
	Vehicle v(id, speed);
	vehicles.push_back(v);
	
	
	//increase global id.
	id++;
}

void Environment::addCorrelationInfo(double position){
	Environment& e = Environment::getInstance();
	if(e.lookUpCorrelationDatabaseAux(
			position, 0, e.correlationDatabase.size()-1, 1
		)
	){
		return;
	}
	//get current time
	double currentTime = Timer::getCurrentTime();
	//Prepare a correlation info data structure
	CorrelationInfo ci(position, currentTime);
	// put it in the database
	e.correlationDatabase.push_back(ci);

	std::sort(e.correlationDatabase.begin(), e.correlationDatabase.end());

	//log this event
	// std::stringstream ss;
	// ss << "Correlation_found: " << ci.getPosition();
	// Logger::log(ss.str());
}

bool Environment::lookUpCorrelationDatabase(double position){
	Environment& e = Environment::getInstance();
	int left = 0;
	int right = e.correlationDatabase.size()-1;
	if(e.correlationDatabase.size()==0){
		return false;
	}
	return e.lookUpCorrelationDatabaseAux(position, left, right);
}


bool Environment::lookUpCorrelationDatabaseAux(
	double position, int left, int right, double correlationMaxDist
){
	//std::cout << "left: " << left << "right: "<< right << std::endl; 
	int middle = (left+right)/2;
	// If correlation info reported in correlationMaxDist meters, it is believed
	// as correlation exist
	//double correlationMaxDist = 100;
	if(left>right || left<0 || right<0){
		return false;
	}if(left==right){
		return abs(correlationDatabase[left].getPosition() - position)
			<correlationMaxDist;
	}else if(
		abs(correlationDatabase[middle].getPosition() - position)
			<correlationMaxDist
	){
		return true;
	}else{
		if(correlationDatabase[middle].getPosition() < position){
			return lookUpCorrelationDatabaseAux(position, middle+1, right);
		}else{
			return lookUpCorrelationDatabaseAux(position, left, middle);
		}
	}
}

void Environment::receiveIAPreamble(int vehicleId, double pos){
	std::stringstream ss;
  	ss << " preamble_received " 
  		<< "from_Vehicle_" << vehicleId
  		<< " at_" << pos;
  	Logger::log(ss.str());
	Environment& e = Environment::getInstance();
	for(unsigned int i=0; i<e.baseStations.size(); i++){
		if(e.baseStations[i].inExtendCoverage(pos)){
			e.vehicles[vehicleId].addLocalSpectrumInfo(
				e.baseStations[i].getCenter()
					-e.baseStations[i].getBasicCoverage(), 
				e.baseStations[i].getCenter()
					+e.baseStations[i].getBasicCoverage()
			);
		}
	}
}



