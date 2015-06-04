#pragma once

#include "Line.h"

class FileContent {
public:
	FileContent();
	~FileContent();
public:
	void readFile(char*);
// for now it'll be a char* in order to get the file content
private:
	char* source;
private:
	Line* lines;
};