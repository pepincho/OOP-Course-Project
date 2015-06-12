#include "Html.h"

#include <iostream>
#include <fstream>

Html::Html() {
	//std::cout << "[Entering Html::Html()]" << std::endl;
}

Html::~Html() {
	//std::cout << "[Entering Html::~Html()]" << std::endl;
}

void Html::processCommand(TextManager& text) {
	std::cout << "processHtml on file " << text.getFileName() << std::endl;
	generateHtmlFile(text);
}

void Html::generateHtmlFile(TextManager& text) {
	char* currFileName = text.getFileName();
	int sizeCurrFileName = strlen(currFileName);
	
	int newLenNameFile = strlen(currFileName) - 4;
	char* newName = new char[newLenNameFile];
	
	for (int i = 0; i < sizeCurrFileName; i++) {
		if (currFileName[i] == '.')
			break;
		else
			newName[i] = currFileName[i];
	}
	newName[newLenNameFile] = '\0';
	//std::cout << "The new name of the file is " << newName << std::endl;
	//strcpy_s(newName, newLenNameFile, currFileName);
	char* toNewHtmlName = ".html";
	char newText[50];

	strcpy(newText, newName);
	strcat(newText, toNewHtmlName);
	std::cout << "The new name of the file is " << newText << std::endl;

	char** source = text.getFileLines();
	int numberLines = text.getNumberLines();

	//std::ofstream myTextFile(newText, std::ios::binary | std::ios::out, std::ios::trunc);
	//if (!myTextFile) {
	//	std::cerr << "Error!" << std::endl;
	//	return;
	//}
	//char* bam = makeInitialHtmlFile();
	//myTextFile.write((const char*)bam, strlen(bam));
	//for (int i = 0; i < numberLines; i++) {
	//	myTextFile.write((const char*)"<p>", strlen("<p>"));
	//	myTextFile.write((const char*)source[i], strlen(source[i]));
	//	myTextFile.write((const char*)"</p>", strlen("</p>"));
	//}
	//myTextFile.write((const char*)"</body>", strlen("</body>"));
	//myTextFile.write((const char*)"</html>", strlen("</html>"));

	//myTextFile.close();
}

char* Html::makeInitialHtmlFile() {
	char* htmlContent = "<html> \
		<head> \
		<link rel = \"stylesheet\" type = \"text/css\" href = \"style.css\"> \
		</head> \
		<body> \
		<h1 id = \"home1\"> \
		Petar Ivanov, Informatics, Faculty number : 45121 \
		</h1 > \
		<table id = \"t01\"> \
		<tr> \
		<th> C++ code fragment </td> \
		<th> Color of the fragment </td> \
		</tr> \
		<tr> \
		<td> Comments </td> \
		<td> Green </td> \
		</tr> \
		<tr> \
		<td> Reserved keywords </td> \
		<td> Blue </td> \
		</tr> \
		<tr> \
		<td> Strings </td> \
		<td> Red </td> \
		</tr> \
		<tr> \
		<td> Preprocessor directives </td> \
		<td> Yellow </td> \
		</tr> \
		<tr> \
		<td> Numbers </td> \
		<td> Black </td> \
		</tr> \
		<tr> \
		<td> Character literals </td> \
		<td> Pink </td> \
		</tr> \
		</table> \
		<br /> <br />";

	return htmlContent;
}