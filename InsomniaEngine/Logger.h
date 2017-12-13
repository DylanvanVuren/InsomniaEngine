#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

#define Debug 0
#define Warning 1
#define Info 2
#define Error 3

/*
//logger types
enum LOGTYPE {
	Debug,
	Warning,
	Error,
	Info
};
*/

class Logger{
	public:
		//Logger constructor requires file name
		Logger();
		//Destruct logger and close the filestream
		~Logger();
		//void setFile(char* fname);
		//Write to the file requiring text(char) and the log level
		void Write(int ltype, char* line);
		void Write(char* line);
		//Set the time and calculate milis
		std::string deterTime();

	private:
		std::ofstream o_stream;
};


