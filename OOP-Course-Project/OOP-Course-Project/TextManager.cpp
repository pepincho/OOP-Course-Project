#include "TextManager.h"

#include <iostream>
#include <fstream>


TextManager::TextManager() {
	this->sourceLines = NULL;
	this->numberLines = 0;
	this->fileName = NULL;
	//std::cout << "TextManager::TextManager()" << std::endl;
}

TextManager::~TextManager() {
	clearSourceLines();
	delete[] this->fileName;
	//std::cout << "TextManager::~TextManager()" << std::endl;
}

void TextManager::clearSourceLines() {
	for (int i = 0; i < this->numberLines; i++) {
		delete[] this->sourceLines[i];
	}
	delete[] sourceLines;

	this->numberLines = 0;
}

//
// function that read the .cpp file content
// stores it in the sourceLines char** array
//
void TextManager::readToFile(char* fileName) {
	int fileSize = getFileSize(fileName);

	// here I can check If the file is too big and return an error with msg

	int counterLines = getFileNumberLines(fileName);
	this->numberLines = counterLines;

	this->sourceLines = new (std::nothrow) char*[this->numberLines];
	if (sourceLines == NULL)
		return;

	int currMaxLineLen = 50;
	for (int i = 0; i < this->numberLines; i++) {
		this->sourceLines[i] = new (std::nothrow) char[currMaxLineLen];
		if (sourceLines[i] == NULL)
			return;
	}

	std::ifstream myFile(fileName, std::ios::binary);

	int currentLine = 0;
	int currentIndex = 0;
	char c;

	while (myFile) {
		myFile.get(c);

		if (myFile) {
			if (c == '\n') {
				this->sourceLines[currentLine][currentIndex] = c;
				this->sourceLines[currentLine][currentIndex + 1] = '\0';
				currentLine++;
				currentIndex = 0;
			}
			else {
				this->sourceLines[currentLine][currentIndex] = c;
				this->sourceLines[currentLine][currentIndex + 1] = '\0';
				currentIndex++;
			}
		}
		else {
			if (c == '\n') {
				this->sourceLines[currentLine][currentIndex] = c;
				this->sourceLines[currentLine][currentIndex + 1] = '\0';
			}
		}
	}

	myFile.close();
}

//
// function that returns the file size
//
int TextManager::getFileSize(char* fileName) {
	std::ifstream myFile(fileName, std::ios::binary | std::ios::ate);

	if (!myFile) {
		std::cerr << "Error!" << std::endl;
		return 0;
	}

	return int(myFile.tellg());
}

//
// function that returns the number of lines in the sourceLines char** array
//
int TextManager::getFileNumberLines(char* fileName) {
	std::ifstream myFile(fileName, std::ios::binary);

	if (!myFile) {
		std::cerr << "Error!" << std::endl;
		return 0;
	}

	char c;
	int counterLines = 1;

	while (myFile) {
		myFile.get(c);
		if (myFile) {
			if (c == '\n') {
				counterLines++;
			}
		}
	}

	return counterLines;
}

//
// function that insert a given line in the sourceLines char** array
//
void TextManager::insertLine(char* line, int atRow) {
	int newNumLines = this->numberLines + 1;
	char** temp = new (std::nothrow) char*[newNumLines];
	if (temp == NULL)
		return;
	int indx = 0;

	for (int i = 0; i < atRow; i++) {
		size_t buffSize = strlen(this->sourceLines[i]) + 1;
		temp[i] = new (std::nothrow) char[buffSize];
		if (temp[i] == NULL)
			return;
		strcpy_s(temp[i], buffSize, this->sourceLines[i]);
		indx = i;
	}
	indx++;

	size_t lineLen = strlen(line) + 1;
	temp[atRow] = new (std::nothrow) char[lineLen];
	if (temp[atRow] == NULL)
		return;

	strcpy_s(temp[atRow], lineLen, line);

	for (int i = indx; i < this->numberLines; i++) {
		size_t buffSize = strlen(this->sourceLines[i]) + 1;
		temp[i + 1] = new (std::nothrow) char[buffSize];
		if (temp[i + 1] == NULL)
			return;
		strcpy_s(temp[i + 1], strlen(this->sourceLines[i]) + 1, this->sourceLines[i]);
	}

	this->numberLines = newNumLines;
	this->sourceLines = new (std::nothrow) char*[this->numberLines];

	if (this->sourceLines == NULL)
		return;

	for (int i = 0; i < this->numberLines; i++) {
		size_t buffSize = strlen(temp[i]) + 1;
		this->sourceLines[i] = new (std::nothrow) char[buffSize];
		if (this->sourceLines[i] == NULL)
			return;
		strcpy_s(sourceLines[i], strlen(temp[i]) + 1, temp[i]);
	}

	delete[] temp;
}

