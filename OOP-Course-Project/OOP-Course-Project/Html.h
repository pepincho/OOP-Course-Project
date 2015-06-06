#pragma once

#include "Command.h"
#include "TextManager.h"

class Html : public Command {
public:
	Html();
	virtual ~Html();

	virtual void processCommand(TextManager& text);
};