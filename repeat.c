#include "main.h"

void repeat (long long int totalArgsInEachCommand, char *listofArgs[]) {

    // Return if no. of args < 3
    if (totalArgsInEachCommand < 3) {
        printf(stderr, "Too less arguments\n");
        return;
    }

    ll repeatTimes = atoi(listOfArgs[1]);

    char repeatCommand[SIZE];
    strcpy(repeatCommand, listOfArgs[2]);

    for (int i = 3; i < totalArgsInEachCommand; i++)
        strcat(repeatCommand, listOfArgs[i]);

    
    
    for (int i = 0; i < repeatTimes; i++) {
        pid_t pid = fork();

        // Checking for error
        if (pid < 0) {
            printf(stderr, "Unable to fork");
            return;
        }

        ll check_execvp = execvp(repeatCommand, repeatCommand); 

        if(check_execvp < 0){
            printf(stderr, "Invalid command!\n");
            exit(1);
        }
    }
    return;
    

}