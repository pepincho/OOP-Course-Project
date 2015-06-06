#pragma once

#include "Command.h"
#include "TextManager.h"

class Identation : public Command {
public:
	Identation();
	virtual ~Identation();

	virtual void processCommand(TextManager& text);
};