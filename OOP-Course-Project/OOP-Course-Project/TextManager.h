#pragma once

#include "Line.h"

class TextManager {
public:
	TextManager();
	~TextManager();
private:
	int getFileSize(char*);
public:
	void readFile(char*);
	void writeFile(char*);
public:
	void deleteLine(int);
	void changeLine(int);
	const char* getLine(int);
	void insertLine(char*, int);
// for now it'll be a char* in order to get the file content
public:
	//char* fileName;

	char* source;
	int fileSize;

	char** sourceLines;
	int numberLines;

	int getFileLines(char*);
private:
	//Line* lines;
};