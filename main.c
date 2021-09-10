#include "main.h"



void getInputToTerminal(){     // fetches command from terminal
    inputGiven = (char *)malloc(SIZE);

    if(inputGiven == NULL){
        fprintf(stderr,"Oops! Memory Error!\n");
    }
    int checkError = gets(inputGiven);
    if (checkError == -1) {
        // overkill();
        exit(0);
    }
    if (strcmp(inputGiven, "clear") == 0) {
        clear;
    }
}

void getCommand() {
    command = (char *)malloc(SIZE);

    if(command == NULL){
        fprintf(stderr,"Oops! Memory Error!\n");
    }
    int length = strlen(inputGiven);
    for (int i = 0; i < length; i++) {
        if (inputGiven[i] == ' ') {
            break;
        }else {
            command[i] = inputGiven[i];
        }
    }
}

void getCurrentDirectory(){     // stores the current dir to currdir
    if(getcwd(currentDir, SIZE) == NULL) {
        perror("");
        exit(0);
    }
    // tilda_adder(currentDir);
    return;
}

void getHomeDirectory(){     // stores home dir to homedir
    if(getcwd(homeDir, SIZE) == NULL) {
        perror("");
        exit(0);
    }
    return;
}

void storePreviousPath() {
    getCurrentDirectory();
    getHomeDirectory();
    strcpy(previousDir, homeDir);
}



int main()
{
    welcomePrompt();
    while (1)
    {   
        getCurrentDirectory();
        getHomeDirectory();

        // Prints the welcome message
        promptPrint();

        

        // Takes the full command with the arguments
        getInputToTerminal();

        // Stores the path of the previous directory
        storePreviousPath();

        // Store the command
        getCommand();

        // Check commands
        if (strcmp(inputGiven, "cd") == 0) {
            cd(3, currentDir);
        }

        
        
    }
}
