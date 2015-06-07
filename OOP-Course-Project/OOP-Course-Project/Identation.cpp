#include "Identation.h"

#include <iostream>

Identation::Identation() {
	std::cout << "[Entering Identation::Identation()]" << std::endl;
}

Identation::Identation(bool identationStyle) {
	std::cout << "[Entering Identation::Identation(bool identationStyle)]" << std::endl;
	this->identationStyle = identationStyle;
}

Identation::~Identation() {
	std::cout << "[Entering Identation::~Identation()]" << std::endl;
}

void Identation::processCommand(TextManager& text) {
	std::cout << "processIdentation on file " << text.getFileName() << std::endl;
}