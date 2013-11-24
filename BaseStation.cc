#include <cstdlib>

#include "BaseStation.h"

BaseStation::BaseStation(
	double center, double basicCoverage, double extendCoverage
){
	this->center = center;
	this->basicCoverage = basicCoverage;
	this->extendCoverage = extendCoverage;
}