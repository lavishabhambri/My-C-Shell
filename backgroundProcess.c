#include "main.h"

// void bgChildHandler(ll totalArgsInEachCommand, char *listofArgs[]) {

//     // Make the child process as the leader of the new group of processes.
//     // Setting the process ID of child = Process ID of group
//     setpgid(0, 0);

//     // Removing the last '&' as we need the name
//     listOfArgs[totalArgsInEachCommand - 1] = NULL;

//     // Since the child has become the leader, so now give the control back to the 
//     // default signals. SIGINT - Ctrl + C(Interrupt handler)
//     signal(SIGINT, SIG_DFL);

//     // Causes the system to set the default signal handler for the given signal
//     // Ctrl + Z.
//     signal(SIGTSTP, SIG_DFL);

//     // Returns of calling process(i.e. the group leader)
//     pid_t pidVal = getpid();

//     // Overlay's a process that has been created by a call to the fork function.
//     // Execute the files.
//     ll check_execvp = execvp(listOfArgs[0], listOfArgs);     
    
//     // Check for the errors.
//     if(check_execvp < 0){
//         printf("Invalid command!\n");
//         exit(1);
//     }

//     exit(0);
// }

// void bgParentHandler(pid_t pid) {
//     // Now store the process details in the processes Arrays
//     // Store pid
//     processesIndex[totalNoOfProcesses] = pid;

//     // Get length of the command
//     ll lengthOfCommand = strlen(listOfArgs[0]);

//     // create a space in memory
//     processesNames[totalNoOfProcesses] = (char *) malloc(lengthOfCommand * sizeof(char));

//     // Copy command into this array
//     strcpy(processesNames[totalNoOfProcesses], listOfArgs[0]);

//     // Update the status to 1
//     processesStatus[totalNoOfProcesses] = 1;

//     // Inc no. of processes by 1
//     totalNoOfProcesses++;

//     printf("[%lld]\n", processesIndex[totalNoOfProcesses - 1]);
//     return;
// }


// void backgroundProcess(long long int totalArgsInEachCommand, char *listofArgs[]) {
    
//     // Forking child process
//     pid_t pid = fork();

//     // Checking for error
//     if (pid < 0) {
//         printf("Unable to fork");
//         return;
//     }
//     // Sending the child process to background
//     else if (pid == 0){

//         bgChildHandler(totalArgsInEachCommand, &listOfArgs);
//     }

//     // Means PID > 0, i.e. the parent's process
//     else {

//         if (kill(pid, SIGCONT) < 0) {
//             perror("Could not run background process");
//             return;
//         }

//         bgParentHandler(pid);
//     }
    
// }



// This is the function for running a background process, i.e a command ending with &
void backgroundProcess(long long totalArgsInEachCommand, char *listOfArgs[]) {

    // Forking child process
    ll forkReturnedValue = fork();

    if(forkReturnedValue < 0) {
        fprintf(stderr, "Unable to fork\n");
        return;
    }

    // Sending the child process to background
    if(forkReturnedValue == 0) {   
        
        // Make the child process as the leader of the new group of Jobs.
        // Setting the process ID of group = Process ID of child                                            
        setpgrp();   

        // Removing the last '&' as we need the name                                          
        listOfArgs[totalArgsInEachCommand - 1] = NULL;
        
        // Since the child has become the leader, so now give the control back to the 
        // default signals. SIGINT - Ctrl + C(Interrupt handler)
        signal(SIGINT, SIG_DFL);

        // Causes the system to set the default signal handler for the given signal
        // Ctrl + Z.
        signal(SIGTSTP, SIG_DFL);

        // Returns of calling process (i.e. the group leader)
        pid_t pid = getpid();

        // Overlay's a process that has been created by a call to the fork function.
        // Execute the execuateble files.
        ll execcvpReturnedValue = execvp(listOfArgs[0], listOfArgs);  

        // Check for the errors.                        
        if(execcvpReturnedValue < 0){
            fprintf(stderr, "Invalid command!\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    // Handle the parent process
    else {
        ll len = strlen(listOfArgs[0]);  
        for (int i = 1; i < totalArgsInEachCommand - 1; i++) {
            len += strlen(listOfArgs[i]);
        }                                 
        
        // Now store the process details in the Jobs Arrays
        // Store pid
        myJobs[totalNoOfJobs].pid = forkReturnedValue;
        myJobsTemp[totalNoOfJobs].pid = forkReturnedValue;
        
        // create a space in memory
        myJobs[totalNoOfJobs].jobsNames = malloc(len * sizeof(char));
        myJobsTemp[totalNoOfJobs].jobsNames = malloc(len * sizeof(char));

        // Check for errors
        if(listOfArgs[0] == NULL){
            fprintf(stderr, "Memory Error!\n");
        }

        strcpy(myJobs[totalNoOfJobs].jobsNames, listOfArgs[0]);
        strcpy(myJobsTemp[totalNoOfJobs].jobsNames, listOfArgs[0]);
        // Copy the commandName in the processesNames array
        for (int i = 1; i < totalArgsInEachCommand-1; i++) {
            strcat(myJobs[totalNoOfJobs].jobsNames, " ");
            strcat(myJobsTemp[totalNoOfJobs].jobsNames, " ");
            strcat(myJobs[totalNoOfJobs].jobsNames, listOfArgs[i]);
            strcat(myJobsTemp[totalNoOfJobs].jobsNames, listOfArgs[i]);
        }

        // Set status of bg processes as 1
        myJobs[totalNoOfJobs].jobsStatus = 1;
        myJobsTemp[totalNoOfJobs].jobsStatus = 1;

        // Store index
        myJobs[totalNoOfJobs].jobsIndex = totalNoOfJobs;
        myJobsTemp[totalNoOfJobs].jobsIndex = totalNoOfJobs;

        // Increase the total no of processes
        totalNoOfJobs++;

        // Print the ID
        fprintf(stderr,"[%lld] started\n", myJobs[totalNoOfJobs-1].pid);
        return;
    }
}
