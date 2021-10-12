#include "main.h"

void cd(long long int numArgs, char *commandArgument) {

    // Throw an error if no. of Arguments to the cd command > 2
    if (numArgs > 2) {
        printf(stderr, "Error : too many arguments have been passed!");
        return;
    }

    // Means we have to move to the home directory as only cd is passed
    if (numArgs == 1) {

        // Get the current directory
        getCurrentDirectory();
        strcpy(pseudoHome, currentDir);
        if(chdir(pseudoHome) < 0){
            perror("cd ");
            return;
        }
        strcpy(lastCD, currentDir);
    }

    // Means we have 2 arguments to the command.
    else {
        // Case - Move to the pseudoHome
        if(strcmp(commandArgument, "~") == 0) {
            if(chdir(pseudoHome) < 0) {
                perror("cd ");
                return;
            }
            strcpy(lastCD, currentDir);
            getCurrentDirectory();
            
        }

        // Case - When we have to store the last cd as well.
        else if (strcmp(commandArgument, "-") == 0) {
            printf("%s\n", lastCD);
            if(chdir(lastCD) < 0) {
                perror("cd ");
                return;
            }
            strcpy(lastCD, currentDir);
        }

        // Else move to the directory specified
        else {
            if (chdir(commandArgument) < 0) {
                perror("cd ");
                return;
            }
            strcpy(lastCD, currentDir);
            getCurrentDirectory();
        }
     
    }
    return;
}