#pragma once

//
// class that take care of the source in the given .cpp file
//
class TextManager {
public:
	TextManager();
	TextManager(char*);
	~TextManager();
public:
	void readToFile(char*);
	void writeToFile(char* &);
public:
	void removeLine(int);
	void setLine(char*, int);
	char* getLine(size_t) const;
	void insertLine(char*, int);

	void removeLineTEST(int);
public:
	char** getFileLines();
	int getNumberLines() const;

	char* getFileName() const;
	int getFileSize(char*);
private:
	int getFileNumberLines(char*);

	// function that delete the allocated memory
	void clearSourceLines();
private:
	// array of lines that represent the file text content
	char** sourceLines;

	char* fileName;
	
	// save the current number of lines in the sourceLines array
	int numberLines;
};