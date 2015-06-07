#include "CommandFactory.h"

#include <iostream>
#include <cstring>

CommandFactory::CommandFactory() {
	std::cout << "[Entering CommandFactory::CommandFactory()]" << std::endl;
}

CommandFactory::~CommandFactory() {
	std::cout << "[Entering CommandFactory::~CommandFactory()]" << std::endl;
	clearCommands();
}

void CommandFactory::clearCommands() {
	for (int i = 0; i < this->numberCommands; i++) {
		delete[] this->commands[i];
	}
	delete[] commands;
}

CommandFactory::CommandFactory(const char** arrCommands, int sizeArrCommands) {
	std::cout << "[Entering CommandFactory::CommandFactory(const char** arrCommands, int sizeArrCommands)]" << std::endl;
	this->numberCommands = sizeArrCommands;
	this->commands = new (std::nothrow) Command*[this->numberCommands];

	for (int i = 0; i < sizeArrCommands; i++) {
		createCommands(arrCommands[i], i);
	}
}

void CommandFactory::createCommands(const char* nameCommand, int indx) {
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
	else if (strcmp(nameCommand, "identation=tabs") == 0) {
		bool style = 0;
		this->commands[indx] = new Identation(style);
		return;
	}
	else if (strcmp(nameCommand, "identation=spaces") == 0) {
		bool style = 1;
		this->commands[indx] = new Identation(style);
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
	//else {
	//	throw std::exception("Wrong command");
	//}
}

const int CommandFactory::getNumberCommands() const {
	return (const int) this->numberCommands;
}

//const Command* CommandFactory::getCommand(int indx) const {
//	return this->commands[indx];
//}

//const Command& CommandFactory::operator[](int index) const {
//	return this->commands[index];
//}

Command** CommandFactory::getCommands() const {
	return (Command**) this->commands;
}