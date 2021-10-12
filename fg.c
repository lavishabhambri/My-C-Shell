#include "main.h"

// Checks for the errors
int checkErrors(ll totalArgsInEachCommand) {
    if(totalArgsInEachCommand <= 1) {
        printf("Too few arguments!\n");
        return 0;
    }

    else if(totalArgsInEachCommand > 2) {
        printf("Too many arguments!\n");
        return 0;
    }
    return 1;
}

// set the terminal signals to default
void callSignals() {
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
}

// This function brings any process to fg by its id
void fg(ll totalArgsInEachCommand, char *listOfArgs[]) {

    useconds_t usec = 1000;
    usleep(usec);

    // Check for the errors
    if (checkErrors(totalArgsInEachCommand) == 0) 
        return; 
    else {
        ll indexOfRequiredJob = atoi(listOfArgs[1]);
        if(indexOfRequiredJob <= 0 || indexOfRequiredJob > totalNoOfJobs || myJobs[indexOfRequiredJob - 1].jobsStatus == -1) {
            printf("No process exists!\n");
            return;
        }
    

        // Process IDs of group leader (Child), child ID, currnt ID. 
        pid_t childPgid = getpgid(myJobs[indexOfRequiredJob].pid);
        pid_t childPid = myJobs[indexOfRequiredJob - 1].pid;
        pid_t currPgid = getpgrp();
        
        // This is the index in the sorted array myJobsTemp
        ll neededIndex = -1;
        
        for (int i = 0; i < totalNoOfJobs; i++) {
            if (myJobs[indexOfRequiredJob - 1].pid == myJobsTemp[i].pid && myJobsTemp[i].jobsStatus != -1) {
                neededIndex = i;
            }
        }
    

        if (neededIndex != -1) {
            // printf("%s %d %d\n", myJobsTemp[neededIndex - 1].jobsNames, myJobsTemp[neededIndex - 1].jobsIndex, neededIndex);

            // Since the current process is now in fg, so remove from myJobs bg arr
            myJobs[indexOfRequiredJob - 1].jobsStatus = -1;        
            myJobsTemp[neededIndex].jobsStatus = -1;        

            //  Ignore the terminal control signals
            signal(SIGTTOU,SIG_IGN);
            signal(SIGTTIN,SIG_IGN);

            // Display the resume message
            printf("[%lld] %s resumed\n", myJobs[indexOfRequiredJob - 1].pid, myJobs[indexOfRequiredJob - 1].jobsNames);   
        

            // pass the terminal to child
            ll tcsetpgrpReturnValue = tcsetpgrp(STDIN_FILENO, childPgid);

            // Check for error
            if(tcsetpgrpReturnValue < 0){   
                myJobs[indexOfRequiredJob - 1].jobsStatus = 1;
                myJobsTemp[neededIndex].jobsStatus = 1;
                perror("tcsetpgrp ");
                callSignals();
                return;
            };

            // Send the SIGCONT signal and kill the child
            if(kill(childPid, SIGCONT) < 0) {
                myJobs[indexOfRequiredJob - 1].jobsStatus = 1;
                myJobsTemp[neededIndex - 1].jobsStatus = 1;
                perror("kill ");
                callSignals();
                return;
            }

            int status;

            // wait for the process
            waitpid(childPid, &status, WUNTRACED);   

            // take the access of the terminal back
            tcsetpgrp(0, currPgid); 
            
            // Set the signals
            callSignals();

            // If any process is suspended by ctrl-Z
            if(WIFSTOPPED(status)) {                 
                fprintf(stderr," Process %s with process ID [%lld] suspended\n", myJobs[indexOfRequiredJob - 1].jobsNames, myJobs[indexOfRequiredJob - 1].pid);
                myJobs[indexOfRequiredJob - 1].jobsStatus = 1;
                myJobsTemp[neededIndex - 1].jobsStatus = 1;
            }
        }else {
            printf("No such process exists!\n");
        }
        return;
    }
}