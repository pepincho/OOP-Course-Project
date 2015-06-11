#pragma once

#include "Command.h"
#include "TextManager.h"

class Comments : public Command {
public:
	Comments();
	virtual ~Comments();

	virtual void processCommand(TextManager& text);
private:
	// remove single-line comment -> // style
	void removeComment(TextManager& text);

	// remove multi-line comment -> /* */ style
	void removeMultiLineComment(TextManager& text);

	void makeNewLine(char* line, int currLineLen, int startComment, int endComment, char* newLine);

	int findStartComment(char*, int);
	int findEndComment(char*, int);
	
	bool hasComment(char*, int);

	bool hasOpeningComment(char*, int);
	bool hasClosingComment(char*, int);

	int findStartMultiLineComment(char*, int);
	int findEndMultiLineComment(char*, int);

	bool hasMultiLineComment(char*, int);
};