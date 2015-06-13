#include "CommandFactory.h"

#include <iostream>
#include <cstring>

CommandFactory::CommandFactory() {
	//std::cout << "[Entering CommandFactory::CommandFactory()]" << std::endl;
}

CommandFactory::~CommandFactory() {
	//std::cout << "[Entering CommandFactory::~CommandFactory()]" << std::endl;
	clearCommands();
}

//
// function that delete all command objects
//
void CommandFactory::clearCommands() {
	for (int i = 0; i < this->numberCommands; i++) {
		delete[] this->commands[i];
	}
	delete[] commands;
}

CommandFactory::CommandFactory(char** arrCommands, int sizeArrCommands) {
	//std::cout << "[Entering CommandFactory::CommandFactory(const char** arrCommands, int sizeArrCommands)]" << std::endl;
	this->numberCommands = sizeArrCommands;
	this->commands = new (std::nothrow) Command*[this->numberCommands];

	for (int i = 0; i < sizeArrCommands; i++) {
		createCommands(arrCommands[i], i);
	}
}

//
// function that creates command objects
// if there is a wrong command it throws an exceptions
//
void CommandFactory::createCommands(char* nameCommand, int indx) {
	if (strcmp(nameCommand, "comments") == 0) {
		this->commands[indx] = new Comments();
		return;
	}
	else if (strcmp(nameCommand, "newlines=CRLF") == 0) {
		bool style = 0;
		this->commands[indx] = new NewLines(style);
		return;
	}
	else if (strcmp(nameCommand, "newlines=LF") == 0) {
		bool style = 1;
		this->commands[indx] = new NewLines(style);
		return;
	}
	else if (strcmp(nameCommand, "indentation=tabs") == 0) {
		bool style = 0;
		this->commands[indx] = new Indentation(style);
		return;
	}
	else if (strcmp(nameCommand, "indentation=spaces") == 0) {
		bool style = 1;
		this->commands[indx] = new Indentation(style);
		return;
	}
	else if (strcmp(nameCommand, "format") == 0) {
		this->commands[indx] = new Format();
		return;
	}
	else if (strcmp(nameCommand, "html") == 0) {
		this->commands[indx] = new Html();
		return;
	}
	else {
		char message[130];
		sprintf_s(message, 130, "Unknown command \"%s\"", nameCommand);
		throw std::exception(message);
	}
}

const int CommandFactory::getNumberCommands() const {
	return (const int) this->numberCommands;
}

Command** CommandFactory::getCommands() const {
	return (Command**) this->commands;
}