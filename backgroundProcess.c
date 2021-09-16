#include "main.h"
#include <signal.h>

void childHandler(ll totalArgsInEachCommand, char *listofArgs[]) {

    // Make the child process as the leader of the new group of processes.
    // Setting the process ID of child = Process ID of group
    setpgid(0, 0);

    // Removing the last '&' as we need the name
    listOfArgs[totalArgsInEachCommand - 1] = NULL;

    // Since the child has become the leader, so now give the control back to the 
    // default signals. SIGINT - Ctrl + C(Interrupt handler)
    signal(SIGINT, SIG_DFL);

    // Causes the system to set the default signal handler for the given signal
    // Ctrl + Z.
    signal(SIGTSTP, SIG_DFL);

    // Returns of calling process(i.e. the group leader)
    pid_t pidVal = getpid();

    // Overlay's a process that has been created by a call to the fork function.
    // Execute the files.
    ll check_execvp = execvp(listOfArgs[0],listOfArgs);     
    
    // Check for the errors.
    if(check_execvp < 0){
        printf(stderr, "Invalid command!\n");
        exit(1);
    }

    exit(0);
}


void backgroundProcess(long long int totalArgsInEachCommand, char *listofArgs[]) {
    // Only 2 arguments can be passed to '&'
    if (totalArgsInEachCommand != 2) {
        printf(stderr, "Incorrect number of arguments");
        return;
    }
    
    else {
        // Forking child process
        pid_t pid = fork();

        // Checking for error
        if (pid < 0) {
            printf(stderr, "Unable to fork");
            return;
        }
        // Sending the child process to background
        else if (pid == 0){

            childHandler(totalArgsInEachCommand, &listOfArgs);
        }
        // Means PID > 0, i.e. the parent's process
        else {

            // *****************DOUBTS*************
            // if (kill(pid, SIGCONT) < 0) {
            //     perror("Could not run background process");
            //     return;
            // }
            // if (strcmp(token[0], "vim") == 0)
            // kill(p, 19);


            printf("[%d] started %s\n",pid, listOfArgs[0]);
        }
    }
}
