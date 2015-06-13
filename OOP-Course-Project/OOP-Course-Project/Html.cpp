#include "Html.h"

#include <iostream>
#include <fstream>
//
#include <cctype>
#include <cstring>

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
	char newText[_MAX_PATH];

	strcpy(newText, newName);
	strcat(newText, toNewHtmlName);
	std::cout << "The new name of the file is " << newText << std::endl;

	char** source = text.getFileLines();
	int numberLines = text.getNumberLines();

	std::ofstream myTextFile(newText, std::ios::binary | std::ios::out, std::ios::trunc);
	if (!myTextFile) {
		std::cerr << "Error!" << std::endl;
		return;
	}
	char* bam = makeInitialHtmlFile();
	myTextFile.write((const char*)bam, strlen(bam));

	//
	// I should split a single line in char** array of words
	// and after that to check what type of word is
	//

	for (int i = 0; i < numberLines; i++) {
		//myTextFile.write((const char*)"<p style=\"font-size:110% \">", strlen("<p style=\"font-size:160% \">"));
		//myTextFile.write((const char*)source[i], strlen(source[i]));
		//myTextFile.write((const char*)"</p>", strlen("</p>"));

		//std::cout << "Symbol: " << source[0][0] << std::endl;
		if (isLineDirective(source[i])) {
			myTextFile.write((const char*)"<p id=\"directive\" style=\"font-size:120% \">", strlen("<p id=\"directive\" style=\"font-size:120% \">"));
			myTextFile.write((const char*)source[i], strlen(source[i]));
			myTextFile.write((const char*)"</p>", strlen("</p>"));
			continue;
		}
		else if (hasComment(source[i], strlen(source[i]))) {
			myTextFile.write((const char*)"<p id=\"comment\" style=\"font-size:120% \">", strlen("<p id=\"comment\" style=\"font-size:120% \">"));
			myTextFile.write((const char*)source[i], strlen(source[i]));
			myTextFile.write((const char*)"</p>", strlen("</p>"));
			continue;
		}
		else {
			//char **word = NULL;
			//int wordsCount = countWords(source[i]);
			//word = new char *[wordsCount];
			char* temp = new (std::nothrow) char[strlen(source[i]) + 1];
			strcpy_s(temp, strlen(source[i]) + 1, source[i]);
			char * pch;
			pch = strtok(temp, " ,.-()<>;");
			myTextFile.write((const char*)"<p style=\"font-size:120% \">", strlen("<p style=\"font-size:120% \">"));
			while (pch != NULL) {
				//std::cout << pch << std::endl;
				if (strcmp(pch, "int") == 0 || strcmp(pch, "double") == 0 || strcmp(pch, "float") == 0) {
					myTextFile.write((const char*)"&nbsp", strlen("&nbsp"));

					myTextFile.write((const char*)"<span id=\"res_word\" \">", strlen("<span id=\"res_word\" \">"));
					myTextFile.write((const char*)pch, strlen(pch));
					myTextFile.write((const char*)"</span>", strlen("</span>"));
				}
				else if (strcmp(pch, "if") == 0 || strcmp(pch, "else") == 0 || strcmp(pch, "main") == 0) {
					myTextFile.write((const char*)"&nbsp", strlen("&nbsp"));

					myTextFile.write((const char*)"<span id=\"res_word\" \">", strlen("<span id=\"res_word\" \">"));
					myTextFile.write((const char*)pch, strlen(pch));
					myTextFile.write((const char*)"</span>", strlen("</span>"));
				}
				else if (strcmp(pch, "for") == 0 || strcmp(pch, "while") == 0 || strcmp(pch, "return") == 0) {
					myTextFile.write((const char*)"&nbsp", strlen("&nbsp"));

					myTextFile.write((const char*)"<span id=\"res_word\" \">", strlen("<span id=\"res_word\" \">"));
					myTextFile.write((const char*)pch, strlen(pch));
					myTextFile.write((const char*)"</span>", strlen("</span>"));
				}
				else if (strcmp(pch, "char") == 0 || strcmp(pch, "char*") == 0) {
					myTextFile.write((const char*)"&nbsp", strlen("&nbsp"));

					myTextFile.write((const char*)"<span id=\"res_word\" \">", strlen("<span id=\"res_word\" \">"));
					myTextFile.write((const char*)pch, strlen(pch));
					myTextFile.write((const char*)"</span>", strlen("</span>"));
				}
				else if (strcmp(pch, "1") == 0 || strcmp(pch, "2") == 0 || strcmp(pch, "3") == 0 || strcmp(pch, "4") == 0 || strcmp(pch, "5") == 0) {
					myTextFile.write((const char*)"&nbsp", strlen("&nbsp"));

					myTextFile.write((const char*)"<span id=\"number\" \">", strlen("<span id=\"number\" \">"));
					myTextFile.write((const char*)pch, strlen(pch));
					myTextFile.write((const char*)"</span>", strlen("</span>"));
				}
				else {
					//char* space = "&nbsp";
					myTextFile.write((const char*)"&nbsp", strlen("&nbsp"));
					myTextFile.write((const char*)"<span \" \">", strlen("<span \" \">"));
					myTextFile.write((const char*)pch, strlen(pch));
					myTextFile.write((const char*)"</span>", strlen("</span>"));
				}
				pch = strtok(NULL, " ,.-");
			}
			myTextFile.write((const char*)"</p>", strlen("</p>"));


			//char *result = source[i];
			//toWords(source[i], word);
			//for (int j = 0; j < wordsCount; j++) {
			//	if (strcmp(word[j], "int") == 0) {
			//		myTextFile.write((const char*)"<p id=\"res_word\" style=\"font-size:120% \">", strlen("<p id=\"res_word\" style=\"font-size:120% \">"));
			//		myTextFile.write((const char*)source[i], strlen(source[i]));
			//		myTextFile.write((const char*)"</p>", strlen("</p>"));
			//	}
			//}
		}

		//myTextFile.write((const char*)"<p style=\"font-size:120% \">", strlen("<p style=\"font-size:120% \">"));
		//myTextFile.write((const char*)source[i], strlen(source[i]));
		//myTextFile.write((const char*)"</p>", strlen("</p>"));
	}
	myTextFile.write((const char*)"</body>", strlen("</body>"));
	myTextFile.write((const char*)"</html>", strlen("</html>"));

	myTextFile.close();
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
		<td> Pink </td> \
		</tr> \
		<tr> \
		<td> Numbers </td> \
		<td> Black </td> \
		</tr> \
		<tr> \
		<td> Character literals </td> \
		<td> Orange </td> \
		</tr> \
		</table> \
		<br /> <br />";

	return htmlContent;
}

