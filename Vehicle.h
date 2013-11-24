#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>

class Vehicle{

public:
	Vehicle(long id, double speed);

	void move();
	void paperAlgorithm();
	void paperAlgorithmWithIA();

	std::string str();
	
	void addLocalSpectrumInfo(double start, double end);
protected:
	long id;
	//0 for transmitting;
	//1 for sensing
	int mode;

	double speed;
	double position;

	double lastSensePos;
	double lastSenseTime;

	double disabled;
 
	std::vector<double> correlationPoints;

	struct KnownSpectrumRange{
		double start;
		double end;
	};

	std::vector<KnownSpectrumRange> localSpectrumInfo;

	/**
	* Judges if the vehicle enters a new region, 
	* Return true if the vehicle have traversed 100 meters or 60 seconds
	*/
	bool needSpectrumInfo();

	/**
	* Looks up in local database and tries to find correlation information,
	* Returns true if local information exist;
	*/
	bool isCorrelationInfoExist();

	/**
	* Senses local WS RSSI and 2G RSSI, and try to find correlation 
	* Returns true if correlation exist.
	*/
	bool isCorrelationExist();

	/**
	* Senses local WS channel and returns true if WS RSSI > TH
	*/
	bool isWSRSSIGreaterThanTH();
	/**
	* Senses local WS channel and returns true if 2G RSSI > TH
	*/
	bool isCellularRSSIGreaterThanTH();

	/**
	* Does corresponding action if empty channel is found, no matter by sensing
	* or by querying database
	*/
	void channelFound();

	/**
	* Conducts actions for querying the database
	*/
	void queryDatabase();

	/**
	* Conducts actions for broadcasting the correlation information
	*/
	void broadcastCorrelation();

	/**
	* Checks if this vehicle already knows the spectrum information at this 
	* point.
	*/
	bool lookUpLocalSpectrumInfo();

	void sendPreamble();

};

#endif
