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
		filename << "" << timer << ".log";
	}else{
		filename << Setting::read().logName << ".log";
	}
	this->logFile.open(filename.str().c_str(), std::ios::out);
	std::cout<<"log " << filename.str() << " created" << std::endl;
	if(!logFile.is_open()){
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
	logFile << str << std::endl;
}