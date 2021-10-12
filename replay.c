#include "main.h"
#include "foregroundProcess.h"

// This function is for the replay functionality
void replay(long long totalArgsInEachCommand, char *listOfArgs[]) {
    if (totalArgsInEachCommand < 7) {
        printf("Too few arguments");
        return;
    }

    char *replayCommand[totalArgsInEachCommand - 6];
    long long int i = 2;
    long long int k = 0;
    while (strcmp(listOfArgs[i], "-interval") != 0) {
        replayCommand[k] = (char *)malloc(strlen(listOfArgs[i]) * sizeof(char));
        strcpy(replayCommand[k], listOfArgs[i]);
        k++;
        i++;
    }
    

    ll replayPeriod = atoi(listOfArgs[totalArgsInEachCommand - 1]);
    ll replayInterval = atoi(listOfArgs[totalArgsInEachCommand - 3]);
    int steps = replayPeriod / replayInterval;

    char *sleepCommand[2];
    sleepCommand[0] = malloc(strlen("sleep") * sizeof(char));
    strcpy(sleepCommand[0], "sleep");
    sleepCommand[1] = malloc(strlen(listOfArgs[totalArgsInEachCommand - 3]) * sizeof(char));
    strcpy(sleepCommand[1], listOfArgs[totalArgsInEachCommand - 3]);

    for (int i = 0; i < steps; i++) {
        // foregroundProcess()
        // printf("%s", sleepCommand[i]);
        foregroundProcess(2, sleepCommand);
        foregroundProcess(k, replayCommand);

    }

    // Stores if any extra second is left
    int extraSteps = replayPeriod % replayInterval;
    char *extraSleepCommand[2];
    extraSleepCommand[0] = malloc(strlen("sleep") * sizeof(char));
    strcpy(extraSleepCommand[0], "sleep");

    char text[20];
    sprintf(text, "%d", extraSteps);   
    extraSleepCommand[1] = malloc(strlen(text) * sizeof(char));
    strcpy(extraSleepCommand[1], text);
    
    
    foregroundProcess(2, extraSleepCommand);
    return;
}