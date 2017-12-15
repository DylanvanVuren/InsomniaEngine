#include "logger.h"
#include <cstdlib>
#include <windows.h>
#include <tchar.h>
#include <iostream>

int compare(int a, int b) {
	if (a < 0 || b < 0) {
		throw std::invalid_argument("received negative value");
	}
}

int main(void) {
	Logger *pLog = new Logger();
	/*for (int i = 0; i < 100; i++) {
		char c[50];
		sprintf_s(c, "Looped: %d times", i);
		pLog->Write(2,c);
	}*/	
	StackWImpl sw;
	double not_a_number = std::log(-1.0);
	if (errno == EDOM) {
		char c[50];
		sprintf_s(c, " ", not_a_number);
		pLog->Write(3, c);
	}
	
	return 0;
}