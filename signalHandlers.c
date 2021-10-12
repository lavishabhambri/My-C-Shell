#include "main.h"

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
        for(ll i = 0; i < totalNoOfJobs; i++){

            if((ll)pid == myJobs[i].pid) { 

                // check if its a background process.
                if (myJobs[i].jobsStatus != -1) {
                    myJobs[i].jobsStatus = -1;
                        printf("%s with pid %lld exited normally with exit status %d\n",   myJobs[i].jobsNames, myJobs[i].pid, status); 
                    
                    break;
                }
            }
        }
    }
    return;
}

// This is the signal controller for CTRL+C and CTRL+Z
void signalControl(int signal)
{
    if(fgJob.pid > 0)
    {
        myJobs[totalNoOfJobs].pid = fgJob.pid;
        strcpy(myJobs[totalNoOfJobs].jobsNames,fgJob.jobsNames);
        myJobs[totalNoOfJobs].jobsIndex = totalNoOfJobs;
        myJobs[totalNoOfJobs].jobsStatus = 1;

        myJobsTemp[totalNoOfJobs].pid = fgJob.pid;
        strcpy(myJobsTemp[totalNoOfJobs].jobsNames, fgJob.jobsNames);
        myJobsTemp[totalNoOfJobs].jobsIndex = totalNoOfJobs;
        myJobsTemp[totalNoOfJobs].jobsStatus = 1;

        totalNoOfJobs++;

  		kill(fgJob.pid , signal);
        fgJob.pid = -1;
        printf("\n");
    }
    else
    {
        printf("\nNo foreground process found\n");
        printf("Press [ENTER] to continue\n");
    }
}