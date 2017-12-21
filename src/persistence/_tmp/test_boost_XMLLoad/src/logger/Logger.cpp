#include "Logger.h"

#include <string>
#include <ctime>

//necessary for static filestream!!!
std::ofstream Logger::fileStream;

Logger::Logger(int level) : debugLevel(level)  {
	if(DEBUGOUTPUT == DEBUGFILE && !fileStream.is_open()) {
		std::string dir = getenv("HOME");

		std::time_t t = std::time(NULL);
		char mbstr[100];
		std::strftime(mbstr, sizeof(mbstr), "%F-%R", std::localtime(&t));

		dir = dir + "/" + mbstr + "-" + DEBUGFILENAME;

		fileStream.open(dir, std::ios::out | std::ios::app);
	}
}

Logger::~Logger() {

}

void Logger::flushOutput() {
	switch (DEBUGOUTPUT) {
		case DEBUGOFF:
			break;
		case DEBUGTERMINAL:
			std::cout.flush();
			break;
		case DEBUGFILE:
			fileStream.flush();
			break;
		default:
			break;
	}
}

void Logger::closeOutput() {
	if(DEBUGOUTPUT == DEBUGFILE && fileStream.is_open()) {
		fileStream.close();
	}
}