#pragma once

#include "Command.h"
#include "TextManager.h"

class NewLines : public Command {
public:
	NewLines();
	NewLines(bool);
	virtual ~NewLines();

	virtual void processCommand(TextManager& text);
private:
	// 0 -> with \r\n
	// 1 -> with \n
	bool newLinesStyle;
}; 