#ifndef TIMER_H
#define TIMER_H

/**
* A singleton that controls the simulation time
*/
class Timer{
	public:
		static Timer& getInstance();
		static bool advance();
		static double getTimeStep();
		static double getCurrentTime();
	private:
		Timer();
		Timer( Timer const& );
		void operator=(Timer const&);

		double nowTime;
		double lastTime;
		double timeStep;
		double maxTime;
};

#endif