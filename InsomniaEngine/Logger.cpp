// basic file operations
#include "logger.h"
#include <time.h>

static const char* ftxt = "logfile.txt";

void Logger::setLogLvl(int lvl) {

}

Logger::Logger() {
	o_stream.open(ftxt);
	
	//Set top of log file
	o_stream << deterTime() << "Log name set " << &ftxt << std::endl;
	o_stream << deterTime() << "Logging start " << std::endl;
	o_stream << deterTime() << "Logging lvl " << lvl << std::endl;


}

std::string Logger::deterTime() {
	SYSTEMTIME stime;
	//structure to store system time (in usual time format)
	FILETIME ltime;
	//structure to store local time (local time in 64 bits)
	FILETIME ftTimeStamp;
	char TimeStamp[256];//to store TimeStamp information
	GetSystemTimeAsFileTime(&ftTimeStamp); //Gets the current system time

	FileTimeToLocalFileTime(&ftTimeStamp, &ltime);//convert in local time and store in ltime
	FileTimeToSystemTime(&ltime, &stime);//convert in system time and store in stime

	//Store text format in TimeStamp for output
	sprintf(TimeStamp, "[%d:%d:%d:%d] ", stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
	return TimeStamp;
}

void Logger::Write(char* text) {
	o_stream << deterTime() << text << std::endl;
}

void Logger::Write(int lvl, char* text) {
	if (lvl == Debug){
		o_stream << "Error" << deterTime() << text << std::endl;
	}else if(lvl == Warning){
		o_stream << "Warning" << deterTime() << text << std::endl;
	}
	else if (lvl == Info) {
		o_stream << "Info" << deterTime() << text << std::endl;
	}
	else if (lvl == Error) {
		o_stream << "Error" << deterTime() << text << std::endl;
	}
}

Logger::~Logger() {
	o_stream.flush();
	o_stream.close();
}