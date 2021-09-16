#include "main.h"

// Stores the path of the executable file
char executablePath[SIZE];

pid_t getMyPID(long long int totalArgsInEachCommand, char *listofArgs[]) {

    // If no. of arguments == 2, convert the pid from string to integer.
    if (totalArgsInEachCommand == 2)
        return atoi(listOfArgs[1]);
    
    // else return the pid from the getpid function.
    return getpid();
}

void printExecutableName() {
    
    // strstr - returns the first pointer of the non-matched character
    char *relativePath = strstr(executablePath, pseudoHome);
	if (relativePath != NULL)
	{
		relativePath += strlen(pseudoHome);
		printf("Executable Path -- ~%s\n", relativePath);
	}
	else
	{
		printf("Executable Path -- %s\n", executablePath);
	}
    return;  
}



void pinfo(long long int totalArgsInEachCommand, char *listofArgs[]) {

    // Check if the no. of arguments > 2
    if (totalArgsInEachCommand > 2) {
        printf(stderr, "Too many arguments");
        return;
    }

    // getting the PID
    pid_t pid = getMyPID(totalArgsInEachCommand, listOfArgs);

    // Check for the error
    if(pid == 0){
        printf(stderr,"Invalid process ID\n");
        return;
    }

    char pStatus;
    long long int pMemory;

    // Now look for the pid in the proc file
    char procFile[SIZE];
    sprintf(procFile, "/proc/%d/stat", pid);


    char exeFile[SIZE];
    
    sprintf(exeFile, "/proc/%d/exe", pid);

    
    FILE  *procfileDescriptor = fopen(procFile, "r");
    if(procfileDescriptor == NULL) {
        fprintf(stderr,"Process with ID %d does not exist!\n",(int)pid);
        return;
    } 
    
    // Else print this
    fscanf(procfileDescriptor, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &pStatus, &pMemory);
    fclose(procfileDescriptor);
    printf("PID -- %d\n", pid);
    printf("Process Status -- %c\n", pStatus);
    printf("Memory -- %lld\n", pMemory);
    
    int length = readlink(exeFile, executablePath, sizeof(executablePath));
    if(length < 0){
        fprintf(stderr,"No path for executable file of process ID %d found!\n", (int)pid);
    }
    else{
        executablePath[length] = '\0';

        // Check if the pseudoHome is present in executable path
        printExecutableName();
    }

}
