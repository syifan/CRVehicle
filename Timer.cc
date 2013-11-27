#include <cstdlib>
#include <iostream>

#include "Setting.h"

#include "Timer.h"

Timer& Timer::getInstance(){
	static Timer instance;
	return instance;
}

double Timer::getTimeStep(){
	Timer& t = Timer::getInstance();
	return t.timeStep;
}

double Timer::getCurrentTime(){
	Timer& t = Timer::getInstance();
	return t.nowTime;
}

bool Timer::advance(){
	Timer& t = Timer::getInstance();
	t.lastTime = t.nowTime;
	t.nowTime = t.nowTime+t.timeStep;

	int numNotificationPoints = Setting::read().numNotificationPoints;
	
	static int nextTick = 1;
	static double boundary = t.maxTime/numNotificationPoints*nextTick;

	if(t.nowTime>boundary && t.lastTime<boundary){
		double percentage = 100.0/numNotificationPoints*nextTick;
		nextTick++;
		boundary = t.maxTime/numNotificationPoints*nextTick;
		std::cout << percentage << "\%" << std::endl;
	}
	
	if(t.nowTime>t.maxTime){
		return false;
	}else{
		return true;
	}
}

Timer::Timer(){
	nowTime = 0; 
	timeStep = Setting::read().timeStep;
	lastTime = 0;
	maxTime = Setting::read().endTime;
}
