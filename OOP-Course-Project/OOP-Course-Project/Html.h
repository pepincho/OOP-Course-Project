#pragma once

#include "Command.h"
#include "TextManager.h"

//
// html class that represent a html command
// inherit the base abstract command class
//
class Html : public Command {
public:
	Html();
	virtual ~Html();

	virtual void processCommand(TextManager& text);
	//
	// 1) commets will be in green color
	// 2) reserved keywords in C++ wil bee in blue color
	// 3) strings will be in red color
	// 4) preprocessor directives will be in yellow color
	// 4) numbers will be in black color
	// 5) character literals will be in pink color
	//
private:
	char* makeInitialHtmlFile();

	bool isLineDirective(char* line);
	bool hasComment(char*, int);

	//
	int countWords(const char* str);
	void toWords(const char *sentence, char **word);
	bool isAlphaNum(char c);
public:
	void generateHtmlFile(TextManager& text);
};