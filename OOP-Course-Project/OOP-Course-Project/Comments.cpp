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
	//removeComment(text);
	//removeMultiLineComment(text);
}

void Comments::removeComment(TextManager& text) {
	char** source = (char**)text.getFileLines();
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

		//makeNewLine(source[i], currLineLen, startComment, endComment, newLine, newLineSize);
		makeNewLine(source[i], currLineLen, startComment, endComment, newLine);
		newLine[newLineSize - 1] = '\0';
		text.setLine(newLine, i);
	}
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

//void Comments::makeNewLine(char* line, int currLineLen, int startComment, int endComment, char* newLine, int newLineSize) {
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

void Comments::removeMultiLineComment(TextManager& text) {
	char** source = (char**)text.getFileLines();
	int numLines = text.getNumberLines();
	bool isInComment = false;
	
	for (int i = 0; i < numLines; i++) {
		int currLineLen = strlen((char*)text.getFileLines()[i]);
		std::cout << "on line: " << source[i] << std::endl;

		if (hasOpeningComment((char*)text.getFileLines()[i], currLineLen) == true) {
			isInComment = true;
			std::cout << "zapochva komentara" << std::endl;
			continue;

			//int startColumnComment = findStartMultiLineComment(source[i], currLineLen);
			//int endColumnComment = findEndMultiLineComment(source[i], currLineLen);
			//std::cout << "startColumnComment: " << startColumnComment << std::endl;
			//std::cout << "endColumnComment: " << endColumnComment << std::endl;

			//int sizeCurrNewLine = currLineLen - (endColumnComment - startColumnComment);

			//char* currNewLine = new (std::nothrow) char[sizeCurrNewLine + 1];
			//if (currNewLine == NULL)
			//	return;

			//makeNewLine(source[i], currLineLen, startColumnComment, endColumnComment - 1, currNewLine);
			////currNewLine[sizeCurrNewLine] = '\0';
			//currNewLine[sizeCurrNewLine - 1] = '\0';
			//text.setLine(currNewLine, i);
		}
		if (hasClosingComment((char*)text.getFileLines()[i], currLineLen) == true) {
			isInComment = false;
			std::cout << "svurshva komentara" << std::endl;
			continue;

			//int startColumnComment = findEndMultiLineComment(source[i], currLineLen);

			//int sizeCurrNewLine = currLineLen - startColumnComment;

			//char* currNewLine = new (std::nothrow) char[sizeCurrNewLine + 1];

			//if (currNewLine == NULL)
			//	return;

			//makeNewLine(source[i], currLineLen, startColumnComment, startColumnComment, currNewLine);
			//currNewLine[sizeCurrNewLine - 1] = '\0';
			//text.setLine(currNewLine, i);

		}
		if (isInComment == true) {
			text.removeLine(i);
			//numLines -= 1;
			std::cout << "v komentara" << std::endl;
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
//int startLine, 
int Comments::findEndMultiLineComment(char* line, int lineLen) {
	//int arr[2];
	//for (int i = startLine; i < numberLines; i++) {
	//	int currLineLen = strlen(lines[i]);
	//	for (int j = 0; j < currLineLen - 1; j++) {
	//		if (lines[i][j] == '*' && lines[i][j + 1] == '/') {
	//			arr[0] = i;
	//			arr[1] = j + 1;
	//			return arr;
	//		}
	//	}
	//}
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '*' && line[i + 1] == '/') {
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