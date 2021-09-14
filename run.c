#include "main.h"

// This executes the various commands entered by the user.
void commandHandler() {
    long long int totalCommands = addAllCommandsInList();

    // If the list is empty then simply return
    if (totalCommands == 0 || listOfArgs[0] == NULL) 
        return;
    
    // Check for cd.
    if(strcmp(listOfArgs[0], "cd") == 0) {
        cd(totalCommands, listOfArgs[1]);
    }

    else if(strcmp(listOfArgs[0], "pwd") == 0) {
        // the no. of arguments should be = 1
        if (totalCommands != 1) {
            printf(stderr, "Error : too many arguments have been passed!");
            return;
        }
        pwd();
    }

    else if(strcmp(listOfArgs[0], "echo") == 0) {
        echo();
    }

    else if(strcmp(listOfArgs[0], "ls") == 0) {
        ls(totalCommands, listOfArgs);
    }
}