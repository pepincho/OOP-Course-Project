#include "Indentation.h"

#include <iostream>

Indentation::Indentation() {
	//std::cout << "[Entering Indentation::Indentation()]" << std::endl;
}

Indentation::Indentation(bool identationStyle) {
	//std::cout << "[Entering Indentation::Indentation(bool identationStyle)]" << std::endl;
	this->identationStyle = identationStyle;
}

Indentation::~Indentation() {
	//std::cout << "[Entering Indentation::~Indentation()]" << std::endl;
}

void Indentation::processCommand(TextManager& text) {
	std::cout << "processIdentation on file " << text.getFileName() << std::endl;

	changeStyle(text);
}

//
// function that changes the style in the given .cpp file
// it takes a TextManager instance of the .cpp file
//
void Indentation::changeStyle(TextManager& text) {
	char** source = text.getFileLines();
	int numberLines = text.getNumberLines();

	for (int i = 0; i < numberLines; i++) {
		int currLineLen = strlen(source[i]);

		// check which is the preferable style (tabs)
		if (this->identationStyle == 0) {
			for (int j = 0; j < currLineLen; j++) {
				currLineLen = strlen(source[i]);

				// if the current symbol is '\t' we skip this step
				if (source[i][j] == '\t') {
					continue;
				}

				// check are the next four symbols spaces
				// and we replace them with a '\t' symbol
				else if (areNextFourSpaces(source[i], j) == true) {
					int sizeNewLine = currLineLen - 1 - 1 - 1 + 1;
					char* newLine = new (std::nothrow) char[sizeNewLine];
					if (newLine == NULL)
						return;

					int currIndx = 0;

					for (int k = currIndx; k < j; k++) {
						newLine[currIndx] = source[i][k];
						currIndx++;
					}

					int temp = currIndx;

					for (int k = j + 3; k < currLineLen; k++) {
						newLine[currIndx] = source[i][k];
						currIndx++;
					}

					newLine[temp] = '\t';
					newLine[sizeNewLine - 1] = '\0';
					text.setLine(newLine, i);
				}
			}
		}
		// if the preferable style is the other one (spaces)
		// we come here
		else {
			for (int j = 0; j < currLineLen; j++) {
				currLineLen = strlen(source[i]);

				// if the next four symbols are spaces we skip this step
				if (areNextFourSpaces(source[i], j) == true) {
					continue;
				}

				// check are the next symbol is '\t'
				// and we replace it with four spaces
				else if (source[i][j] == '\t') {
					int sizeNewLine = currLineLen + 1 + 1 + 1 + 1;
					char* newLine = new (std::nothrow) char[sizeNewLine];
					if (newLine == NULL)
						return;

					int currIndx = 0;

					for (int k = 0; k < j; k++) {
						newLine[k] = source[i][k];
						currIndx++;
					}

					int temp = currIndx;
					newLine[currIndx] = ' ';
					currIndx++;
					newLine[currIndx] = ' ';
					currIndx++;
					newLine[currIndx] = ' ';
					currIndx++;
					newLine[currIndx] = ' ';
					currIndx++;

					for (int k = j + 1; k < currLineLen; k++) {
						newLine[currIndx] = source[i][k];
						currIndx++;
					}

					newLine[sizeNewLine - 1] = '\0';
					text.setLine(newLine, i);
				}
			}
		}
	}
}

//
// function that checks are the next four symbols spaces
//
bool Indentation::areNextFourSpaces(char* line, int startPos) {
	if (line[startPos] == ' ' && line[startPos + 1] == ' ' && line[startPos + 2] == ' ' && line[startPos + 3] == ' ') {
		return true;
	}
	else {
		return false;
	}
}
