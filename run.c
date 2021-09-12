#include "main.h"

// This executes the various commands entered by the user.
void commandHandler() {
    long long int totalCommands = addAllCommandsInList();

    // If the list is empty then simply return
    if (totalCommands == 0 || listOfArgs[0] == NULL) 
        return;
    
    // Check for cd.
    if(strcmp(listOfArgs[0], "cd")==0) {
        cd(totalCommands, listOfArgs[1]);
    }
}