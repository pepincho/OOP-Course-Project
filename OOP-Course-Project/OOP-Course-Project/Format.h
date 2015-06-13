#pragma once

#include "Command.h"
#include "TextManager.h"

class Format : public Command {
public:
	Format();
	virtual ~Format();

	virtual void processCommand(TextManager& text);
private:
	void formatText(TextManager& text);


	void makeNewLine(char* line, int currLineLen, int startLine, int endLine, char* newLine);

	int findEndLine(char*, int);
	bool hasEndLine(char* line, int currLineLen);
};