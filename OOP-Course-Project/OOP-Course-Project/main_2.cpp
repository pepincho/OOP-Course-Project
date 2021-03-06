#include <iostream>

#include "ConsoleInput.h"
#include "TextManager.h"

#include "CommandFactory.h"


int main(int argc, char* argv[]) {

    ConsoleInput cmdInput;
    cmdInput.distinguishConsoleInput(argc, argv);

    //std::cout << "The number of Files is " << cmdInput.getNumberFiles() << std::endl;
    //char** files = cmdInput.getPathsToFiles();
    //for (int i = 0; i < cmdInput.getNumberFiles(); i++) {
    //    std::cout << "file[" << i << "] is " << files[i] << std::endl;
    //}
    //std::cout << "The number of Commands is " << cmdInput.getNumberCommands() << std::endl;
    //char** nameCommands = cmdInput.getCommands();
    //for (int i = 0; i < cmdInput.getNumberCommands(); i++) {
    //    std::cout << "command[" << i << "] is " << nameCommands[i] << std::endl;
    //}

    //std::cout << "------------------------------------------" << std::endl;

    //char* currFileName = "test.txt";
    //char* currFileName = "test_format_2.cpp";

    //TextManager fileSource(currFileName);
    //char** source = fileSource.getFileLines();
    //int counterLines = fileSource.getNumberLines();
    //int sizeSource = 0;
    //std::cout << "The file has " << fileSource.getNumberLines() << " lines." << std::endl;
    //for (int i = 0; i < counterLines; i++) {
    //    std::cout << "<>line[" << i << "] -> " << source[i] << " len: " << strlen(source[i]) << std:    
    //    sizeSource += strlen(source[i]);
    //}
    //std::cout << "Size of the file before commands: " << sizeSource << std::endl;

    //std::cout << "------------------------------------------" << std::endl;
    
    try {
        CommandFactory commandFac(cmdInput.getCommands(), cmdInput.getNumberCommands());
        int numberCommands = commandFac.getNumberCommands();
    
        //for (int i = 0; i < numberCommands; i++) {
        //    commandFac.getCommands()[i]->processCommand(fileSource);
        //}
        int numberFiles = cmdInput.getNumberFiles();
        for (int i = 0; i < numberFiles; i++) {
            TextManager fileSource(cmdInput.getPathsToFiles()[i]);

            for (int j = 0; j < numberCommands; j++) {
                commandFac.getCommands()[j]->processCommand(fileSource);
            }
            fileSource.writeToFile(cmdInput.getPathsToFiles()[i]);
        }
    
    }
    catch (std::exception& e) {
        std::cerr << "ERROR: Operation failed! Reason: " << e.what() << std::endl;
        std::exit(0);
    }

    


    //
    //char* hop = "peshko";
    //fileSource.insertLine(hop, 2);
    //
    //

    //std::cout << "------------------------------------------" << std::endl;

    //char** newSource = fileSource.getFileLines();
    //int counterNewLines = fileSource.getNumberLines();
    //int sizeNewSource = 0;
    //std::cout << "The file has " << fileSource.getNumberLines() << " lines." << std::endl;
    //for (int i = 0; i < counterNewLines; i++) {
    //    std::cout << "<>line[" << i << "] -> " << newSource[i] << " len: " << strlen(newSource[i]) <    //}
    //    sizeNewSource += strlen(newSource[i]);
    //}
    //std::cout << "Size of the file after commands: " << sizeNewSource << std::endl;

    //std::cout << "------------------------------------------" << std::endl;

    return 0;
}

