#include "Format.h"

#include <iostream>

Format::Format() {
	//std::cout << "[Entering Format::Format()]" << std::endl;
}

Format::~Format() {
	//std::cout << "[Entering Format::~Format()]" << std::endl;
}

void Format::processCommand(TextManager& text) {
	std::cout << "processFormat on file " << text.getFileName() << std::endl;
	
	formatText(text);
}

void Format::formatText(TextManager& text) {
	char** source = text.getFileLines();
	int numLines = text.getNumberLines();
	int currLineLen = 0;
	for (int i = 0; i < text.getNumberLines(); i++) {
		currLineLen = strlen(text.getFileLines()[i]);
		if (hasEndLine(text.getFileLines()[i], currLineLen)) {

			int startLine = 0;
			//int endLine = findEndLine(source[i], currLineLen);
			int endLine = findEndLine(text.getFileLines()[i], strlen(text.getFileLines()[i]));

			//int newLineSize = currLineLen - (endLine - startLine);
			//std::cout << "endLine: " << endLine << std::endl;
			int newLineSize = endLine + 2 + 1;
			char* newLine = new (std::nothrow)char[newLineSize + 1];
			if (newLine == NULL)
				return;

			//makeNewLine(source[i], currLineLen, startLine, endLine, newLine);
			makeNewLine(text.getFileLines()[i], strlen(text.getFileLines()[i]), startLine, endLine, newLine);

			newLine[newLineSize - 2] = '\r';
			newLine[newLineSize - 1] = '\n';
			newLine[newLineSize] = '\0';
		
			// the other part of the line
			//std::cout << "currLine: " << text.getFileLines()[i] << std::endl;
			int startLine_2 = endLine + 1;
			//std::cout << "startLine_2 " << startLine_2 << std::endl;

			int endLine_2 = currLineLen - 1;
			//std::cout << "endLine_2 " << endLine_2 << std::endl;

			int sizeOtherLine = currLineLen - newLineSize + 2;
			char* otherPartLine = new (std::nothrow)char[sizeOtherLine + 1];
			if (otherPartLine == NULL)
				return;
			//std::cout << "sizeOtherLine " << sizeOtherLine << std::endl;
			//strcpy_s(otherPartLine, sizeOtherLine + 1, text.getFileLines()[i] + endLine);
			makeNewLine(text.getFileLines()[i], strlen(text.getFileLines()[i]), startLine_2, endLine_2, otherPartLine);
			otherPartLine[sizeOtherLine] = '\0';

			//std::cout << "newLine: " << newLine << std::endl;
			//std::cout << "otherPartLine: " << otherPartLine << std::endl;
			text.insertLine(otherPartLine, i + 1);
			text.setLine(newLine, i);
		}
	}
}

int Format::findEndLine(char* line, int currLineLen) {
	for (int i = 0; i < currLineLen; i++) {
		if (line[i] == ';') {
			return i;
		}
	}
}

bool Format::hasEndLine(char* line, int currLineLen) {
	for (int i = 0; i < currLineLen; i++) {
		if (line[i] == ';') {
			return true;
		}
	}
	return false;
}


void Format::makeNewLine(char* line, int currLineLen, int startLine, int endLine, char* newLine) {
	int indx = 0;
	for (int j = startLine; j < endLine; j++) {
		newLine[indx] = line[j];
		indx++;
	}
	newLine[indx] = line[endLine];
}