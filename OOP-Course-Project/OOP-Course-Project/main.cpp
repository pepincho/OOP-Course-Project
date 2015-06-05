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

	char* fileName = "test.txt";
	
	TextManager fileSource;
	fileSource.readFile(fileName);

	char* sourceFile = fileSource.source;

	//for (int i = 0; i < fileSource.fileSize; i++) {
	//	std::cout << "source[" << i << "] = " << fileSource.source[i] << std::endl;
	//}
	//std::cout << std::endl << std::endl;

	for (int i = 0; i < fileSource.numberLines; i++) {
		std::cout << "sourceLine[" << i << "] = " << fileSource.sourceLines[i] << std::endl;
	}

	std::cout << "--------------------------------------------" << std::endl;

	//char* newLine = "std::cout << \"Peshko\" << std::endl;";
	//std::cout << strlen(newLine) << std::endl;
	//int atLine = 5;

	//fileSource.insertLine(newLine, atLine);

	//int getLine = 4;
	//std::cout << getLine << " line is " << fileSource.getLine(getLine) << std::endl;

	//std::cout << "--------------------------------------------" << std::endl;
	//
	//char* currText = "opa.cpp";
	//char* alabala = ".old";

	//char newText[50];

	//strcpy(newText, currText);
	//strcat(newText, alabala);
	//std::cout << newText << std::endl;

	//rename(fileName, newText);

	return 0;
}