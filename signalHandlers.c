#include "main.h"


// For Ctrl + C
void ctrlCHandler(int sig) {
    signal(sig, SIG_IGN);
}


// For Ctrl + Z
void ctrlZHandler(int sig) {
    signal(sig, SIG_IGN);
}

// For checking if a process ended or not.
void sigchildHandler() {
    pid_t pid;
    int status;

    pid = waitpid(-1, &status, WNOHANG);

    // Check if its a valid process
    if (pid < 0) {
        printf(stderr,"Invalid process ID\n");
        return;
    }

    else {
        for(ll i = 0; i < totalNoOfProcesses; i++){

            if((ll)pid == processesIndex[i]) { 

                // check if its a background process.
                if (processesStatus[i] != -1) {
                    processesStatus[i] = -1;
                    // [1]+  Done                    gedit
                    // printf("Process %s with process ID [%lld] stopped with exit status %d\n",processesNames[i], (ll)pid,status); // throw a message
                    printf("%s with pid %lld exited normally with exit status %d\n",   processesNames[i], processesIndex[i], status); // throw a message
                    
                    break;
                }
            }
        }
    }
    return;
}


