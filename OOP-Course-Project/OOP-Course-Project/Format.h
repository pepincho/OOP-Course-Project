#pragma once

#include "Command.h"
#include "TextManager.h"

class Format : public Command {
public:
	Format();
	virtual ~Format();

	virtual void processCommand(TextManager& text);
};