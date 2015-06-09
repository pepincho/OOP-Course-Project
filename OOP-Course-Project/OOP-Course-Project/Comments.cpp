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
	removeMultiLineComment(text);
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
	
	int currIndex = 0;
	for (int i = 0; i < numLines; i++) {
		//std::cout << "on line: " << source[i] << std::endl;
		int currLineLen = strlen(source[i]);

		if (hasOpeningComment(source[currIndex], strlen(source[currIndex])) == true) {
			currLineLen = strlen(source[currIndex]);

			for (int p = 0; p < currLineLen - 1; p++) {

				if (source[currIndex][p] == '*' && source[currIndex][p + 1] == '/') {
					currLineLen = strlen(source[currIndex]);

					int startColumnComment = findStartMultiLineComment(source[currIndex], currLineLen);
					int endColumnComment = findEndMultiLineComment(source[currIndex], currLineLen);
					int sizeCurrNewLine = currLineLen - (endColumnComment - startColumnComment);

					char* currNewLine = new (std::nothrow) char[sizeCurrNewLine + 1];
					if (currNewLine == NULL)
						return;

					makeNewLine(source[currIndex], currLineLen, startColumnComment, endColumnComment - 1, currNewLine);
					currNewLine[sizeCurrNewLine] = '\0';

					text.setLine(currNewLine, currIndex);
				}
			}


			currLineLen = strlen(source[currIndex]);
			//std::cout << "zapochva komentara" << std::endl;

			int startColumnComment = findStartMultiLineComment(source[currIndex], currLineLen);
			int endColumnComment = findEndMultiLineComment(source[currIndex], currLineLen);
			//std::cout << "startColumnComment: " << startColumnComment << std::endl;
			//std::cout << "endColumnComment: " << endColumnComment << std::endl;

			int sizeCurrNewLine = currLineLen - (endColumnComment - startColumnComment);

			char* currNewLine = new (std::nothrow) char[sizeCurrNewLine + 1];
			if (currNewLine == NULL)
				return;

			makeNewLine(source[currIndex], currLineLen, startColumnComment, endColumnComment - 1, currNewLine);
			currNewLine[sizeCurrNewLine] = '\0';
			//currNewLine[sizeCurrNewLine - 1] = '\n';
			//currNewLine[sizeCurrNewLine - 2] = '\r';
			text.setLine(currNewLine, currIndex);

			isInComment = true;
			currIndex++;
			continue;
		}
		if (hasClosingComment(source[currIndex], strlen(source[currIndex])) == true) {
			
			currLineLen = strlen(source[currIndex]);

			//std::cout << "svurshva komentara" << std::endl;
			
			int endColumnComment = findEndMultiLineComment(source[currIndex], currLineLen);
			int sizeCurrNewLine = currLineLen - endColumnComment - 1;

			char* currNewLine = new (std::nothrow) char[sizeCurrNewLine + 1];
			if (currNewLine == NULL)
				return;

			makeNewLine(source[currIndex], currLineLen, 0, endColumnComment, currNewLine);
			//makeNewLine(source[currIndex], currLineLen, endColumnComment, currLineLen - 1, currNewLine);

			currNewLine[sizeCurrNewLine] = '\0';
			//currNewLine[sizeCurrNewLine - 1] = '\0';
			text.setLine(currNewLine, currIndex);

			currIndex++;
			isInComment = false;
			continue;

		}
		if (isInComment == true) {
			text.removeLine(currIndex);
			//currIndex++;
			//i -= 1;
			//numLines -= 1;
			//std::cout << "v komentara" << std::endl;
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