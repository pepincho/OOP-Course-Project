#pragma once

#include "Command.h"
#include "TextManager.h"

class Indentation : public Command {
public:
	Indentation();
	Indentation(bool);
	virtual ~Indentation();

	virtual void processCommand(TextManager& text);
private:
	// 0 -> with tabs
	// 1 -> with spaces
	bool identationStyle;

	void changeStyle(TextManager& text);

	bool areNextFourSpaces(char*, int);
};