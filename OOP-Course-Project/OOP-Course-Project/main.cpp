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

	std::cout << "---------------------------------------------" << std::endl;

	char* fileName = "test_2.txt";
	
	TextManager fileSource;
	fileSource.readToFile(fileName);
	int numberLines = fileSource.getNumberLines();

	const char** fileLines = fileSource.getFileLines();
	for (int i = 0; i < numberLines; i++) {
		std::cout << "line[" << i << "] is " << fileLines[i] << std::endl;
	}


	std::cout << "--------------------------------------------" << std::endl;

	char* newLine = "std::cout << \"Peshko\" << std::endl;";
	int atLine = 5;
	fileSource.insertLine(newLine, atLine);
	int setLineOn = 0;
	fileSource.setLine(newLine, setLineOn);
	fileLines = fileSource.getFileLines();
	numberLines = fileSource.getNumberLines();
	//std::cout << numberLines << std::endl;
	for (int i = 0; i < numberLines; i++) {
		std::cout << "line[" << i << "] is " << fileLines[i] << std::endl;
	}
	std::cout << "--------------------------------------------" << std::endl;
	fileSource.removeLine(atLine);
	fileLines = fileSource.getFileLines();
	numberLines = fileSource.getNumberLines();
	for (int i = 0; i < numberLines; i++) {
		std::cout << "line[" << i << "] is " << fileLines[i] << std::endl;
	}
	
	//int getLine = 4;
	//std::cout << getLine << " line is " << fileSource.getLine(getLine) << std::endl;

	//std::cout << "--------------------------------------------" << std::endl;
	//fileSource.writeToFile(fileName);
	std::cout << "--------------------------------------------" << std::endl;

	return 0;
}