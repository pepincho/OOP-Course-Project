#include <iostream>

#include "ConsoleInput.h"
#include "TextManager.h"


int main(int argc, char* argv[]) {

	ConsoleInput cmdInput;
	cmdInput.distinguishConsoleInput(argc, argv);

	std::cout << "The number of Files is " << cmdInput.getNumberFiles() << std::endl;
	const char** files = cmdInput.getPathsToFiles();
	for (int i = 0; i < cmdInput.getNumberFiles(); i++) {
		std::cout << "file[" << i << "] is " << files[i] << std::endl;
	}
	std::cout << "The number of Commands is " << cmdInput.getNumberCommands() << std::endl;
	const char** commands = cmdInput.getCommands();
	for (int i = 0; i < cmdInput.getNumberCommands(); i++) {
		std::cout << "command[" << i << "] is " << commands[i] << std::endl;
	}



	return 0;
}