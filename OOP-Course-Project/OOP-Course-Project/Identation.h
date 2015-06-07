#pragma once

#include "Command.h"
#include "TextManager.h"

class Identation : public Command {
public:
	Identation();
	Identation(bool);
	virtual ~Identation();

	virtual void processCommand(TextManager& text);
private:
	// 0 -> with tabs
	// 1 -> with spaces
	bool identationStyle;

	void changeStyle(TextManager& text);

	bool areNextFourSpaces(char*, int);


	void setLine(char**, char*, int);

};