#include "TextManager.h"

#include <iostream>
#include <fstream>


TextManager::TextManager() {
	this->sourceLines = NULL;
	this->numberLines = 0;
	std::cout << "TextManager::TextManager()" << std::endl;
}

TextManager::~TextManager() {
	clearSourceLines();
	std::cout << "TextManager::~TextManager()" << std::endl;
}

void TextManager::clearSourceLines() {
	for (int i = 0; i < this->numberLines; i++) {
		delete[] this->sourceLines[i];
	}
	delete[] sourceLines;

	this->numberLines = 0;
}

void TextManager::readToFile(char* fileName) {
	int fileSize = getFileSize(fileName);
	std::cout << "The size of the file is " << fileSize << std::endl;

	// here I can check If the file is too big and return an error with msg

	int counterLines = getFileNumberLines(fileName);
	this->numberLines = counterLines;
	std::cout << "The file has " << counterLines << " lines." << std::endl;

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
	}

	myFile.close();
}

int TextManager::getFileSize(char* fileName) {
	std::ifstream myFile(fileName, std::ios::binary | std::ios::ate);

	if (!myFile) {
		std::cerr << "Error!" << std::endl;
		return 0;
	}

	return int(myFile.tellg());
}

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

		if (c == '\n')
			counterLines++;		
	}

	return counterLines;
}

void TextManager::insertLine(char* line, int atRow) {
	int newNumLines = this->numberLines + 1;
	char** temp = new (std::nothrow) char*[newNumLines];
	if (temp == NULL)
		return;
	int indx = 0;
	std::cout << newNumLines << std::endl;
	//for (int i = 0; i < this->numberLines + 1; i++) {
	//	temp[i] = new (std::nothrow) char[50];
	//}

	for (int i = 0; i < atRow; i++) {
		//strcpy(temp[i], this->sourceLines[i]);
		//temp[strlen(this->sourceLines[i])] = '\0';
		temp[i] = this->sourceLines[i];
		indx = i;
	}
	indx++;

	size_t lineLen = strlen(line) + 1;
	temp[atRow] = new (std::nothrow) char[lineLen];
	if (temp[atRow] == NULL)
		return;

	strcpy_s(temp[atRow], lineLen, line);
	//temp[lineLen] = '\0';

	for (int i = indx; i < this->numberLines; i++) {
		temp[i + 1] = this->sourceLines[i];
		//strcpy(temp[i + 1], this->sourceLines[i]);
		//temp[strlen(this->sourceLines[i])] = '\0';
	}

	//std::cout << "The new char** of lines is:" << std::endl;
	//for (int i = 0; i < newSize; i++) {
	//	std::cout << "temp[" << i << "] = " << temp[i] << std::endl;
	//}
	//clearSourceLines();
	this->numberLines = newNumLines;
	this->sourceLines = new (std::nothrow) char*[this->numberLines];

	if (this->sourceLines == NULL)
		return;

	for (int i = 0; i < this->numberLines; i++) {
		size_t buffSize = strlen(temp[i]) + 1;
		//strcpy_s(this->sourceLines[i], buffSize, temp[i]);
		this->sourceLines[i] = temp[i];
		//std::cout << this->sourceLines[i] << std::endl;
	}

	delete temp;
	//for (int i = 0; i < this->numberLines; i++) {
	//	delete[] temp[i];
	//}
	//delete[] temp;
}

const char* TextManager::getLine(size_t atRow) const {
	return (const char*) this->sourceLines[atRow];
}

void TextManager::setLine(char* newLine, int atRow) {
	newLine = "#include <iostream> peshko";
	this->sourceLines[atRow] = new (std::nothrow) char[strlen(newLine) + 1];
	strcpy_s(this->sourceLines[atRow], strlen(newLine) + 1, newLine);
	//delete[] this->sourceLines[atRow];
	//this->sourceLines[atRow] = NULL;
	//this->sourceLines[atRow] = newLine;
}

void TextManager::removeLine(int atRow) {

}

void TextManager::writeToFile(char* currFileName) {

}

const char** TextManager::getFileLines() const {
	return (const char**) this->sourceLines;
}

const int TextManager::getNumberLines() const {
	return (const int) this->numberLines;
}