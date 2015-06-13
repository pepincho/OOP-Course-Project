#include "NewLines.h"

#include <iostream>

NewLines::NewLines() {
	//std::cout << "[Entering NewLines::NewLines()]" << std::endl;
}

NewLines::NewLines(bool newLinesStyle) {
	//std::cout << "[Entering NewLines::NewLines(bool newLinesStyle)]" << std::endl;
	this->newLinesStyle = newLinesStyle;
}

NewLines::~NewLines() {
	//std::cout << "[Entering NewLines::~NewLines()]" << std::endl;
}

void NewLines::processCommand(TextManager& text) {
	std::cout << "processNewLines on file " << text.getFileName() << std::endl;
	changeStyle(text);
}

//
// function that changes the style in the given .cpp file
// it takes a TextManager instance of the .cpp file
//
void NewLines::changeStyle(TextManager& text) {
	char** source = (char**)text.getFileLines();
	int numberLines = text.getNumberLines();

	for (int i = 0; i < numberLines; i++) {
		int currLineLen = strlen(source[i]);
		
		// check which is the preferable style (CRLF)
		if (this->newLinesStyle == 0) {
			for (int j = 0; j < currLineLen - 1; j++) {

				if (source[i][j] == '\r' && source[i][j + 1] == '\n') {
					continue;
				}

				else if ((source[i][j] != '\r' && source[i][j + 1] == '\n')) {
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

		// if the preferable style is the other one (LF)
		// we come here
		else {
			for (int j = 0; j < currLineLen - 1; j++) {
				if (source[i][j] != '\r' && source[i][j + 1] == '\n') {
					continue;
				}
				else if (source[i][j] == '\r' && source[i][j + 1] == '\n') {
					char* newLine = new (std::nothrow) char[currLineLen - 1 + 1];
					if (newLine == NULL)
						return;

					for (int k = 0; k < currLineLen - 1 - 1; k++) {
						newLine[k] = source[i][k];
					}

					newLine[currLineLen - 1 - 1] = '\n';
					newLine[currLineLen - 1] = '\0';
					text.setLine(newLine, i);
				}
			}
		}
	}
}
