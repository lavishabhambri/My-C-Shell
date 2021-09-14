#include "main.h"

// This executes the various commands entered by the user.
void commandHandler() {
    long long int noOfCommands = 0;
    tokenizer(listOfCommands, inputGiven, ";\n", &noOfCommands);

    for (int i = 0; i < noOfCommands; i++) {
        long long int totalArgsInEachCommand = 0;
        tokenizer(listOfArgs, listOfCommands[i], " \t", &totalArgsInEachCommand);
        
        // If the list is empty then simply return
        if (totalArgsInEachCommand == 0 || listOfArgs[0] == NULL) 
            return;
        
        // Check for cd.
        if(strcmp(listOfArgs[0], "cd") == 0) {
            cd(totalArgsInEachCommand, listOfArgs[1]);
        }

        else if(strcmp(listOfArgs[0], "pwd") == 0) {
            // the no. of arguments should be = 1
            if (totalArgsInEachCommand != 1) {
                printf(stderr, "Error : too many arguments have been passed!");
                return;
            }
            pwd();
        }

        else if(strcmp(listOfArgs[0], "echo") == 0) {
            echo(totalArgsInEachCommand, listOfArgs);
        }

        else if(strcmp(listOfArgs[0], "ls") == 0) {
            ls(totalArgsInEachCommand, listOfArgs);
        }
    }
    

    return;
}