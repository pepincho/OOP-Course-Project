#pragma once

#include "TextManager.h"

//
// base abstract class that represent a command
//
class Command {
public:
	Command();
	virtual ~Command();

	virtual void processCommand(TextManager& text) = 0;
};