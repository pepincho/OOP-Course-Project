#include "NewLines.h"

#include <iostream>

NewLines::NewLines() {
	std::cout << "[Entering NewLines::NewLines()]" << std::endl;
}

NewLines::~NewLines() {
	std::cout << "[Entering NewLines::~NewLines()]" << std::endl;
}

void NewLines::processCommand(TextManager& text) {
	std::cout << "processNewLines on file " << text.getFileName() << std::endl;
}