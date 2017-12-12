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
		void setFile(char* fname);
		//Write to the file requiring text(char)
		void Write(int ltype, char* line);
		void Write(char* line);
		void setLogLvl(int lvl);
		//char& deterTime();
		std::string deterTime();
		static const std::string PRIORITY_NAMES[];

	private:
		std::ofstream o_stream;
};


