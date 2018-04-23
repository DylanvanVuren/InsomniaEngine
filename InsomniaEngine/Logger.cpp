// basic file operations
#include "logger.h"
#include <time.h>

static const char* ftxt = "logfile.txt";
static int logLevel;
static std::string offset = " \t ";

Logger::Logger() {
	o_stream.open(ftxt);

	////Set top of log file
	//o_stream << deterTime() << offset << "LOG" << offset << "Log name is" << offset << ftxt << std::endl;
	//o_stream << deterTime() << offset << "LOG" << offset << "Logging level" << offset << logLevel << std::endl; //have to adjust
	//o_stream << deterTime() << offset << "LOG" << offset << "Logging start\n" << std::endl;
}
//int Logger::WriteStack(int i) {
//	i = errno;
//	NL_RETURN(i);
//}

//void Logger::WriteStack() {
//	StackWImpl sw;
//	sw.ShowCallstack();
//}
//
//std::string Logger::WriteStack() {
//	StackWImpl sw;
//	return sw.terug;
//}

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
	sprintf_s(TimeStamp, "[%d:%d:%d:%d]", stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
	return TimeStamp;
}

void Logger::Write(char* text) {
	o_stream << deterTime() << text << std::endl;
}

void Logger::Write(int lvl) {
	o_stream << lvl << std::endl;
	logLevel = lvl;
}

void Logger::Write(int lvl, char* text) {

	if (lvl == Debug) {
		o_stream << deterTime() << offset << "Debug" << offset << text << std::endl;
	}
	else if (lvl == Warning) {
		o_stream << deterTime() << offset << "Warning" << offset << text << std::endl;
	}
	else if (lvl == Info) {
		o_stream << deterTime() << offset << "Info" << offset << text << std::endl;
	}
	else if (lvl == Error) {
		o_stream << deterTime() << offset << "Error" << offset << text << std::endl;
		o_stream << deterTime() << offset << "errno\n" << offset << offset << std::strerror(errno) << std::endl;
		o_stream << deterTime() << offset << "Trace" << std::endl;
		//o_stream << offset << offset << "Error at: " << std::string(__FUNCTION__) << "(line:" << __LINE__ << ")"  << std::endl;
		//o_stream << offset << offset << offset << WriteStack() << std::endl;//WriteStack();
		//o_stream << offset << offset << offset << WriteStack() << std::endl;
	}
	logLevel = lvl;
}

Logger::~Logger() {
	o_stream.flush();
	o_stream.close();
}