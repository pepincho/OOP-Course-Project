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
	char* getLine(size_t) const;
	void insertLine(char*, int);
public:
	char** getFileLines() const;
	int getNumberLines() const;

	char* getFileName() const;
	int getFileSize(char*);
private:
	int getFileNumberLines(char*);
	void clearSourceLines();
private:
	char** sourceLines;
	int numberLines;

	char* fileName;
};