bool Html::isLineDirective(char* line) {
	if (line[0] == '#') {
		return true;
	}
	return false;
}

bool Html::hasComment(char* line, int lineLen) {
	for (int i = 0; i < lineLen - 1; i++) {
		if (line[i] == '/' && line[i + 1] == '/') {
			return true;
		}
	}
	return false;
}

//
//
//

int Html::countWords(const char* str) {
	if (str == NULL)
		return 1;

	bool inSpaces = true;
	int numWords = 0;

	while (*str != NULL) {
		if (std::isspace(*str))
		{
			inSpaces = true;
		}
		else if (inSpaces)
		{
			numWords++;
			inSpaces = false;
		}
		++str;
	}

	return numWords;
}

void Html::toWords(const char *sentence, char **word) {
	int wordsCount = countWords(sentence);

	for (int i = 0; i < wordsCount; i++) {
		while (*sentence && (!isAlphaNum(*sentence))) {
			sentence++;
		}

		const char *end = NULL;
		int len = 0;

		if (*sentence) {
			end = sentence + 1;
			while (*end && (isAlphaNum(*end) || *end != ' ')) {
				end++;
			}
			len = end - sentence;
		}

		if (len > 0) {
			word[i] = new char[len + 1];
			for (int pos = 0; pos < len; pos++) {
				word[i][pos] = sentence[pos];
			}
			word[i][len] = '\0';
			len = 0;
		}

		sentence = end;
	}
}

bool Html::isAlphaNum(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9')) {
		return true;
	}
	else {
		return false;
	}
}