#include "main.h"

// Permissions we want to give to the output file
#define PERMISSIONS 0644


// This is the function for redirection
int redirectionHandler(ll totalArgsInEachCommand, char *listOfArgs[]) {
    
    char inputFile[10000], outputFile[10000];
    int position1 = 0, position2 = 0, position3 = 0;
    int inputDup, outputDup;
    int pos = 100;
    int inputfd, outputfd;

    // Check for the first positions of all the <, >, >>.
	for(int i = 0; i < totalArgsInEachCommand; i++) {
		if(strcmp(listOfArgs[i], "<") == 0) position1 = i;
		if(strcmp(listOfArgs[i], ">") == 0) position2 = i;
		if(strcmp(listOfArgs[i], ">>") == 0) position3 = i;
	}

	// Case - 1
	if(position1 != 0) {
        
		strcpy(inputFile, listOfArgs[position1 + 1]);
		pos = position1;
        listOfArgs[pos] = NULL;
        struct stat tmp;
		if(stat(inputFile, &tmp) < 0) {
			perror("");
			return -1;
		}

		// Storing the input file
		inputDup = dup(STDIN_FILENO);
        if (inputDup < 0) {
            perror("Dup ");
            return -1;
        }

		// Open the input file	
   		inputfd = open(inputFile, O_RDONLY, PERMISSIONS);
		if (inputfd < 0) {
			printf("File doesn't exist!\n");
			return -1;
		}   
		if (dup2(inputfd, STDIN_FILENO)) {
            perror("Dup2 ");
            return -1;
        }
	}
	
	// Case - 2
    if(position2 != 0 || position3 != 0) {
        
        if(position2 + position3 <= pos)
			pos = position2 + position3;
		strcpy(outputFile, listOfArgs[position2 + position3 + 1]);
        listOfArgs[pos] = NULL;
        outputDup = dup(STDOUT_FILENO);
        if (outputDup < 0) {
            perror("Dup ");
            return -1;
        }

		if(position2 != 0)
	    	outputfd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONS);
		else
	    	outputfd = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, PERMISSIONS);

		if (outputfd < 0) {
			printf("File doesn't exist!\n");
			return -1;
		}  

		if(dup2(outputfd, STDOUT_FILENO) < 0)
		{
			perror("Dup2 ");
			return -1;
		}
	}

	// if(position1 != 0) {
	// 	struct stat tmp;
	// 	if(stat(inputFile, &tmp) < 0)
	// 		perror("");

	// 	inputDup = dup(STDIN_FILENO);
    //     if (inputDup < 0) {
    //         perror("Dup ");
    //         exit(1);
    //     }
   	// 	inputfd = open(inputFile, O_RDONLY, PERMISSIONS);
	// 	if (dup2(inputfd, STDIN_FILENO)) {
    //         perror("Dup2 ");
    //         exit(1);
    //     }
	// }

	// if(position2 != 0 || position3 != 0)
	// {
	// 	outputDup = dup(STDOUT_FILENO);
    //     if (outputDup < 0) {
    //         perror("Dup ");
    //         exit(1);
    //     }

	// 	if(position2 != 0)
	//     	outputfd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONS);
	// 	else
	//     	outputfd = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, PERMISSIONS);

	// 	if(dup2(outputfd, STDOUT_FILENO) < 0)
	// 	{
	// 		perror("Dup2 ");
	// 		exit(1);
	// 	}
	// }

	// Forking the process
	pid_t pidValue;
	pidValue = fork();
	if(pidValue < 0) {
		close(outputfd);
		perror("Fork ");
		return -1;
	}
	if(pidValue == 0) {
		if(execvp(listOfArgs[0], listOfArgs) < 0) {
			perror("Execvp ");
			return -1;
		}
	}
	else {
		wait(NULL);
		dup2(inputDup, STDIN_FILENO);
		dup2(outputDup, STDOUT_FILENO);
	}   
	return 0;
}

// This function checks if redirection is possible
int checkRedirection(ll totalArgsInEachCommand, char *listOfArgs[]) {
    for (int i = 0; i < totalArgsInEachCommand; i++) {
        if (strcmp(listOfArgs[i], "<") == 0)
            return 1;
        else if(strcmp(listOfArgs[i], ">") == 0)
            return 1;
        else if(strcmp(listOfArgs[i], ">>") == 0 )
            return 1;
    }
    return 0;

}