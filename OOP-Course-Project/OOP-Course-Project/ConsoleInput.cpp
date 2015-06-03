#include "ConsoleInput.h"

#include <iostream>

ConsoleInput::ConsoleInput() {
	this->numberFiles = 0;
	this->numberCommands = 0;
	this->pathsToFiles = NULL;
	this->commands = NULL;
	std::cout << "ConsoleInput::ConsoleInput()" << std::endl;
}

ConsoleInput::~ConsoleInput() {
	clearPathsToFiles(this->pathsToFiles, this->numberFiles);
	clearCommands(this->commands, this->numberCommands);
	this->numberFiles = 0;
	this->numberCommands = 0;
	std::cout << "ConsoleInput::~ConsoleInput()" << std::endl;
}

void ConsoleInput::clearPathsToFiles(char** files, int sizeFiles) {
	for (int i = 0; i < sizeFiles; i++) {
		delete[] files[i];
	}
	delete[] files;
}

void ConsoleInput::clearCommands(char** commands, int sizeCommands) {
	for (int i = 0; i < sizeCommands; i++) {
		delete[] commands[i];
	}
	delete[] commands;
}

//void ConsoleInput::addPathsToFiles(char** paths, int sizePaths) {
//	this->numberFiles = sizePaths;
//	
//	this->pathsToFiles = new (std::nothrow) char*[sizePaths];
//
//	if (pathsToFiles == NULL) {
//		return;
//	}
//
//	for (int i = 0; i < sizePaths; i++) {
//		int currentPathSize = strlen(paths[i]);
//		this->pathsToFiles[i] = new (std::nothrow) char[currentPathSize + 1];
//		// if (pathsToFiles[i] == NULL) {
//		if (pathsToFiles == NULL) {
//			return;
//		}
//		strcpy(this->pathsToFiles[i], paths[i]);
//		this->pathsToFiles[currentPathSize] = '\0';
//	}
//}
//
//void ConsoleInput::addCommands(char** commands, int sizeCommands) {
//	this->numberCommands = sizeCommands;
//
//	this->commands = new (std::nothrow) char*[sizeCommands];
//
//	if (commands == NULL) {
//		return;
//	}
//
//	for (int i = 0; i < sizeCommands; i++) {
//		int currentCommandSize = strlen(commands[i]);
//		this->commands[i] = new (std::nothrow) char[currentCommandSize + 1];
//		// if (commands[i] == NULL) {
//		if (commands == NULL) {
//			return;
//		}
//		strcpy(this->commands[i], commands[i]);
//		this->commands[currentCommandSize] = '\0';
//	}
//}

void ConsoleInput::distinguishConsoleInput(int argc, char* argv[]) {
	char** commands;
	char** pathFiles;

	int counterCommands = 0;
	int counterFiles = 0;

	for (int i = 0; i < argc; i++) {
		if (isCommand(i, argv[i])) {
			counterCommands++;
		}
		else {
			if (i == 0) {
				continue;
			}
			counterFiles++;
		}
	}

	commands = new (std::nothrow) char*[counterCommands];
	pathFiles = new (std::nothrow) char*[counterFiles];

	int indexCommands = 0;
	int indexFiles = 0;

	for (int i = 0; i < argc; i++) {
		if (isCommand(i, argv[i])) {
			commands[indexCommands] = new (std::nothrow) char[strlen(argv[i]) - 2];
			//strcpy(commands[indexCommands], argv[i]);
			copyCommand(commands[indexCommands], argv[i]);
			//commands[strlen(argv[i])] = "\0";
			indexCommands++;
		}
		else {
			if (i == 0) {
				continue;
			}
			pathFiles[indexFiles] = new (std::nothrow) char[strlen(argv[i])];
			strcpy(pathFiles[indexFiles], argv[i]);
			pathFiles[strlen(argv[i])] = "\0";
			indexFiles++;
		}
	}

	setNumberFiles(counterFiles);

	//std::cout << "---------------------------------" << std::endl;

	//std::cout << "There are " << counterCommands << " commands." << std::endl;
	//std::cout << "Commands are:" << std::endl;

	//for (int i = 0; i < counterCommands; i++) {
	//	std::cout << commands[i] << " is a command!" << std::endl;
	//}

	//std::cout << "---------------------------------" << std::endl;

	//std::cout << "There are " << counterFiles << " files." << std::endl;
	//std::cout << "Files are:" << std::endl;

	//for (int i = 0; i < counterFiles; i++) {
	//	std::cout << pathFiles[i] << " is a file!" << std::endl;
	//}
}

bool ConsoleInput::isCommand(int index, char* item) {
	if (item[0] == '-' && item[1] == '-') {
		return true;
	}
	else {
		return false;
	}
}

void ConsoleInput::copyCommand(char* destinationStr, const char* sourceStr) {
	int i = 2;
	int j = 0;

	while (sourceStr[i] != '\0') {
		destinationStr[j] = sourceStr[i];
		i++;
		j++;
	}
	destinationStr[j] = '\0';
}

void ConsoleInput::setNumberFiles(int sizeFiles) {
	this->numberFiles = sizeFiles;
}

const int ConsoleInput::getNumberFiles() {
	return this->numberFiles;
}
