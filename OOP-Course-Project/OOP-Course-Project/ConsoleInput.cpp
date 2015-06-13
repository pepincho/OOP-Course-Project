#include "ConsoleInput.h"

#include <iostream>
#include <assert.h>


ConsoleInput::ConsoleInput() {
	this->numberFiles = 0;
	this->numberCommands = 0;
	this->pathsToFiles = NULL;
	this->commands = NULL;
	//std::cout << "ConsoleInput::ConsoleInput()" << std::endl;
}

ConsoleInput::~ConsoleInput() {
	clearPathsToFiles();
	clearCommands();
	//std::cout << "ConsoleInput::~ConsoleInput()" << std::endl;
}

//
// function that delete the allocated memory
//
void ConsoleInput::clearPathsToFiles() {
	for (int i = 0; i < this->numberFiles; i++) {
		delete[] this->pathsToFiles[i];
	}
	delete[] pathsToFiles;

	this->numberFiles = 0;
}

//
// function that delete the allocated memory
//
void ConsoleInput::clearCommands() {
	for (int i = 0; i < this->numberCommands; i++) {
		delete[] this->commands[i];
	}
	delete[] commands;

	this->numberCommands = 0;
}

//
// function that disgtinguish commands from files
// save the commands in char** commands array
// save the file and their paths in char** pathsToFiles array
//
void ConsoleInput::distinguishConsoleInput(int argc, char* argv[]) {
	int counterCommands = 0;
	int counterFiles = 0;

	for (int i = 1; i < argc; i++) {
		if (isCommand(argv[i])) {
			counterCommands++;
		}
		else {
			counterFiles++;
		}
	}

	this->numberFiles = counterFiles;
	this->numberCommands = counterCommands;

	this->commands = new char*[this->numberCommands];
	this->pathsToFiles = new char*[this->numberFiles];

	int indexCommands = 0;
	int indexFiles = 0;

	for (int i = 1; i < argc; i++) {
		size_t buffSize = strlen(argv[i]) + 1;

		if (isCommand(argv[i])) {
			buffSize -= 2;
			this->commands[indexCommands] = new char[buffSize];
			strcpy_s(this->commands[indexCommands], buffSize, argv[i] + 2);
			indexCommands++;
		}
		else {
			this->pathsToFiles[indexFiles] = new char[buffSize];
			strcpy_s(this->pathsToFiles[indexFiles], buffSize, argv[i]);
			indexFiles++;
		}
	}
}

//
// function that checks is the given argument is a command
//
bool ConsoleInput::isCommand(char* item) {
	assert(item != NULL);

	if (item[0] == '\0' || item[1] == '\0') {
		return false;
	}

	return item[0] == '-' && item[1] == '-';
}

int ConsoleInput::getNumberFiles() const {
	return this->numberFiles;
}

int ConsoleInput::getNumberCommands() const {
	return this->numberCommands;
}

char** ConsoleInput::getPathsToFiles() const {
	return this->pathsToFiles;
}

char** ConsoleInput::getCommands() const {
	return this->commands;
}
