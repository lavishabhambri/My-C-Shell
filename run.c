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

        // Checking the background process (if at last we have &)
        if(strcmp(listOfArgs[totalArgsInEachCommand - 1],"&")==0){
            backgroundProcess(totalArgsInEachCommand, listOfArgs);
            return;
        }
        
        // Check for cd.
        else if(strcmp(listOfArgs[0], "cd") == 0) {
            cd(totalArgsInEachCommand, listOfArgs[1]);
        }


        // Check for pwd
        else if(strcmp(listOfArgs[0], "pwd") == 0) {
            // the no. of arguments should be = 1
            if (totalArgsInEachCommand != 1) {
                printf("Error : too many arguments have been passed!");
                return;
            }
            pwd();
        }

        // Check for echo
        else if(strcmp(listOfArgs[0], "echo") == 0) {
            echo(totalArgsInEachCommand, listOfArgs);
        }

        // Check for ls
        else if(strcmp(listOfArgs[0], "ls") == 0) {
            ls(totalArgsInEachCommand, listOfArgs);
        }

        // Check for pinfo
        else if(strcmp(listOfArgs[0], "pinfo") == 0) {
            pinfo(totalArgsInEachCommand, listOfArgs);
        }

        // Check for fg
        else if(strcmp(listOfArgs[0], "fg") == 0) {
            fg(totalArgsInEachCommand, listOfArgs);
        }

        // Check for exit
        else if(strcmp(listOfArgs[0], "exit") == 0) {
            forceKill();
            exit(0);
        }

        // Check for repeat
        else if(strcmp(listOfArgs[0], "repeat") == 0) {
            repeat(totalArgsInEachCommand, listOfArgs);
        }

        else {
            foregroundProcess(totalArgsInEachCommand, listOfArgs);
        }
    }
    

    return;
}