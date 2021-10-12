#include "main.h"

// Checks error
int checkErrorsInSig(ll totalArgsInEachCommand) {
    if(totalArgsInEachCommand <= 2) {
        printf("Too few arguments!\n");
        return 0;
    }

    else if(totalArgsInEachCommand > 3) {
        printf("Too many arguments!\n");
        return 0;
    }
    return 1;
}

// set the terminal signals to default
void callSignalsInSig() {
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
}

void sig(ll totalArgsInEachCommand, char *listOfArgs[]) {

    useconds_t usec = 1000;
    usleep(usec);

    // Check for the errors
    if (checkErrorsInSig(totalArgsInEachCommand) == 0) 
        return; 
    else {
        ll indexOfRequiredJob = atoi(listOfArgs[1]);
        ll signalNumber = atoi(listOfArgs[2]);

        if(indexOfRequiredJob <= 0 || indexOfRequiredJob > totalNoOfJobs || myJobs[indexOfRequiredJob - 1].jobsStatus == -1) {
            printf("No process exists!\n");
            return;
        }

        // Process IDs of group leader (Child), child ID, currnt ID. 
        pid_t childPgid = getpgid(myJobs[indexOfRequiredJob - 1].pid);
        pid_t childPid = myJobs[indexOfRequiredJob - 1].pid;
        pid_t currPgid = getpgrp();

        // Since the current process is now in fg, so remove from myJobs bg arr
        myJobs[indexOfRequiredJob - 1].jobsStatus = -1;        

        //  Ignore the terminal control signals
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        // callSignalsInSig();

        // Display the resume message
        printf("[%lld] %s resumed\n", myJobs[indexOfRequiredJob - 1].pid, myJobs[indexOfRequiredJob - 1].jobsNames);   


        // pass the terminal to child
        ll tcsetpgrpReturnValue = tcsetpgrp(STDIN_FILENO, childPgid);
        if(tcsetpgrpReturnValue < 0){   
            myJobs[indexOfRequiredJob - 1].jobsStatus = 1;
            perror("tcsetpgrp ");
            callSignalsInSig();
            return;
        };

        if(kill(childPid, signalNumber) < 0) {
            myJobs[indexOfRequiredJob - 1].jobsStatus = 1;
            perror("kill ");
            callSignalsInSig();
            return;
        }

        int status;

        // wait for the process
        waitpid(childPid, &status, WUNTRACED);   

        // take the terminal back
        tcsetpgrp(0, currPgid);                 
        callSignalsInSig();

        // If any process is suspended by ctrl-Z
        if(WIFSTOPPED(status)) {                 
            fprintf(stderr," Process %s with process ID [%lld] suspended\n", myJobs[indexOfRequiredJob - 1].jobsNames, myJobs[indexOfRequiredJob - 1].pid);
            myJobs[indexOfRequiredJob - 1].jobsStatus = 1;
        }
        return;
    }
}
