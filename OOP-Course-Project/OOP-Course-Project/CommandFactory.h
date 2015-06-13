#pragma once

#include "ConsoleInput.h"
#include "TextManager.h"

#include "Comments.h"
#include "NewLines.h"
#include "Indentation.h"
#include "Format.h"
#include "Html.h"

//
// class that creates commands from the given console input
// it store the instance of commands in an array
//
class CommandFactory {
public:
	CommandFactory();

	// CTOR that takes the commands from the console
	// and makes instances of these commands
	CommandFactory(char** arrCommands, int sizeArrCommands);

	~CommandFactory();
public:
	void createCommands(char* nameCommand, int);
	const int getNumberCommands() const;

	Command** getCommands() const;
private:
	void clearCommands();
private:
	// array of commands objects
	Command** commands;
	
	// save the current number of commands
	int numberCommands;
};