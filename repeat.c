#include "main.h"

void repeat (long long int totalArgsInEachCommand, char *listofArgs[]) {

    // Return if no. of args < 3
    if (totalArgsInEachCommand < 3) {
        printf(stderr, "Too less arguments\n");
        return;
    }

    ll repeatTimes = atoi(listOfArgs[1]);
    char *args[totalArgsInEachCommand - 2];

    int k=0;
    for (int i = 2; i < totalArgsInEachCommand; i++) {
        int len = strlen(listOfArgs[i]);
        args[k] = (char *)malloc((len + 2) * sizeof(char));
        strcpy(args[k], listOfArgs[i]);
        k++;
    }

    if (strcmp(args[0], "echo") == 0) {
        for (int i = 0; i < repeatTimes; i++) {
            echo(totalArgsInEachCommand - 2, args);
        }
        return;
    }
    else if (strcmp(args[0], "cd") == 0) {
        for (int i = 0; i < repeatTimes; i++) {
            cd(totalArgsInEachCommand - 2, args[1]);
        }
        return;
    }
    else if (strcmp(args[0], "pwd") == 0) {
        for (int i = 0; i < repeatTimes; i++) {
            pwd(totalArgsInEachCommand - 2, args);
        }
        return;
    }
    else if (strcmp(args[0], "ls") == 0) {
        for (int i = 0; i < repeatTimes; i++) {
            ls(totalArgsInEachCommand - 2, args);
        }
        return;
    }

    // Check for pinfo
    else if(strcmp(args[0], "pinfo") == 0) {
        for (int i = 0; i < repeatTimes; i++) {
            pinfo(totalArgsInEachCommand - 2, args);
        }
        return;
    }

    else {
        for (int i = 0; i < repeatTimes; i++) {
            foregroundProcess(totalArgsInEachCommand - 2, args);
        }
        return;
    }
    return;

}