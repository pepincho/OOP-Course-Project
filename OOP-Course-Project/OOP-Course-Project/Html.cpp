#include "Html.h"

#include <iostream>

Html::Html() {
	std::cout << "[Entering Html::Html()]" << std::endl;
}

Html::~Html() {
	std::cout << "[Entering Html::~Html()]" << std::endl;
}

void Html::processCommand(TextManager& text) {
	std::cout << "processHtml on file " << text.getFileName() << std::endl;
}