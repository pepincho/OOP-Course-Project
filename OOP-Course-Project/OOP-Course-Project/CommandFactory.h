#pragma once

#include "ConsoleInput.h"
#include "TextManager.h"

#include "Comments.h"
#include "NewLines.h"
#include "Indentation.h"
#include "Format.h"
#include "Html.h"

class CommandFactory {
public:
	CommandFactory();
	CommandFactory(char** arrCommands, int sizeArrCommands);
	~CommandFactory();
public:
	void createCommands(char* nameCommand, int);
	const int getNumberCommands() const;

	Command** getCommands() const;
private:
	void clearCommands();
private:
	Command** commands;
	int numberCommands;
};