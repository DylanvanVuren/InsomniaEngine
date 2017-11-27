// basic file operations
#include "logger.h"

Logger::Logger(char* fname) {
	o_stream.open(fname);
}

void Logger::Write(char* text) {
	o_stream << text << std::endl;
}

Logger::~Logger() {
	o_stream.flush();
	o_stream.close();
}