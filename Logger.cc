#include <time.h>
#include <string>
#include <iostream>
#include <sstream>

#include "Timer.h"
#include "Setting.h"

#include "Logger.h"


Logger::Logger(){
	std::stringstream filename;
	if(Setting::read().logName.compare("")==0){
		time_t timer;
		timer = time(NULL);
		filename << "" << timer ;
	}else{
		filename << Setting::read().logName;
	}
	std::stringstream logFileName;
	std::stringstream csvFileName;
	logFileName << filename.str() << ".log";
	csvFileName << filename.str() << ".csv";
	/*
	this->logFile.open(logFileName.str().c_str(), std::ios::out);
	std::cout<<"log " << logFileName.str() << " created" << std::endl;
	if(!logFile.is_open()){
		std::cerr << "Fail to open file!" << std::endl;
		exit(1);
	}
	*/
	
	this->csvFile.open(csvFileName.str().c_str(), std::ios::out);
	std::cout<<"log " << csvFileName.str() << " created" << std::endl;
	if(!csvFile.is_open()){
		std::cerr << "Fail to open file!" << std::endl;
		exit(1);
	}

	started = true;
}

Logger& Logger::getInstance(){
	static Logger instance;
	return instance;
}

Logger::~Logger(){
	logFile.close();
}

void Logger::start(){
	Logger& logger = Logger::getInstance();
	logger.started = true;
	// std::cout<<"Logger enabled\n";
}

void Logger::log(std::string event){
	Logger & logger = Logger::getInstance();
	std::stringstream ss;
	double eventTime = Timer::getCurrentTime();
	ss << eventTime << " " << event;
	if(logger.started){
		logger.write(ss.str());
	}
	logger.logcsv(event);
}

void Logger::log(double pos, std::string event){
	if(Setting::read().isParciallyLog){
		if(
			pos>Setting::read().logStartPos
			&& pos<Setting::read().logEndPos
		){
			Logger::log(event);
		}
	}else{
		Logger::log(event);
	}
}

void Logger::write(std::string str){
	//logFile << str << std::endl;
}

void Logger::writeCSV(std::string str){
	csvFile << str << std::endl;
}

void Logger::logcsv(std::string event){
	static int timeslot = 0;
	static int num_query = 0;
	static int channelFound = 0;
	static int num_vehicles = 0;

	static double lastTime=0;
	static double lastCSMATime = 0;

	if(event.compare("query_database")==0){
		num_query++;
	}else if(event.compare("channel_found")==0){
		channelFound++;
	}else if(event.compare("new")==0){
		num_vehicles++;
	}

	if(Setting::read().Algorithm.compare("PaperWithoutIA")==0){
		if(event.compare("query_database")==0){
			timeslot += 2;
		}else if(event.compare("broadcast_correlation")==0){
			timeslot += 1;
		}
	}else if(Setting::read().Algorithm.compare("PaperWithIA")==0){
		if(event.compare("send_preamble")==0){
			timeslot += 3;
		}
	}else if(Setting::read().Algorithm.compare("PureQuery")==0){
		if(event.compare("query_database")==0){
			timeslot += 2;
		}
	}else if(Setting::read().Algorithm.compare("CSMA")==0){
		double csmaTime = Timer::getCurrentTime();	
		if(lastCSMATime!=csmaTime){
			lastCSMATime = csmaTime;
			if(
				event.compare("difs")==0 ||
				event.compare("backoff")==0 ||
				event.compare("RTS")==0 ||
				event.compare("sifs")==0 ||
				event.compare("CTS")==0 ||
				event.compare("data")==0 ||
				event.compare("ack")==0
			  ){
				timeslot += 1;
			}
		}
		
	}

	double time = Timer::getCurrentTime();
	std::stringstream ss;
	if(time-lastTime>1){
		ss << time << "," << 
			timeslot << "," << 
			num_query << "," <<
			channelFound << "," <<
			num_vehicles;
		this->writeCSV(ss.str());
		lastTime = time;
	}
}


