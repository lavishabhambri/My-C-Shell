#include "main.h"

// When the child is called
int fgChildHandler(ll totalArgsInEachCommand, char *repeatArgs[]) {
    // Make the child process as the leader of the new group of processes.
    // Setting the process ID of child = Process ID of group
    setpgid(0, 0);

    // Removing the last '&' as we need the name
    repeatArgs[totalArgsInEachCommand] = NULL;

    // For passing the control to signal
    tcsetpgrp(STDIN_FILENO, getpgid(0));

    // Since the child has become the leader, so now give the control back to the 
    // default signals. SIGINT - Ctrl + C(Interrupt handler)
    signal(SIGINT, SIG_DFL);

    // Causes the system to set the default signal handler for the given signal
    // Ctrl + Z.
    signal(SIGTSTP, SIG_DFL);

    // Overlay's a process that has been created by a call to the fork function.
    // Execute the files.
    ll check_execvp = execvp(repeatArgs[0], repeatArgs);     
    
    // Check for the errors.
    if(check_execvp < 0){
        printf("Invalid command!\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}


void fgParentHandler(ll pid, char *repeatArgs[], int totalArgsInEachCommand) {
    // When the parent is called
    char fgCommand[SIZE];
    strcpy(fgCommand, "");
    strcat(fgCommand, repeatArgs[0]);
    
    fgJob.pid = pid;
    fgJob.jobsNames = malloc(strlen(repeatArgs[0]) * sizeof(char));
    strcpy(fgJob.jobsNames, repeatArgs[0]);
    fgJob.jobsIndex = 0;
            
    int status;
    // waits for child process(fg)
    // Here WUNTRACED uis used as the status is sent back even if the child is stopped by ctrlZ (i.e. not killed)
    if (waitpid(pid, &status, WUNTRACED) < 0)
        printf("Invalid command");

    fgJob.pid = -1;
    

    // For passing the control to signal
    tcsetpgrp(STDIN_FILENO, getpgid(0));


    // Setting the default behaviours.
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    if(WIFSTOPPED(status)){   // if child is stopped(not killed) by ctrl-z, we can check that by this macro!
        int len = strlen(fgCommand);
        for (int i = 1; i < totalArgsInEachCommand - 1; i++) {
            len += strlen(repeatArgs[i]);
        }

        // push created child to jobs as its suspended in background!
        myJobs[totalNoOfJobs].pid = pid;
        myJobs[totalNoOfJobs].jobsNames = malloc(len * sizeof(char));
        // strcpy(myJobs[totalNoOfJobs].jobsNames, fgCommand);
        myJobs[totalNoOfJobs].jobsStatus = 1;    
        myJobs[totalNoOfJobs].jobsIndex = totalNoOfJobs;
        
        // Store in the temp array as well
        myJobsTemp[totalNoOfJobs].pid = pid;
        myJobsTemp[totalNoOfJobs].jobsNames = malloc(len * sizeof(char));
        // strcpy(myJobsTemp[totalNoOfJobs].jobsNames, fgCommand);
        myJobsTemp[totalNoOfJobs].jobsStatus = 1;    
        myJobsTemp[totalNoOfJobs].jobsIndex = totalNoOfJobs;

        strcpy(myJobs[totalNoOfJobs].jobsNames, repeatArgs[0]);
        strcpy(myJobsTemp[totalNoOfJobs].jobsNames, repeatArgs[0]);
        // Copy the commandName in the processesNames array
        for (int i = 1; i < totalArgsInEachCommand-1; i++) {
            strcat(myJobs[totalNoOfJobs].jobsNames, " ");
            strcat(myJobsTemp[totalNoOfJobs].jobsNames, " ");
            strcat(myJobs[totalNoOfJobs].jobsNames, listOfArgs[i]);
            strcat(myJobsTemp[totalNoOfJobs].jobsNames, listOfArgs[i]);
        }

        // Now increase the total no. of jobs present
        totalNoOfJobs++;


        // For the + thing.
        foreProcessesID[noOfForeProcesses] = pid;
        noOfForeProcesses++;
        
        printf("Process %s with process ID [%lld] suspended\n", fgCommand, (ll)pid );
        return;
    }else{
            if (status == 1)
        printf("Process %s with process ID [%lld] exited normally\n", fgCommand, (ll)pid );
    }
    
}

// This function calls the command which is not explicitly written by me
void foregroundProcess(long long int totalArgsInEachCommand, char *repeatArgs[]) {
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);


    // Forking child process
    ll pid = fork();

    // Checking for error
    if (pid < 0) {
        printf("Unable to fork");
        return;
    }
    // Sending the child process to background
    else if (pid == 0) {
        fgChildHandler(totalArgsInEachCommand, repeatArgs);

    }

    // Means PID > 0, i.e. the parent's process
    else {

        fgParentHandler(pid, repeatArgs, totalArgsInEachCommand);
        
    }

}

