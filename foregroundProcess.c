#include "main.h"

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

void fgParentHandler(ll pid, char *repeatArgs[]) {
    char fgCommand[SIZE];
    strcpy(fgCommand, repeatArgs[0]);
    
    int status;

    // waits for child process(fg)
    // Here WUNTRACED uis used as the status is sent back even if the child is stopped by ctrlZ (i.e. not killed)
    waitpid(pid, &status, WUNTRACED);

    // For passing the control to signal
    tcsetpgrp(STDIN_FILENO, getpgid(0));

    // Setting the default behaviours.
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
        

    if(WIFSTOPPED(status)){   // if child is stopped(not killed) by ctrl-z, we can check that by this macro!
        int len = strlen(fgCommand);
         
        processesIndex[totalNoOfProcesses] = pid;                // push created child to jobs as its suspended in background!
        processesNames[totalNoOfProcesses] = malloc(len * sizeof(char));
        
        strcpy(processesNames[totalNoOfProcesses], fgCommand);
        processesStatus[totalNoOfProcesses] = 1;

        totalNoOfProcesses++;
        printf("Process %s with process ID [%lld] suspended\n", fgCommand, (ll)pid );
        return;
    }else{
        printf("Process %s with process ID [%lld] exited normally\n", fgCommand, (ll)pid );
    }
    
}


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
    else if (pid == 0){
        // // fgChildHandler(totalArgsInEachCommand, &repeatArgs);
        // // Make the child process as the leader of the new group of processes.
        // // Setting the process ID of child = Process ID of group
        // setpgid(0, 0);

        // // Removing the last '&' as we need the name
        // repeatArgs[totalArgsInEachCommand] = NULL;

        // // For passing the control to signal
        // tcsetpgrp(STDIN_FILENO, getpgid(0));

        // // Since the child has become the leader, so now give the control back to the 
        // // default signals. SIGINT - Ctrl + C(Interrupt handler)
        // signal(SIGINT, SIG_DFL);

        // // Causes the system to set the default signal handler for the given signal
        // // Ctrl + Z.
        // signal(SIGTSTP, SIG_DFL);

        // // Overlay's a process that has been created by a call to the fork function.
        // // Execute the files.
        // ll check_execvp = execvp(repeatArgs[0], repeatArgs);     
        
        // // Check for the errors.
        // if(check_execvp < 0){
        //     printf("Invalid command!\n");
        //     exit(EXIT_FAILURE);
        // }
        // exit(EXIT_SUCCESS);
        fgChildHandler(totalArgsInEachCommand, repeatArgs);

    }

    // Means PID > 0, i.e. the parent's process
    else {
        if (kill(pid, SIGCONT) < 0) {
            perror("Could not run background process");
            return;
        }
        fgParentHandler(pid, repeatArgs);

    //     char fgCommand[SIZE];
    //     strcpy(fgCommand, repeatArgs[0]);
    //     int status;

    //     // waits for child process(fg)
    //     // Here WUNTRACED uis used as the status is sent back even if the child is stopped by ctrlZ (i.e. not killed)
    //     waitpid(pid, &status, WUNTRACED);

    //     // For passing the control to signal
    //     tcsetpgrp(STDIN_FILENO, getpgid(0));

    //     // Setting the default behaviours.
    //     signal(SIGTTIN, SIG_DFL);
    //     signal(SIGTTOU, SIG_DFL);

    //     if(WIFSTOPPED(status)){   // if child is stopped(not killed) by ctrl-z, we can check that by this macro!
            
    //         int len = strlen(fgCommand);
            
    //         processesIndex[totalNoOfProcesses] = pid;                // push created child to jobs as its suspended in background!
    //         processesNames[totalNoOfProcesses] = malloc(len * sizeof(char));
            
    //         strcpy(processesNames[totalNoOfProcesses], fgCommand);
    //         processesStatus[totalNoOfProcesses] = 1;

    //         totalNoOfProcesses++;
    //         printf("Process %s with process ID [%lld] suspended\n", fgCommand, (ll)pid );
    //         return;
    //     }
    // }
    // return;
    }

}


