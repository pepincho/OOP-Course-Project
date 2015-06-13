#pragma once

#include "Command.h"
#include "TextManager.h"

//
// format class that represent a format command
// inherit the base abstract command class
//
class Format : public Command {
public:
	Format();
	virtual ~Format();

	virtual void processCommand(TextManager& text);
private:
	void formatText(TextManager& text);


	void makeNewLine(char* line, int currLineLen, int startLine, int endLine, char* newLine);

	void makeNewLine(char* line, int currLineLen, int startLine, int endLine, char* newLine, int counterIndentation);


	int findEndLine(char*, int);
	bool hasEndLine(char* line, int currLineLen);

	bool hasOpeningBracket(char* line, int currLineLen);
	bool hasClosingBracket(char* line, int currLineLen);

	int findOpeningBracket(char* line, int currLineLen);
	int findClosingBracket(char* line, int currLineLen);
};