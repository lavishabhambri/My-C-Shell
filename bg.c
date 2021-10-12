#include "main.h"

// This is the function for bring a process in background via its id
void bg(ll totalArgsInEachCommand, char *listOfArgs[]) {

    // Checking errors
    if(totalArgsInEachCommand <= 1) {
        printf("Too few arguments!\n");
        return;
    }
    else if(totalArgsInEachCommand > 2){
        printf("Too many arguments!\n");
        return;
    }
    
    else {
        ll indexOfRequiredJob = atoi(listOfArgs[1]);
        
        // Check if the process exists or not
        if(indexOfRequiredJob > totalNoOfJobs || indexOfRequiredJob < 1 || myJobs[indexOfRequiredJob - 1].pid  == -1){
            printf("Process doesn't exist!\n");
            return;
        }

        pid_t childPid = myJobs[indexOfRequiredJob - 1].pid;

        // Giving signal to the child, ie send the signal SIGCONT, kill the child process
        ll killReturnedValue = kill(childPid, SIGCONT);
        
        // Check error in killing
        if(killReturnedValue < 0){              
            perror("bg ");
            return;
        }
        return;
    }
}