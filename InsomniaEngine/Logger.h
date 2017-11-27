#include <iostream>
#include <fstream>

class Logger{

	public:
		//Logger const requires file name
		Logger(char* fname);
		//Destruct logger and close the filestream
		~Logger();
		//Write to the file requiring text(char)
		void Write(char* line);
	private:
		std::ofstream o_stream;
};