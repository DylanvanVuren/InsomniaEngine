#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

class Logger{
	public:
		//logger types
		enum LOGTYPE {
			Debug,
			Warning,
			Error,
			Info
		};
		//Logger constructor requires file name
		Logger(char* fname);
		//Destruct logger and close the filestream
		~Logger();
		//Write to the file requiring text(char)
		void Write(LOGTYPE ltype, char* line);
		//char& deterTime();
		std::string deterTime();
		static const std::string PRIORITY_NAMES[];

	private:
		std::ofstream o_stream;
};


