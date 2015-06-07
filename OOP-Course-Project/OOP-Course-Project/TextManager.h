#pragma once

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
	const char* getLine(size_t) const;
	void insertLine(char*, int);
public:
	const char** getFileLines() const;
	const int getNumberLines() const;
	
	const char* getFileName() const;
public:
	int getFileSize(char*);
private:
	int getFileNumberLines(char*);
	void clearSourceLines();
private:
	char** sourceLines;
	int numberLines;

	char* fileName;
};