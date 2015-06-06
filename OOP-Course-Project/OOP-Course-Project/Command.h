#pragma once

#include "TextManager.h"

class Command {
public:
	Command();
	virtual ~Command();

	virtual void processCommand(TextManager& text) = 0;
};