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
	removeComment(text);
}

void Comments::removeComment(TextManager& text) {
	char** source = (char**)text.getFileLines();
	int numLines = text.getNumberLines();
	
	for (int i = 0; i < numLines; i++) {
		int currLineLen = strlen(source[i]);
		//std::cout << "currLineLen: " << currLineLen << std::endl;
		if (hasComment(source[i], currLineLen) == false) {
			continue;
		}

		int startComment = findStartComment(source[i], currLineLen);
		//std::cout << "startComment: " << startComment << std::endl;
		int endComment = findEndComment(source[i], currLineLen);
		//std::cout << "endComment: " << endComment << std::endl;

		//std::cout << "currLineLen - (endComment - startComment)" << newLineSize << std::endl;
		int newLineSize = currLineLen - (endComment - startComment);

		char* newLine = new (std::nothrow)char[newLineSize + 1];
		if (newLine == NULL)
			return;

		makeNewLine(source[i], currLineLen, startComment, endComment, newLine, newLineSize);
		newLine[newLineSize - 1] = '\0';
		text.setLine(newLine, i);
	}
}

int Comments::findStartComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen; i++) {
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

	//for (int i = 0; i < lineLen; i++) {
	//	if (line[i] == '\n') {
	//		return i;
	//	}
	//}
}

void Comments::makeNewLine(char* line, int currLineLen, int startComment, int endComment, char* newLine, int newLineSize) {
	bool isInComm = false;
	int indx = 0;
	for (int j = 0; j < currLineLen; j++) {
		if (j == startComment) {
			isInComm = true;
			continue;
		}
		if (j == endComment) {
			isInComm = false;
			continue;
		}
		if (isInComm == false) {
			newLine[indx] = line[j];
			indx++;
		}
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