#ifndef BASESTATION_H
#define BASESTATION_H

class BaseStation{
public:
	BaseStation(double center, double basicCoverage, double extendCoverage);

	bool inBasicRegion(double pos){return abs(pos-center)<basicCoverage;};
	bool inExtendCoverage(double pos){return abs(pos-center)<extendCoverage;}
	double getCenter(){return center;}
	double getBasicCoverage(){return basicCoverage;}
	double getExtendCoverage(){return extendCoverage;}

private:
	/**
	* Base station location.
	*/
	double center;
	/**
	* The base station knows spectrum info in basic coverage
	*/
	double basicCoverage;

	/**
	* The base station can serve vehicles in extend coverage
	*/
	double extendCoverage;
};

#endif