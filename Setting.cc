#include <cstdlib>

#include "Setting.h"

Setting& Setting::read(){
	return Setting::getInstance();
}

Setting& Setting::getInstance(){
	static Setting instance;
	return instance; 
}

Setting::Setting(){
	this->Algorithm = "PaperWithoutIA";


	//base stations
	this->baseStationLocation.push_back(1500);
	this->baseStationLocation.push_back(2500);
	this->baseStationBasicCoverage = 500;
	this->baseStationExtendCoverage = 3*baseStationBasicCoverage;

	//vehicle related
	logStartPos = 1000;
	logEndPos = 2000;
	disappearPos = 3000;	

	//timer related
	timeStep = 1e-5;
	endTime = 1000;
	numNotificationPoints = 100;

	//log related
	isParciallyLog = false;
}
