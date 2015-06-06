#include "Comments.h"

#include <iostream>

Comments::Comments() {
	std::cout << "[Entering Comments::Comments()]" << std::endl;
}

Comments::~Comments() {
	std::cout << "[Entering Comments::~Comments()]" << std::endl;
}

void Comments::processCommand(TextManager& text) {
	std::cout << "processComments on file " << text.getFileName() << std::endl;
}