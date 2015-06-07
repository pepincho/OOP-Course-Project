#pragma once

#include "Command.h"
#include "TextManager.h"

class Comments : public Command {
public:
	Comments();
	virtual ~Comments();

	virtual void processCommand(TextManager& text);
private:
	void removeComment(TextManager& text);

	void makeNewLine(char* line, int currLineLen, int startComment, int endComment, char* newLine, int newLineSize);

	int findStartComment(char*, int);
	int findEndComment(char*, int);

	bool hasComment(char*, int);
};