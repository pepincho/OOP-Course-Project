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

	changeStyle(text);
}

void Identation::changeStyle(TextManager& text) {
	char** source = (char**)text.getFileLines();
	int numberLines = text.getNumberLines();
	std::cout << "style: " << this->identationStyle << std::endl;
	for (int i = 0; i < numberLines; i++) {
		int currLineLen = strlen(source[i]);
		//
		//
		if (this->identationStyle == 0) {
			for (int j = 0; j < currLineLen; j++) {
				//std::cout << "<------>currLine: " << source[i] << std::endl;
				if (source[i][j] == '\t') {
					continue;
				}
				//else {
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
					int bam = currIndx;
					for (int k = j + 3; k < currLineLen; k++) {
						newLine[currIndx] = source[i][k];
						currIndx++;
					}
					newLine[bam] = '\t';
					newLine[sizeNewLine - 1] = '\0';
					text.setLine(newLine, i);
					//setLine(source, newLine, i);
					//j += 2;
				}
			}
		}
	}
}

bool Identation::areNextFourSpaces(char* line, int startPos) {
	if (line[startPos] == ' ' && line[startPos + 1] == ' ' && line[startPos + 2] == ' ' && line[startPos + 3] == ' ') {
		return true;
	}
	else {
		return false;
	}
}


void Identation::setLine(char** sourceLines, char* newLine, int atRow) {
	sourceLines[atRow] = new (std::nothrow) char[strlen(newLine) + 1];
	strcpy_s(sourceLines[atRow], strlen(newLine) + 1, newLine);
}