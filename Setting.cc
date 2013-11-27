#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

#include "Setting.h"

Setting& Setting::read(){
	return Setting::getInstance();
}

Setting& Setting::getInstance(){
	static Setting instance;
	return instance; 
}

void Setting::parseCommandLineOptions(int argc, char** argv){
	int c;
	Setting& setting = Setting::getInstance();
	while( (c = getopt(argc, argv, "a:o::l::v::"))!=-1 ){
		printf("optopt=%c, optarg=%s\n", optopt, optarg);
		switch(c){
		case 'a':{
			printf("option=a, optopt=%c, optarg=%s\n", optopt, optarg);
			bool valid = false;
			if(strcmp(optarg, "PaperWithoutIA")==0){
				valid = true;
			}else if(strcmp(optarg, "PaperWithIA")==0){
				valid = true;
			}else if(strcmp(optarg, "PureQuery")==0){
				valid = true;
			}else if(strcmp(optarg, "CSMA")==0){
				valid = true;
			}
			if(!valid){
				std::cerr << "Algorithm not valid!\n";
				exit(1);
			}else{
				setting.Algorithm = optarg;
			}
			break;
		}
		case 'o':
			printf("option=o, optopt=%c, optarg=%s\n", optopt, optarg);
			setting.logName = optarg;
			break;
		case 'l':
			printf("option=l, optopt=%c, optarg=%s, lambda=%f\n", 
				optopt, optarg, setting.lambda);

			setting.lambda = atof(optarg);
						break;
		case 'v':
			printf("option=v, optopt=%c, optarg=%s, speed=%f\n", 
				optopt, optarg, setting.speed);

			setting.speed = atof(optarg);
			break;
		}
	}
}

Setting::Setting(){
	//This is where default setting is set.

	this->Algorithm = "PaperWithoutIA";


	//base stations
	this->baseStationLocation.push_back(1500);
	this->baseStationLocation.push_back(2500);
	this->baseStationBasicCoverage = 500;
	this->baseStationExtendCoverage = 3*baseStationBasicCoverage;

	//vehicle related
	disappearPos = 3000;	

	//vehicle generate parameter
	lambda = 1;
	speed = 30;
	speedRange = 0.1;
	//timer related
	timeStep = 1e-2;
	endTime = 10000;
	numNotificationPoints = 100;

	//log related
	logStartPos = 1000;
	logEndPos = 2000;
	isParciallyLog = false;
	logName = "";
}
