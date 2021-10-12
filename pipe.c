#include "main.h"

// Checks if pipe is present or not
int checkPiping(char* listOfArgs[], ll totalArgsInEachCommand) {
    for (int i = 0; i < totalArgsInEachCommand; i++) {
        if (strcmp(listOfArgs[i], "|") == 0)
            return 1;
    }
    return 0;
}

// Counts the total spaces
ll countSpaces(char *str) {
	ll sp = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') 
			sp++;
	}
	return sp;
}

// This function implement the piping functionality
void piping(char *command, char* listOfArgs[], long long totalArgsInEachCommand) {
    // printf("%s\n", command);
    char* pipedCommand[10000];
    ll numPipeCommands = 0;

    // Split commands the on basis of |
    tokenizer(pipedCommand, command, "|", &numPipeCommands);

    // File descriptor
    int fd[2];

    // Storing the original Input & output filedescriptors
    int originalInput = dup(STDIN_FILENO);
    int originalOutput = dup(STDOUT_FILENO);

    // Calling on each command
    for (int i = 0; i  < numPipeCommands; i++) {
        ll lenOfEachPipeCommand = 0;
        char *spaceSepPipedCommand[10000];

        // Tokenizing each command on basis of space, tab and newline
        tokenizer(spaceSepPipedCommand, pipedCommand[i], " \t\n", &lenOfEachPipeCommand);
        
        // Case - 1
        if (i == 0) {
            pipe(fd);
            if(dup2(fd[1], STDOUT_FILENO) < 0) {
                printf("error in dup2\n");
                return;
            }
            close(fd[1]);
        }
        // Case - 2
        else if(i == numPipeCommands - 1) {
            dup2(fd[0], STDIN_FILENO);
            dup2(originalOutput,1);

        }
        // Case - 3
        else {
            dup2(fd[0], STDIN_FILENO);
            pipe(fd);
            if(dup2(fd[1], STDOUT_FILENO) < 0) {
                printf("error in dup2\n");
                return;
            }
            close(fd[1]);

        }

        // Fork the process
        int returnedFork = fork();
        int stat;
        if(returnedFork < 0) {
            printf("failed to fork\n");
        }
        else if(returnedFork == 0) {
            if(checkRedirection(lenOfEachPipeCommand, spaceSepPipedCommand) == 1) {
                redirectionHandler(lenOfEachPipeCommand, spaceSepPipedCommand);
            }
            else {
                execvp(spaceSepPipedCommand[0], spaceSepPipedCommand);
            }
            exit(0);
        }
        else {
            waitpid(returnedFork, &stat, WUNTRACED);
            dup2(originalInput, STDIN_FILENO);
            dup2(originalOutput, STDOUT_FILENO);
        }

    }
    

    return;

}

