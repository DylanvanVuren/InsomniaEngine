#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include "StackWalker.h"

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
		void Write(int ltype);
		//Set the time and calculate milis
		std::string deterTime();
		//Stack print
		//int WriteStack(int i);
		std::string WriteStack();
		//void WriteStack();
	private:
		std::ofstream o_stream;
};

class StackWImpl : public StackWalker
{
public:

	StackWImpl() : StackWalker() {
	}
	virtual void OnOutput(LPCSTR szText)
	{
		o_stream.open("logfile.txt", std::ofstream::app);
		printf(szText);
		StackWalker::OnOutput(szText);
		o_stream << szText << std::endl;
	}
private:
	std::ofstream o_stream;
};
