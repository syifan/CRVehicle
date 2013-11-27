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

void Vehicle::pureQueryAlgorithm(){
	//std::cout<< __FUNCTION__ << std::endl;
	if(disabled) return;
	if(disabled) return;
	switch(mode){
	case 0:
		if(this->needSpectrumInfo()){
			mode = 1;
		}
		break;
	case 1:
		this->queryDatabase();
		this->channelFound();
		mode = 0;
		break;
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

void Vehicle::CSMACA(){
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
				this->outputBuffer++;
				if(this->isCorrelationExist()){
					this->broadcastCorrelation();
					this->outputBuffer++;
				}
			}
			this->CSMACAAlgorithm();
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
	double threshold = 0.3;
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



void Vehicle::CSMACAAlgorithm(){
	static int state = 0;
	static int ifs_timer;
	static int default_difs = 3; 
	//static int default_sifs = 1;
	static int backoff_timer;
	static int num_retry;
	std::stringstream ss;
	if(disabled) return;
	switch(state){
		case 0:
			if(this->outputBuffer>0){
				state = 1;
				ifs_timer = default_difs;
			}
			break;
		case 1: //DIFTS
		   	ss << " difs ";	
			Logger::log(this->position, this->str()+ss.str());

			if(Environment::isChannelOccupied()){
				state = 2;
				backoff_timer = getBackoffTimer(num_retry);
				num_retry++;
			}else{
				ifs_timer--;
				if(ifs_timer<0){
					state = 2;
					backoff_timer = getBackoffTimer(num_retry);
				}
			}
			break;
		case 2: //backoff
		    ss << " backoff ";	
			Logger::log(this->position, this->str()+ss.str());
			if(!Environment::isChannelOccupied()){
				backoff_timer--;
				if(backoff_timer<0){
					state = 3;
				} 
			}else{
				state = 0;
			}
			break;
		case 3: //transmitting
			ss << " RTS ";	
			Logger::log(this->position, this->str()+ss.str());
			state = 4;
			Environment::occupyChannel();
			break;
		case 4: //sift for CTS
			ss << " sifs";
			Logger::log(this->position, this->str()+ss.str());
			state = 5;
			break;
		case 5:
			ss << "CTS ";
			Logger::log(this->position, this->str()+ss.str());
			state = 6;
			Environment::occupyChannel();
			break;
		case 6:
			ss << "sifs";
			Logger::log(this->position, this->str()+ss.str());
			state = 7;
			break;
		case 7:
			ss << "data";
			Logger::log(this->position, this->str()+ss.str());
			state = 8;
			Environment::occupyChannel();
			break;
		case 8:
			ss << "sifs";
			Logger::log(this->position, this->str()+ss.str());
			state = 9;
			break;
		case 9:
			ss << "ack";
			Logger::log(this->position, this->str()+ss.str());
			Environment::occupyChannel();
			this->outputBuffer--;
			num_retry = 0;
			state = 0;
			break;
	}
}

int Vehicle::getBackoffTimer(int retry){
	int cw_min = 15;
	int cw_max = 0;
	int cw = 0;
	if(retry==0){
		return cw_min;
	}else{
		cw_max = cw_min * ( 2 * retry );
		if(cw_max>1023){
			cw_max = 1023;
		}
		cw = rand()%(cw_max-cw_min)+cw_min;
		return cw;
	}
	return cw;
}	


