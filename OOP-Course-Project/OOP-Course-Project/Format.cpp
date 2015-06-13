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

	for (int i = 0; i < text.getNumberLines(); i++) 
	{
		currLineLen = strlen(text.getFileLines()[i]);
		
		int counterIndentation = 0;

		if (hasEndLine(text.getFileLines()[i], currLineLen)) 
		{
			int startLine = 0;
			//int endLine = findEndLine(source[i], currLineLen);
			int endLine = findEndLine(text.getFileLines()[i], strlen(text.getFileLines()[i]));

			int newLineSize = endLine + 2 + 1;
			char* newLine = new (std::nothrow)char[newLineSize + 1];
			if (newLine == NULL)
				return;

			makeNewLine(text.getFileLines()[i], strlen(text.getFileLines()[i]), startLine, endLine, newLine);

			newLine[newLineSize - 2] = '\r';
			newLine[newLineSize - 1] = '\n';
			newLine[newLineSize] = '\0';
		
			// the other part of the line
			int startLine_2 = endLine + 1;
			int endLine_2 = currLineLen - 1;

			int sizeOtherLine = currLineLen - newLineSize + 2;
			char* otherPartLine = new (std::nothrow)char[sizeOtherLine + 1];
			if (otherPartLine == NULL)
				return;

			makeNewLine(text.getFileLines()[i], strlen(text.getFileLines()[i]), startLine_2, endLine_2, otherPartLine);
			otherPartLine[sizeOtherLine] = '\0';

			text.insertLine(otherPartLine, i + 1);
			text.setLine(newLine, i);
			continue;
		}
		//else if (hasOpeningBracket(text.getFileLines()[i], currLineLen) || hasClosingBracket(text.getFileLines()[i], currLineLen)) 
		//{
		//	std::cout << "here, on line: " << i << std::endl;
		//		
		//	

		//}


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

void Format::makeNewLine(char* line, int currLineLen, int startLine, int endLine, char* newLine, int counterIndentation) {
	int indx = 0;
	for (int i = 0; i < counterIndentation; i++) {
		newLine[i] = '\t';
	}
	
	indx = counterIndentation;
	for (int j = startLine; j < endLine; j++) {
		newLine[indx] = line[j];
		indx++;
	}
	newLine[indx] = line[endLine];
}

int Format::findOpeningBracket(char* line, int currLineLen) {
	for (int i = 0; i < currLineLen; i++) {
		if (line[i] == '{') {
			return i;
		}
	}
}

bool Format::hasOpeningBracket(char* line, int currLineLen) {
	for (int i = 0; i < currLineLen; i++) {
		if (line[i] == '{') {
			return true;
		}
	}
	return false;
}

int Format::findClosingBracket(char* line, int currLineLen) {
	for (int i = 0; i < currLineLen; i++) {
		if (line[i] == '}') {
			return i;
		}
	}
}

bool Format::hasClosingBracket(char* line, int currLineLen) {
	for (int i = 0; i < currLineLen; i++) {
		if (line[i] == '}') {
			return true;
		}
	}
	return false;
}