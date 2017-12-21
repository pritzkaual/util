/*
 * Logger.h
 *
 *  Created on: 28.05.2017
 *      Author: root
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <mutex>

class Logger {
private:

	int debugLevel;
	std::mutex mtx;

public:
	static std::ofstream fileStream;
	Logger(int level);
	~Logger();

	template<typename T>
	std::ostream& operator<<(const T text) 
  {
		std::unique_lock<std::mutex> lock(mtx);
		if(debugLevel <= MAXLOGLEVEL) {
			switch (DEBUGOUTPUT) {
			case DEBUGOFF:
				break;
			case DEBUGTERMINAL:
				return std::cout << text;
				break;
			case DEBUGFILE:
				return fileStream << text;
				break;
			default:
				break;
			}
		}
		return std::cout;
	}

	void flushOutput();
	void closeOutput();

};

/* Example

Logger(logwarning) << "mytest" << 1 << std::endl
log.warning("Text" + "test" +str(2)) -> | WARNING:     Texttest2        |
                                        |              tst geht weiter  |

*/
#endif /* IMPL_INCLUDE_UTILTY_LOGGER_H_ */