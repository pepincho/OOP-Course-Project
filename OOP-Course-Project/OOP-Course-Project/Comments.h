#pragma once

#include "Command.h"
#include "TextManager.h"

class Comments : public Command {
public:
	Comments();
	virtual ~Comments();

	virtual void processCommand(TextManager& text);
};