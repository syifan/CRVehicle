#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>

#include "BaseStation.h"
#include "Vehicle.h"

class CorrelationInfo{
private:
	double position;
	double time;
public:
	CorrelationInfo(double position, double time){
		this->position = position;
		this->time = time;
	}
	void updateTime(){
		this->time = Timer::getCurrentTime();
	}
	double getPosition(){
		return this->position;
	}
	double getTime(){
		return this->time;
	}
	bool operator < (
		const CorrelationInfo& ci2
	) const{
		return this->position < ci2.position;
	}
	bool operator == (const CorrelationInfo& ci2){
		return ( this->position == ci2.position );
	}
};

/**
* A singleton that contains and controls everything.
*/
class Environment{
public:
	static Environment& getInstance();
	/**
	* Processes all actions in this time slot
	*/
	static void process();

	/**
	* Receives a broadcast and put the correlation info in the correlation 
	* database
	*/
	static void addCorrelationInfo(double position);

	/**
	* Looks up the database to find correlation exist or not.
	* Returns true if correlation exist in certain distance;
	*/
	static bool lookUpCorrelationDatabase(double position);

	/**
	* Responds to IA preamble and lets the vehicle know spectrum info
	*/
	static void receiveIAPreamble(int id, double pos);

	static bool isChannelOccupied(){
		return Environment::getInstance().channelOccupied;
	};
	static void occupyChannel(){
		Environment::getInstance().channelOccupied = true;
	}
private:
	Environment();
	Environment(Environment const&);
	void operator=(Environment const&);

	/**
	* Generates vehicles in Poisson manner
	*/
	void generatePoissonVehicles(std::vector<Vehicle> & vehicles);


	int lookUpCorrelationDatabaseAux(
		double position, int left, int right, double maxCorrelationDist=100
	);

	/**
	* Generate a vehicle and put it into the vehicles vector
	*/
	void generateOneVehicle(std::vector<Vehicle> & vehicles);

	/**
	* A container that contains all the vehicles
	*/
	std::vector<Vehicle> vehicles;

	/**
	* All base stations
	*/ 
	std::vector<BaseStation> baseStations;

	/**
	* Correlation database is the container for all correlation info.
	* I assume once a vehicle broadcast the correlation info, all cars know 
	* that. So, I put all of correlation info in a centralized database. 
	*/
	std::vector<CorrelationInfo> correlationDatabase; 
	
	bool channelOccupied;
};

#endif
