#include "Format.h"

#include <iostream>

Format::Format() {
	std::cout << "[Entering Format::Format()]" << std::endl;
}

Format::~Format() {
	std::cout << "[Entering Format::~Format()]" << std::endl;
}

void Format::processCommand(TextManager& text) {
	std::cout << "processFormat on file " << text.getFileName() << std::endl;
}