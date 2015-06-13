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

	removeEmptyLines(text);
}

//
// function that removes single-line comments from the text in the cpp file
// it takes a TextManager instance and works on the source
//
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

//
// function that checks is there a comment
//
bool Comments::hasComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '/') {
			return true;
		}
	}
	return false;
}

//
// function that find the start column position of a comment on a given line
// it returns the start index of the comment in the given line
//
int Comments::findStartComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '/') {
			return i;
		}
	}
}

//
// function that find the last position of a comment on a given line
// it returns the last index of the comment in the given line
//
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

//
// function that makes a new line from a given source line
//
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

//
// function that removes multi-line comments from the text in the cpp file
// it takes a TextManager instance and works on the source
//
void Comments::removeMultiLineComment(TextManager& text) {
	char** source = text.getFileLines();
	int numLines = text.getNumberLines();

	bool isInComment = false;
	int currIndex = 0;

	for (int i = 0; i < numLines; i++) {
		int currLineLen = strlen(source[currIndex]);

		if (hasOpeningComment(source[currIndex], strlen(source[currIndex])) == true) {
			currLineLen = strlen(source[currIndex]);

			if (hasClosingComment(source[currIndex], strlen(source[currIndex])) == true) {
				isInComment = false;
			}
			else {
				isInComment = true;
			}

			int startColumnComment = findStartMultiLineComment(source[currIndex], currLineLen);
			int endColumnComment = findEndMultiLineComment(source[currIndex], currLineLen);

			int sizeCurrNewLine = currLineLen - (endColumnComment - startColumnComment);
			char* currNewLine = new (std::nothrow) char[sizeCurrNewLine + 1];
			if (currNewLine == NULL)
				return;

			makeNewLine(source[currIndex], currLineLen, startColumnComment, endColumnComment, currNewLine);
			currNewLine[sizeCurrNewLine] = '\0';
			text.setLine(currNewLine, currIndex);

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

			makeNewLine(source[currIndex], currLineLen, 0, endColumnComment + 1, currNewLine);
			currNewLine[sizeCurrNewLine] = '\0';
			text.setLine(currNewLine, currIndex);

			currIndex++;
			isInComment = false;
			continue;
		}
		else if (isInComment == true) {
			text.removeLine(currIndex);
			currIndex++;
			continue;
		}
		else {
			currIndex++;
			continue;
		}
		currIndex++;
	}
}

//
// function that find the start column position of a multi-line comment on a given line
// it returns the start index of the comment in the given line
//
int Comments::findStartMultiLineComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '*') {
			return i;
		}
	}
}

//
// function that find the last position of a multi-line comment on a given line
// it returns the last index of the comment in the given line
//
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

//
// function that checks is there a start of a multi-line comment
//
bool Comments::hasMultiLineComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '*') {
			return true;
		}
	}
	return false;
}

//
// function that checks are there symbols that open the multi-line comment
//
bool Comments::hasOpeningComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '*') {
			return true;
		}
	}
	return false;
}

//
// function that checks are there symbols that close the multi-line comment
//
bool Comments::hasClosingComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '*' && line[i + 1] == '/') {
			return true;
		}
	}
	return false;
}

//
// function that removes empty lines from the source
//
void Comments::removeEmptyLines(TextManager& text) {
	char** source = text.getFileLines();
	int numLines = text.getNumberLines();

	for (int i = 0; i < text.getNumberLines(); i++) {
		if (text.getFileLines()[i][0] == '\r' && text.getFileLines()[i][1] == '\n') {
			text.removeLineTEST(i);
			i--;
		}
		else if (text.getFileLines()[i][0] == '\n') {
			text.removeLineTEST(i);
			i--;
		}
	}
}