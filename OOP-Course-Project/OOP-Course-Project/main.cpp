#include <iostream>

#include "ConsoleInput.h"
#include "TextManager.h"

#include "CommandFactory.h"


int main(int argc, char* argv[]) {

	ConsoleInput cmdInput;
	cmdInput.distinguishConsoleInput(argc, argv);

	std::cout << "The number of Files is " << cmdInput.getNumberFiles() << std::endl;
	const char** files = cmdInput.getPathsToFiles();
	for (int i = 0; i < cmdInput.getNumberFiles(); i++) {
		std::cout << "file[" << i << "] is " << files[i] << std::endl;
	}
	std::cout << "The number of Commands is " << cmdInput.getNumberCommands() << std::endl;
	const char** nameCommands = cmdInput.getCommands();
	for (int i = 0; i < cmdInput.getNumberCommands(); i++) {
		std::cout << "command[" << i << "] is " << nameCommands[i] << std::endl;
	}

	std::cout << "------------------------------------------" << std::endl;

	//char* currFileName = "test_2.txt";
	char* currFileName = "test_new_lines_style_0.txt";

	TextManager fileSource(currFileName);

	char** source = (char**) fileSource.getFileLines();
	int counterLines = fileSource.getNumberLines();

	for (int i = 0; i < counterLines; i++) {
		std::cout << "line[" << i << "] -> " << source[i] << std::endl;
	}
	int counter = 0;
	for (int i = 0; i < counterLines; i++) {
		counter += strlen(source[i]);
	}
	std::cout << "SIZE OF THE FILE BEFORE COMMANDS: " << counter << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	CommandFactory commandFac(cmdInput.getCommands(), cmdInput.getNumberCommands());
	int numberCommands = commandFac.getNumberCommands();
	
	for (int i = 0; i < numberCommands; i++) {
		commandFac.getCommands()[i]->processCommand(fileSource);
	}

	std::cout << "------------------------------------------" << std::endl;

	char** sourceAfter = (char**)fileSource.getFileLines();
	counterLines = fileSource.getNumberLines();
	
	//for (int i = 0; i < counterLines; i++) {
	//	std::cout << "<> line[" << i << "] -> " << source[i] << std::endl;
	//}

	std::cout << "------------------------------------------" << std::endl;

	//std::cout << "size " << strlen(sourceAfter[5]) << std::endl;
	//std::cout << "check " << sourceAfter[5] << std::endl;

	int counterSymbols = 0;
	
	for (int i = 0; i < counterLines; i++) {
		counterSymbols += strlen(sourceAfter[i]);
	}

	std::cout << "SIZE OF THE FILE AFTER COMMANDS: " << counterSymbols << std::endl;

	for (int i = 0; i < counterLines; i++) {
		std::cout << "<> line[" << i << "] -> " << source[i] << " len: " << strlen(source[i]) << std::endl;
	}

	std::cout << "------------------------------------------" << std::endl;
	return 0;
}