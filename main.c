#include "main.h"


// takes input from the terminal
void getInputToTerminal(){     
    inputGiven = (char *)malloc(SIZE);

    // Checking memory allocation error
    if(inputGiven == NULL){
        fprintf(stderr,"Oops! Memory Error!\n");
        return;
    }

    // Taking Input
    int checkError = gets(inputGiven);
    if (checkError == -1) {
        fprintf(stderr,"Oops! Input Error!\n");
        return;
    }

    // Checking the clear condition
    if (strcmp(inputGiven, "clear") == 0) {
        clear;
    }
    strcpy(copyOfInput, inputGiven);
}

// stores the current dir to currdir
void getCurrentDirectory(){   
    if(getcwd(currentDir, SIZE) == NULL) {
        perror("");
        exit(0);
    }
    return;
}

// Stores the home directory - initiliazed only once in the whole program.
void getPseudoHome() {
    getCurrentDirectory();
    strcpy(pseudoHome, currentDir);
}


int main()
{
    //Getting the username of the current active user
    getlogin_r(username, sizeof(username)); 

    //Getting the systemname 
    gethostname(systemname, sizeof(systemname));

    // Prints the welcome post.
    welcomePrompt();

    // Store the home initially.
    getPseudoHome();

    // Initially lastCD = home path only.
    strcpy(lastCD, pseudoHome);
     

    while (1)
    {   
        // Get current directory
        getCurrentDirectory();
        
        // Prints the welcome message
        printInPrompt();

        // Takes the full command with the arguments
        getInputToTerminal();

        // Checks commands
        commandHandler();
 
    }
    return 0;
}
