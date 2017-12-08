// basic file operations
#include "logger.h"
#include <time.h>

Logger::Logger(char* fname) {
	o_stream.open(fname);
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
	sprintf(TimeStamp, " %d:%d:%d:%d ", stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
	return TimeStamp;
}

void Logger::Write(LOGTYPE ltype, char* text) {
	o_stream << ltype << deterTime() << text << std::endl;
}



Logger::~Logger() {
	o_stream.flush();
	o_stream.close();
}