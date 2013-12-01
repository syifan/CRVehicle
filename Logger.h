#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <cstdlib>

class Logger{
public:
	static Logger& getInstance();
	static void log(std::string event);
	static void log(double pos, std::string event);
	static void start();
private:
	Logger();
	~Logger();
	Logger(Logger const&);
	void operator=(Logger const&);

	void write(std::string str);
	void writeCSV(std::string str);
	
	void logcsv(std::string event);

	std::ofstream logFile;
	std::ofstream csvFile;

	bool started;

};

#endif
