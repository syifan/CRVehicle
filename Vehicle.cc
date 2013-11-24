#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

#include "Timer.h"
#include "Logger.h"
#include "Environment.h"
#include "Setting.h"

#include "Vehicle.h"



Vehicle::Vehicle(long id, double speed){
	this->id = id;
	this->speed = speed;
	this->mode = 0;

	this->lastSensePos = -1000;
	this->lastSenseTime = -1000;

	this->disabled = false;
	// std::cout << "new Vehicle"<<std::endl;
}

std::string Vehicle::str(){
	std::stringstream ss;
	ss 	<< "Vehicle_" << this->id;
	return ss.str();
}

void Vehicle::move(){
	Timer& t = Timer::getInstance();
	double displacement = t.getTimeStep()*speed;
	this->position+=displacement;
	// std::cout << this->str() << ": " << this->position << std::endl;
	if(this->position > Setting::read().disappearPos){
		Logger::start();
		this->disabled = true;
	}
}

void Vehicle::paperAlgorithm(){
	// std::cout<< __FUNCTION__ << std::endl;
	if(disabled) return;
	switch(mode){
	case 0:
		if(this->needSpectrumInfo()){
			mode = 1;
		}
		break;
	case 1:
		bool needToQuery = false;
		if(this->isCorrelationInfoExist()){
			if(this->isWSRSSIGreaterThanTH()){
				needToQuery = true;
			}else{
				if(this->isCellularRSSIGreaterThanTH()){
				}else{
					needToQuery = true;
				}
			}
		}else{
			needToQuery = true;
		}
		if(needToQuery){
			this->queryDatabase();
			if(this->isCorrelationExist()){
				this->broadcastCorrelation();
			}
		}
		this->channelFound();

		mode = 0;
		break;
	}
}

void Vehicle::paperAlgorithmWithIA(){
	// std::cout<< __FUNCTION__ << std::endl;
	if(disabled) return;
	switch(mode){
	case 0:
		if(this->needSpectrumInfo()){
			mode = 1;
		}
		break;
	case 1:
		bool needToQuery = false;
		if(!this->lookUpLocalSpectrumInfo()){
			if(this->isCorrelationInfoExist()){
				if(this->isWSRSSIGreaterThanTH()){
					needToQuery = true;
				}else{
					if(this->isCellularRSSIGreaterThanTH()){
					}else{
						needToQuery = true;
					}
				}
			}else{
				needToQuery = true;
			}
		}
		if(needToQuery){
			this->queryDatabase();
			if(this->isCorrelationExist()){
				this->broadcastCorrelation();
			}
		}
		this->channelFound();

		mode = 0;
		break;
	}
}

bool Vehicle::needSpectrumInfo(){
	
	double distSinceLastSense = abs(this->position - lastSensePos);
	double timeSinceLastSense = abs(Timer::getCurrentTime()- lastSenseTime);

	if(distSinceLastSense>100 || timeSinceLastSense>60){
		return true;
	}else{
		return false;
	}

}

bool Vehicle::isCorrelationInfoExist(){
	bool ret = Environment::lookUpCorrelationDatabase(this->position);
	if(ret){
		std::stringstream ss;
		ss << " Correlation_used " << this->position;
		
		Logger::log(this->position, this->str() + ss.str()); 
		
	}
	return ret;
}

bool Vehicle::isCorrelationExist(){
	double threshold = 0.5;
	double r = ((double)rand())/((double)RAND_MAX);
	if(r<threshold){
		return true;
	}else{
		return false;
	}
}

bool Vehicle::isWSRSSIGreaterThanTH(){
	double threshold = 0.5;
	double r = ((double)rand())/((double)RAND_MAX);
	if(r<threshold){
		return true;
	}else{
		return false;
	}
}

bool Vehicle::isCellularRSSIGreaterThanTH(){
	double threshold = 0.9;
	double r = ((double)rand())/((double)RAND_MAX);
	if(r<threshold){
		return true;
	}else{
		return false;
	}
}

void Vehicle::channelFound(){
	
	Logger::log(this->position, this->str() + " channel_found");
	
	this->lastSenseTime = Timer::getCurrentTime();
	this->lastSensePos	= this->position;
}

void Vehicle::queryDatabase(){
	
	Logger::log(this->position, this->str() + " query_database");
	

	if(Setting::read().Algorithm.compare("PaperWithIA")==0){
		this->sendPreamble();
	}
}

void Vehicle::broadcastCorrelation(){
	
	Logger::log(this->position, this->str() + " broadcast_correlation");
	
	Environment::addCorrelationInfo(this->position);
	// std::cout<<"broadcast! " <<Setting::read().Algorithm << std::endl;
	if(Setting::read().Algorithm.compare("PaperWithIA")==0){
		// std::cout<<"to send preamble\n";
		this->sendPreamble();
	}
}


void Vehicle::sendPreamble(){
	// std::cout<<"sending preamble\n";
	
	Logger::log(this->position, this->str() + " send_pramble");
	
	Environment::receiveIAPreamble(this->id, this->position);

}

bool Vehicle::lookUpLocalSpectrumInfo(){
	for(uint i=0; i<localSpectrumInfo.size(); i++){
		if(
			this->position > localSpectrumInfo[i].start
			&& this->position < localSpectrumInfo[i].end
		  ){
		  	std::stringstream ss;
		  	ss << " Local_spectrum_available " 
		  		<< localSpectrumInfo[i].start << "-"
		  		<< localSpectrumInfo[i].end;
		  	Logger::log(this->position, this->str() + ss.str());
			return true;
		}
	}
	return false;
}

void Vehicle::addLocalSpectrumInfo(double start, double end){
	KnownSpectrumRange ksr;
	ksr.start = start;
	ksr.end = end;
	this->localSpectrumInfo.push_back(ksr);
	std::stringstream ss;
  	ss << " Local_spectrum_added " 
  		<< start << "-"
  		<< end;
  	Logger::log(this->position, this->str() + ss.str());
}









