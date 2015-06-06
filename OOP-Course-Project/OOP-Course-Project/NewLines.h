#pragma once

#include "Command.h"
#include "TextManager.h"

class NewLines : public Command {
public:
	NewLines();
	virtual ~NewLines();

	virtual void processCommand(TextManager& text);
};