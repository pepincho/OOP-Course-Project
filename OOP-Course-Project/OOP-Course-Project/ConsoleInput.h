#pragma once

class ConsoleInput {
public:
	ConsoleInput();
	~ConsoleInput();
public:
	void distinguishConsoleInput(int argc, char* argv[]);
public:
	const int getNumberFiles() const;
	const int getNumberCommands() const;
public:
	const char** getPathsToFiles() const;
	const char** getCommands() const;
private:
	bool isCommand(char*);
	void copyCommand(char*, const char*);
private:
	void clearPathsToFiles();
	void clearCommands();
private:
	int numberFiles;
	char** pathsToFiles;
	int numberCommands;
	char** commands;
};