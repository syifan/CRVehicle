#ifndef SETTING_H
#define SETTING_H

#include <cstdlib>
#include <vector>
#include <string>

class Setting{
public:
	static Setting& getInstance();
	static Setting& read();

	std::string Algorithm;
	//base stations 
	std::vector<double> baseStationLocation;
	double baseStationBasicCoverage;
	double baseStationExtendCoverage;
	//vehicle related;
	double disappearPos;
	//timer related
	double timeStep;
	double endTime;
	double numNotificationPoints;
	//log related
	bool isParciallyLog;
	double logStartPos;
	double logEndPos;

private:
	Setting();
	Setting(Setting const&);
	void operator=(Setting const&);  

	


	
};

#endif
