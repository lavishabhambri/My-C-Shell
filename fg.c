#include "main.h"

// Returns 1 for invalid process, else 0
int checkForInvalidProcess(ll currentProcessIndex) {
    if(currentProcessIndex > totalNoOfProcesses || currentProcessIndex <= 0 || processesStatus[currentProcessIndex-1] == -1){
        return 1;
    }
    return 0;
}

// This func sets the terminal signals to default
void defaultSignals() {
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
}


void fg(long long int totalArgsInEachCommand, char *listofArgs[]) {

    // Only 2 arguments can be passed for fg
    if(totalArgsInEachCommand != 2){
        printf("Incorrect number of arguments\n");
        return;
    }

    else{

        // Convert the string into integer
        ll currentProcessIndex = atoi(listOfArgs[1]);

        if (checkForInvalidProcess(currentProcessIndex) == 1) {
            printf("Invalid process\n");
            return;
        }
        
        // Group ID of child
        pid_t childPgid = getpgid(processesIndex[currentProcessIndex - 1]);

        // PID of child
        pid_t childPid = processesIndex[currentProcessIndex - 1];
        
        pid_t currentPgid = getpgrp();

        // Remove process from backprocess Array
        processesStatus[currentProcessIndex - 1] = -1; 

        // Ignore the access of the terminal
        signal(SIGTTOU,SIG_IGN);    
        signal(SIGTTIN,SIG_IGN);


        printf("[%lld] %s resumed\n", processesIndex[currentProcessIndex - 1],processesNames[currentProcessIndex - 1]);   // throw resume msg


        // Passing the access of terminal to child
        if(tcsetpgrp(STDIN_FILENO, childPgid) < 0) {   
            processesStatus[currentProcessIndex - 1]=1;
            perror("tcsetpgrp ");
            defaultSignals();
            return;
        };


        if(kill(childPid, SIGCONT) < 0) {
            processesStatus[currentProcessIndex - 1] = 1;
            perror("kill ");
            defaultSignals();
            return;
        }

        int status;
        waitpid(childPid, &status, WUNTRACED);   // wait for the process
        tcsetpgrp(0, currentPgid);                 // take the terminal back
        defaultSignals();

        // Check for ctrlZ i.e. if the process is suspended
        if(WIFSTOPPED(status)) {                 
            printf("Process %s with process ID [%lld] suspended\n", processesNames[currentProcessIndex - 1], processesIndex[currentProcessIndex - 1]);
            
            // Make as foreground
            processesStatus[currentProcessIndex - 1] = 1;
        }
        return;
    }
}
