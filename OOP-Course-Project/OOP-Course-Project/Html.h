#pragma once

#include "Command.h"
#include "TextManager.h"

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
public:
	void generateHtmlFile(TextManager& text);
};