#include "main.h"


// takes input from the terminal
void getInputToTerminal(){     
    inputGiven = (char *)malloc(SIZE);

    // Checking memory allocation error
    if(inputGiven == NULL){
        printf("Oops! Memory Error!\n");
        return;
    }

    // Taking Input
    char * checkError = fgets(inputGiven, SIZE, stdin);

    // int checkError = gets(inputGiven);
    if (checkError < 0) {
        printf("Oops! Input Error!\n");
        return;
    } 
    // Condition for CtrlD
    else if (checkError == 0) {
        printf("\n");
        exit(0);
    }
    

    // Checking the clear condition
    if (strcmp(inputGiven, "clear") == 0) {
        clear;
    }
    strcpy(copyOfInput, inputGiven);
}

// stores the current dir to currdir
void getCurrentDirectory() {   
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
     
    // make total no. of processes = 0
    totalNoOfJobs = 0;
    noOfForeProcesses = 0;

    // Loads the history file
    loadHistory(); 

    while (1)
    {   
        // check if any child process terminated
        signal(SIGCHLD, sigchildHandler); 

        // Signal Handlers for CtrlC and Z 
        signal(SIGINT, signalControl);
        signal(SIGTSTP, signalControl);                                               

        // Get current directory
        getCurrentDirectory();
        
        // Prints the welcome message
        printInPrompt();

        // Takes the full command with the arguments
        getInputToTerminal();


        // Checks commands
        commandHandler();

        // writes to history
        if(changeHistory()==0) {                                    
            continue;
        }
 
    }
    return 0;
}
