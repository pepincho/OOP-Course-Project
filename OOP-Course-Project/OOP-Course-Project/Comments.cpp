#include "Comments.h"

#include <iostream>

Comments::Comments() {
	//std::cout << "[Entering Comments::Comments()]" << std::endl;
}

Comments::~Comments() {
	//std::cout << "[Entering Comments::~Comments()]" << std::endl;
}

void Comments::processCommand(TextManager& text) {
	std::cout << "processComments on file " << text.getFileName() << std::endl;
	removeComment(text);
	removeMultiLineComment(text);
}

void Comments::removeComment(TextManager& text) {
	char** source = text.getFileLines();
	int numLines = text.getNumberLines();

	for (int i = 0; i < numLines; i++) {
		int currLineLen = strlen(source[i]);
		if (hasComment(source[i], currLineLen) == false) {
			continue;
		}

		int startComment = findStartComment(source[i], currLineLen);
		int endComment = findEndComment(source[i], currLineLen);

		int newLineSize = currLineLen - (endComment - startComment);
		char* newLine = new (std::nothrow)char[newLineSize + 1];
		if (newLine == NULL)
			return;

		makeNewLine(source[i], currLineLen, startComment, endComment, newLine);
		newLine[newLineSize] = '\0';
		text.setLine(newLine, i);
	}
}

bool Comments::hasComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '/') {
			return true;
		}
	}
	return false;
}

int Comments::findStartComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '/') {
			return i;
		}
	}
}

int Comments::findEndComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if ((line[i] == '\r' && line[i + 1] == '\n')) {
			return i;
		}
		else if (line[i + 1] == '\n') {
			return i + 1;
		}
	}
}

void Comments::makeNewLine(char* line, int currLineLen, int startComment, int endComment, char* newLine) {
	bool isInComm = false;
	int indx = 0;
	for (int j = 0; j < currLineLen; j++) {
		if (j == startComment) {
			isInComm = true;
			continue;
		}
		if (j == endComment) {
			isInComm = false;
			newLine[indx] = line[j];
			indx++;
			continue;
		}
		if (isInComm == false) {
			newLine[indx] = line[j];
			indx++;
		}
	}
}

void Comments::removeMultiLineComment(TextManager& text) {
	//std::cout << "In removeMultiLineComments" << std::endl;
	char** source = text.getFileLines();
	int numLines = text.getNumberLines();
	bool isInComment = false;

	int currIndex = 0;
	for (int i = 0; i < numLines; i++) {
		//std::cout << "on line: " << source[i] << std::endl;
		int currLineLen = strlen(source[currIndex]);

		if (hasOpeningComment(source[currIndex], strlen(source[currIndex])) == true) {
			currLineLen = strlen(source[currIndex]);

			int startColumnComment = findStartMultiLineComment(source[currIndex], currLineLen);
			int endColumnComment = findEndMultiLineComment(source[currIndex], currLineLen);

			int sizeCurrNewLine = currLineLen - (endColumnComment - startColumnComment);

			char* currNewLine = new (std::nothrow) char[sizeCurrNewLine + 1];
			if (currNewLine == NULL)
				return;

			//std::cout << "endColumnComment: " << source[currIndex][endColumnComment] << std::endl;
			makeNewLine(source[currIndex], currLineLen, startColumnComment, endColumnComment, currNewLine);
			//std::cout << "newLine: " << currNewLine << std::endl;
			currNewLine[sizeCurrNewLine] = '\0';
			text.setLine(currNewLine, currIndex);

			isInComment = true;
			currIndex++;
			continue;
		}
		else if (hasClosingComment(source[currIndex], strlen(source[currIndex])) == true) {
			currLineLen = strlen(source[currIndex]);

			int endColumnComment = findEndMultiLineComment(source[currIndex], currLineLen);
			int sizeCurrNewLine = currLineLen - endColumnComment - 1;

			char* currNewLine = new (std::nothrow) char[sizeCurrNewLine + 1];
			if (currNewLine == NULL)
				return;
			//std::cout << "endColumnComment: " << source[currIndex][endColumnComment + 1] << std::endl;
			makeNewLine(source[currIndex], currLineLen, 0, endColumnComment + 1, currNewLine);

			currNewLine[sizeCurrNewLine] = '\0';
			text.setLine(currNewLine, currIndex);

			currIndex++;
			isInComment = false;
			continue;
		}
		else if (isInComment == true) {
			text.removeLine(currIndex);
		}
		else {
			currIndex++;
		}
	}
}

int Comments::findStartMultiLineComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '*') {
			return i;
		}
	}
}

int Comments::findEndMultiLineComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '*' && line[i + 1] == '/') {
			if (i + 1 == lineLen - 1) {
				return i + 2;
			}
			if (findStartMultiLineComment(line, lineLen) == false) {
				return i + 2;
			}
			return i + 1;
		}
	}
	for (int i = 0; i < lineLen - 1; i++) {
		if ((line[i] == '\r' && line[i + 1] == '\n')) {
			return i;
		}
		else if (line[i + 1] == '\n') {
			return i + 1;
		}
	}
}

bool Comments::hasMultiLineComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '*') {
			return true;
		}
	}
	return false;
}

bool Comments::hasOpeningComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '*') {
			return true;
		}
	}
	return false;
}

bool Comments::hasClosingComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '*' && line[i + 1] == '/') {
			return true;
		}
	}
	return false;
}