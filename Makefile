all:
	g++ -Wall -Werror -Wfatal-errors\
		main.cc \
		Timer.cc \
		Vehicle.cc \
		Logger.cc \
		Environment.cc \
		Setting.cc \
		BaseStation.cc \
	-o main
