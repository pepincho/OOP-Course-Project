#pragma once

#include "ConsoleInput.h"
#include "TextManager.h"

#include "Comments.h"
#include "NewLines.h"
#include "Identation.h"
#include "Format.h"
#include "Html.h"


class CommandFactory {
public:
	CommandFactory();
	CommandFactory(const char** arrCommands, int sizeArrCommands);
	~CommandFactory();
public:
	void createCommands(const char* nameCommand, int);
	const int getNumberCommands() const;

	Command** getCommands() const;

	//const Command* getCommand(int) const;
	//const Command& operator[](int index) const;
private:
	void clearCommands();
private:
	Command** commands;
	int numberCommands;
};