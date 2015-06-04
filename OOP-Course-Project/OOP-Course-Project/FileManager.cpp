#include "FileManager.h"

#include <iostream>
#include <fstream>

FileManager::FileManager() {
	this->source = NULL;
	this->fileSize = 0;
}

FileManager::~FileManager() {
	delete this->source;
	this->fileSize = 0;
}


void FileManager::readFile(char* fileName) {
	int fileSize = getFileSize(fileName);
	std::cout << "The size of the file is " << fileSize << std::endl;

	int counterLines = getFileLines(fileName);
	std::cout << "The file has " << counterLines << " lines." << std::endl;

	this->source = new (std::nothrow) char[fileSize + 1];
	if (source == NULL) {
		return;
	}

	this->sourceLines = new (std::nothrow) char*[counterLines];
	if (sourceLines == NULL) {
		return;
	}

	for (int i = 0; i < counterLines; i++) {
		this->sourceLines[i] = new (std::nothrow) char[50];
	}

	std::ifstream myFile(fileName, std::ios::binary);

	int index = 0;
	int currentLine = 0;
	int currentIndex = 0;
	char c;

	while (myFile) {
		myFile.get(c);
		this->source[index] = c;
		
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
		

		index++;
	}

	this->numberLines = counterLines;

	this->source[fileSize] = '\0';
	this->fileSize = fileSize;

	//myFile.close();
}

int FileManager::getFileSize(char* fileName) {
	std::ifstream myFile(fileName, std::ios::binary | std::ios::ate);

	if (!myFile) {
		std::cerr << "Error!" << std::endl;
		//std::exit;
		return 0;
	}

	return int(myFile.tellg());
}

int FileManager::getFileLines(char* fileName) {
	std::ifstream myFile(fileName, std::ios::binary);

	if (!myFile) {
		std::cerr << "Error!" << std::endl;
		return 0;
	}
	
	char c;
	int counterLines = 1;

	while (myFile) {
		myFile.get(c);

		if (c == '\n') {
			counterLines++;
		}
	}

	return counterLines;
}

void FileManager::insertLine(char* line, int atRow) {
	char** temp = new (std::nothrow) char*[this->numberLines + 1];
	int indx = 0;
	std::cout << numberLines << std::endl;
	for (int i = 0; i < this->numberLines + 1; i++) {
		temp[i] = new (std::nothrow) char[50];
	}

	for (int i = 0; i < atRow; i++) {
		strcpy(temp[i], this->sourceLines[i]);
		//temp[strlen(this->sourceLines[i])] = '\0';
		indx = i;
	}
	indx++;
	
	strcpy(temp[atRow], line);
	//temp[strlen(line)] = '\0';

	for (int i = indx; i < this->numberLines; i++) {
		strcpy(temp[i + 1], this->sourceLines[i]);
		//temp[strlen(this->sourceLines[i])] = '\0';
	}

	// I should delete TEMP, recreate new sourceLines and copy temp in it

	std::cout << "The new char** of lines is:" << std::endl;
	for (int i = 0; i < this->numberLines + 1; i++) {
		std::cout << "temp[" << i << "] = " << temp[i] << std::endl;
	}
}

const char* FileManager::getLine(int atRow) {
	return (const char*) this->sourceLines[atRow];
}

void FileManager::changeLine(int atRow) {
	// some code to change the line
}

void FileManager::deleteLine(int) {

}

void FileManager::writeFile(char* currFileName) {

}