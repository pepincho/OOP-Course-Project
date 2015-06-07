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
	void changeStyle(TextManager& text);

	// 0 -> with \r\n CRLF
	// 1 -> with \n LF
	bool newLinesStyle;
}; 