//
// function that returns a line on a given index
//
char* TextManager::getLine(size_t atRow) const {
	return this->sourceLines[atRow];
}

//
// function that makes changes on a line on a given index
// it takes a new line and save it on the given index in sourceLines char** array
//
void TextManager::setLine(char* newLine, int atRow) {
	this->sourceLines[atRow] = new (std::nothrow) char[strlen(newLine) + 1];
	strcpy_s(this->sourceLines[atRow], strlen(newLine) + 1, newLine);
}

//
// function that "remove" the content on a given index
//
void TextManager::removeLine(int atRow) {
	delete[] sourceLines[atRow];
	sourceLines[atRow] = new (std::nothrow) char[2 + 1];
	sourceLines[atRow][0] = '\r';
	sourceLines[atRow][1] = '\n';
	sourceLines[atRow][2] = '\0';
}

//
// function that remove the line on given index from sourceLines char** array
// also decrement the number of lines
//
void TextManager::removeLineTEST(int atRow) {
	int newNumLines = this->numberLines - 1;
	char** temp = new (std::nothrow) char*[newNumLines];
	if (temp == NULL)
		return;
	int indx = 0;

	for (int i = 0; i < atRow; i++) {
		size_t buffSize = strlen(this->sourceLines[i]) + 1;
		temp[i] = new (std::nothrow) char[buffSize];
		if (temp[i] == NULL)
			return;
		strcpy_s(temp[i], buffSize, this->sourceLines[i]);
		indx = i;
	}
	indx++;

	for (int i = indx; i < newNumLines; i++) {
		size_t buffSize = strlen(this->sourceLines[i + 1]) + 1;
		temp[i] = new (std::nothrow) char[buffSize];
		if (temp[i] == NULL)
			return;
		strcpy_s(temp[i], strlen(this->sourceLines[i + 1]) + 1, this->sourceLines[i + 1]);
	}

	this->numberLines = newNumLines;
	this->sourceLines = new (std::nothrow) char*[this->numberLines];

	if (this->sourceLines == NULL)
		return;

	for (int i = 0; i < this->numberLines; i++) {
		size_t buffSize = strlen(temp[i]) + 1;
		this->sourceLines[i] = new (std::nothrow) char[buffSize];
		if (this->sourceLines[i] == NULL)
			return;
		strcpy_s(sourceLines[i], strlen(temp[i]) + 1, temp[i]);
	}

	delete[] temp;
}

//
// function that save the sourceLines char** array in a given file names
// the original file is save as .odd
// the content after commands is save as the original file name
//
void TextManager::writeToFile(char* &currFileName) {
	size_t newLenNameFile = strlen(currFileName) + 1;
	char* newName = new char[newLenNameFile];
	strcpy_s(newName, newLenNameFile, currFileName);
	char* toOldName = ".old";
	char newText[_MAX_PATH];

	strcpy(newText, currFileName);
	strcat(newText, toOldName);
	std::cout << "The new name of the file is " << newText << std::endl;

	rename(currFileName, newText);

	std::ofstream myTextFile(newName, std::ios::binary | std::ios::out, std::ios::trunc);
	if (!myTextFile) {
		std::cerr << "Error!" << std::endl;
		return;
	}

	for (int i = 0; i < this->numberLines; i++) {
		myTextFile.write((const char*)this->sourceLines[i], strlen(this->sourceLines[i]));
	}

	myTextFile.close();
}

char** TextManager::getFileLines() {
	return this->sourceLines;
}

int TextManager::getNumberLines() const {
	return this->numberLines;
}

char* TextManager::getFileName() const {
	return this->fileName;
}

TextManager::TextManager(char* fileName) {
	//std::cout << "TextManager::TextManager(char* fileName)" << std::endl;
	this->fileName = new (std::nothrow) char[strlen(fileName) + 1];
	if (this->fileName == NULL)
		return;
	strcpy_s(this->fileName, strlen(fileName) + 1, fileName);

	readToFile(this->fileName);
}
