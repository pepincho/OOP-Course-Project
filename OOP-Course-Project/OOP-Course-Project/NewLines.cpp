#include "NewLines.h"

#include <iostream>

NewLines::NewLines() {
	std::cout << "[Entering NewLines::NewLines()]" << std::endl;
}

NewLines::NewLines(bool newLinesStyle) {
	std::cout << "[Entering NewLines::NewLines(bool newLinesStyle)]" << std::endl;
	this->newLinesStyle = newLinesStyle;
}

NewLines::~NewLines() {
	std::cout << "[Entering NewLines::~NewLines()]" << std::endl;
}

void NewLines::processCommand(TextManager& text) {
	std::cout << "processNewLines on file " << text.getFileName() << std::endl;
	changeStyle(text);
}

void NewLines::changeStyle(TextManager& text) {
	char** source = (char**) text.getFileLines();
	int numberLines = text.getNumberLines();
	std::cout << "style: " << this->newLinesStyle << std::endl;
	for (int i = 0; i < numberLines; i++) {
		int currLineLen = strlen(source[i]);
		//
		// 
		//
		if (this->newLinesStyle == 0) {
			for (int j = 0; j < currLineLen - 1; j++) {
				if (source[i][j] == '\r' && source[i][j + 1] == '\n') {
					continue;
				}
				//else {
				else if ((source[i][j] != '\r' && source[i][j + 1] == '\n')) {
					//std::cout << "tuke sme" << std::endl;
					char* newLine = new (std::nothrow) char[currLineLen + 1 + 1];
					if (newLine == NULL)
						return;
					for (int k = 0; k < currLineLen - 1; k++) {
						newLine[k] = source[i][k];
					}
					newLine[currLineLen - 1] = '\r';
					newLine[currLineLen] = '\n';
					newLine[currLineLen + 1] = '\0';
					text.setLine(newLine, i);
				}
			}
			if (source[i][0] == '\n') {
				char* newLine = new (std::nothrow) char[currLineLen + 1 + 1];
				if (newLine == NULL)
					return;
				for (int k = 0; k < currLineLen - 1; k++) {
					newLine[k] = source[i][k];
				}
				newLine[currLineLen - 1] = '\r';
				newLine[currLineLen] = '\n';
				newLine[currLineLen + 1] = '\0';
				text.setLine(newLine, i);
			}
		}
		else {
			//std::cout << "tak Size len: " << currLineLen << std::endl;
			for (int j = 0; j < currLineLen - 1; j++) {
				if (source[i][j] != '\r' && source[i][j + 1] == '\n') {
					//std::cout << "tuka li sum " << std::endl;

					continue;
				}
				//else {
				else if (source[i][j] == '\r' && source[i][j + 1] == '\n') {
					//std::cout << "epa tuk sum " << std::endl;

					char* newLine = new (std::nothrow) char[currLineLen - 1 + 1];
					if (newLine == NULL)
						return;
					for (int k = 0; k < currLineLen - 1 - 1; k++) {
						newLine[k] = source[i][k];
					}
					newLine[currLineLen - 1 - 1] = '\n';
					newLine[currLineLen - 1] = '\0';
					//std::cout << "Size len: " << strlen(newLine) << std::endl;
					text.setLine(newLine, i);
				}
			}
		}
	}
}
