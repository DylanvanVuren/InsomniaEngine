// basic file operations
#include <iostream>
#include <fstream>

void Write() {
	std::ofstream myfile;
	myfile.open("example.txt");
	myfile << "Writing this to a file." << std::endl;
	myfile.close();
}