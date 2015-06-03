#include <iostream>

#include "ConsoleInput.h"


int main(int argc, char* argv[]) {

	ConsoleInput cmdInput;
	cmdInput.distinguishConsoleInput(argc, argv);

	std::cout << "The number of Files is " << cmdInput.getNumberFiles() << std::endl;
	// std::cout << "The number of Commands is " << cmdInput.numberCommands << std::endl;

	return 0;
}