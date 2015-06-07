#include "TextManager.h"

#include <iostream>
#include <fstream>


TextManager::TextManager() {
	this->sourceLines = NULL;
	this->numberLines = 0;
	this->fileName = NULL;
	std::cout << "TextManager::TextManager()" << std::endl;
}

TextManager::~TextManager() {
	clearSourceLines();
	delete[] this->fileName;
	std::cout << "TextManager::~TextManager()" << std::endl;
}

void TextManager::clearSourceLines() {
	//for (int i = 0; i < this->numberLines; i++) {
	//	delete[] this->sourceLines[i];
	//}
	//delete[] sourceLines;

	//this->numberLines = 0;
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
				//if (c == 0xBB || c == 0xBF || c == 0xEF) {
				//	std::cout << "hop" << std::endl;
				//	this->sourceLines[currentLine][currentIndex] = '\0';
				//	currentIndex++;
				//	continue;
				//}
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
		if (myFile) {
			if (c == '\n') {
				counterLines++;
			}
		}
	}

	return counterLines;
}

void TextManager::insertLine(char* line, int atRow) {
	int newNumLines = this->numberLines + 1;
	char** temp = new (std::nothrow) char*[newNumLines];
	if (temp == NULL)
		return;
	int indx = 0;

	for (int i = 0; i < atRow; i++) {
		temp[i] = this->sourceLines[i];
		indx = i;
	}
	indx++;

	size_t lineLen = strlen(line) + 1;
	temp[atRow] = new (std::nothrow) char[lineLen];
	if (temp[atRow] == NULL)
		return;

	strcpy_s(temp[atRow], lineLen, line);

	for (int i = indx; i < this->numberLines; i++) {
		temp[i + 1] = this->sourceLines[i];
	}

	this->numberLines = newNumLines;
	this->sourceLines = new (std::nothrow) char*[this->numberLines];

	if (this->sourceLines == NULL)
		return;

	for (int i = 0; i < this->numberLines; i++) {
		size_t buffSize = strlen(temp[i]) + 1;
		this->sourceLines[i] = temp[i];
	}

	delete[] temp;
}

const char* TextManager::getLine(size_t atRow) const {
	return (const char*) this->sourceLines[atRow];
}

void TextManager::setLine(char* newLine, int atRow) {
	//newLine = "#include <iostream> peshko";
	//this->sourceLines[atRow] = new (std::nothrow) char[strlen(newLine) + 1 + 2];
	
	//std::cout << "size of newLine in setLine: " << strlen(newLine) << std::endl;
	this->sourceLines[atRow] = new (std::nothrow) char[strlen(newLine) + 1];
	//std::cout << "size of new line: " << strlen(newLine) << std::endl;
	strcpy_s(this->sourceLines[atRow], strlen(newLine) + 1, newLine);
	//this->sourceLines[atRow][strlen(newLine) + 1] = '\r';
	//this->sourceLines[atRow][strlen(newLine) + 1 + 1] = '\n';
}

void TextManager::removeLine(int atRow) {
	int newNumLines = this->numberLines - 1;

	for (int i = atRow; i < this->numberLines - 1; i++) {
		size_t currLen = strlen(this->sourceLines[i + 1]) + 1;
		strcpy_s(this->sourceLines[i], currLen, this->sourceLines[i + 1]);
	}
	delete[] sourceLines[this->numberLines - 1];
	this->numberLines = newNumLines;
}

void TextManager::writeToFile(char* &currFileName) {
	size_t newLenNameFile = strlen(currFileName) + 1;
	char* newName = new char[newLenNameFile];
	strcpy_s(newName, newLenNameFile, currFileName);
	char* toOldName = ".old";
	char newText[50];
	
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
	//myTextFile.write((const char*)&this->sourceLines, sizeof(this->sourceLines));
		//myTextFile << sourceLines[i];
		//myTextFile.write((const char*)&this->sourceLines[i], sizeof(this->sourceLines[i]));
	}

	myTextFile.close();
}

const char** TextManager::getFileLines() const {
	return (const char**) this->sourceLines;
}

const int TextManager::getNumberLines() const {
	std::cout << "number of lines: " << this->numberLines << std::endl;
	return (const int) this->numberLines;
}

const char* TextManager::getFileName() const {
	return (const char*) this->fileName;
}

TextManager::TextManager(char* fileName) {
	this->fileName = new (std::nothrow) char[strlen(fileName) + 1];
	if (this->fileName == NULL)
		return;
	strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
	
	readToFile(this->fileName);
}
