#ifndef SETTING_H
#define SETTING_H

#include <cstdlib>
#include <vector>
#include <string>

class Setting{
public:

	static Setting& getInstance();
	static Setting& read();

	static void parseCommandLineOptions(int argc, char** argv);

	std::string Algorithm;
	//base stations 
	std::vector<double> baseStationLocation;
	double baseStationBasicCoverage;
	double baseStationExtendCoverage;
	//vehicle related;
	double disappearPos;
	//vehicle generate parameter
	double meanDist;
	double lambda;
	double speed;
	double speedRange;
	//timer related
	double timeStep;
	double endTime;
	double numNotificationPoints;
	//log related
	bool isParciallyLog;
	double logStartPos;
	double logEndPos;
	std::string logName;
	//whether or not use real data
	int useRealData;

private:
	Setting();
	Setting(Setting const&);
	void operator=(Setting const&);  

	


	
};

#endif
