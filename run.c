#include "main.h"

// This executes the various commands entered by the user.
void commandHandler() {
    long long int noOfCommands = 0;
    tokenizer(listOfCommands, inputGiven, ";\n", &noOfCommands);

    for (int i = 0; i < noOfCommands; i++) {
        char tempStr[10000];
        strcpy(tempStr, listOfCommands[i]);


        long long int totalArgsInEachCommand = 0;
        tokenizer(listOfArgs, listOfCommands[i], " \t", &totalArgsInEachCommand);

        // Check piping
        if(checkPiping(listOfArgs, totalArgsInEachCommand) == 1){ //tokenize pipe commands
			piping(tempStr, listOfArgs, totalArgsInEachCommand);
		}
        else {
            // Check redirection
            int returnedRedirectionValue = checkRedirection(totalArgsInEachCommand, listOfArgs);
            if (returnedRedirectionValue == 1) {
                // printf("Yes\n");
                redirectionHandler(totalArgsInEachCommand, listOfArgs);
            }
            
            // If the list is empty then simply return
            else {

                if (totalArgsInEachCommand == 0 || listOfArgs[0] == NULL) 
                    return;

                // Checking the background process (if at last we have &)
                else if(strcmp(listOfArgs[totalArgsInEachCommand - 1],"&")==0){
                    backgroundProcess(totalArgsInEachCommand, listOfArgs);
                    // return;
                }
                
                // Check for cd.
                else if(strcmp(listOfArgs[0], "cd") == 0) {
                    cd(totalArgsInEachCommand, listOfArgs[1]);
                }


                // Check for pwd
                else if(strcmp(listOfArgs[0], "pwd") == 0) {
                    // the no. of arguments should be = 1
                    if (totalArgsInEachCommand != 1) {
                        printf("Error : too many arguments have been passed!");
                        return;
                    }
                    pwd();
                }

                // Check for echo
                else if(strcmp(listOfArgs[0], "echo") == 0) {
                    echo(totalArgsInEachCommand, listOfArgs);
                }

                // Check for ls
                else if(strcmp(listOfArgs[0], "ls") == 0) {
                    ls(totalArgsInEachCommand, listOfArgs);
                }

                // Check for pinfo
                else if(strcmp(listOfArgs[0], "pinfo") == 0) {
                    pinfo(totalArgsInEachCommand, listOfArgs);
                }


                // Check for exit
                else if(strcmp(listOfArgs[0], "exit") == 0) {
                    if(changeHistory() == 0){                                    
                        continue;
                    }
                    exit(0);
                }

                // Check for repeat
                else if(strcmp(listOfArgs[0], "repeat") == 0) {
                    repeat(totalArgsInEachCommand, listOfArgs);
                }

                // Check for history
                else if(strcmp(listOfArgs[0], "history") == 0) {
                    history(totalArgsInEachCommand, listOfArgs);
                }

                // Check for jobs
                else if(strcmp(listOfArgs[0], "jobs") == 0) {
                    jobs(totalArgsInEachCommand, listOfArgs);
                }

                // Check for bg
                else if(strcmp(listOfArgs[0], "bg") == 0) {
                    bg(totalArgsInEachCommand, listOfArgs);
                }

                // Check for fg
                else if(strcmp(listOfArgs[0], "fg") == 0) {
                    fg(totalArgsInEachCommand, listOfArgs);
                }

                // Check for sig
                else if(strcmp(listOfArgs[0], "sig") == 0) {
                    sig(totalArgsInEachCommand, listOfArgs);
                }

                // Check for replay
                else if(strcmp(listOfArgs[0], "replay") == 0) {
                    replay(totalArgsInEachCommand, listOfArgs);
                }

                // Bonus Dirty command
                else if(strcmp(listOfArgs[0], "baywatch") == 0 && strcmp(listOfArgs[totalArgsInEachCommand-1], "dirty") == 0) {
                    dirty(totalArgsInEachCommand, listOfArgs);
                }

                // Bonus Interrupt command
                else if(strcmp(listOfArgs[0], "baywatch") == 0 && strcmp(listOfArgs[totalArgsInEachCommand-1], "interrupt") == 0) {
                    interrupt(totalArgsInEachCommand, listOfArgs);
                }

                // Bonus Newborn command
                else if(strcmp(listOfArgs[0], "baywatch") == 0 && strcmp(listOfArgs[totalArgsInEachCommand-1], "newborn") == 0) {
                    newborn(totalArgsInEachCommand, listOfArgs);
                }


                else {
                    foregroundProcess(totalArgsInEachCommand, listOfArgs);
                }
            }
        }
            // check if any child process terminated
            signal(SIGCHLD, sigchildHandler); 
        }


    return;
}

