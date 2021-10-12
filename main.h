#ifndef __MAIN_H
#define __MAIN_H

#include "prompt.h"
#include "headers.h"
#include "cd.h"
#include "run.h"
#include "helpers.h"
#include "pwd.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "signalHandlers.h"
#include "history.h"
#include "jobs.h"
#include "bg.h"
#include "fg.h"
#include "sig.h"
#include "redirection.h"
#include "replay.h"
#include "dirty.h"
#include "interrupt.h"
#include "newborn.h"

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>


typedef struct job {
    // For storing all the processes that I create
    char *jobsNames;
    int jobsIndex;
    ll jobsStatus;
    ll pid;
}job;

ll totalNoOfJobs;

// This stores the actual list of jobs -> needed for "sig" command
job myJobs[SIZE];

// This stores the sorted list of jobs for "jobs" command
job myJobsTemp[SIZE];

// This stores the fg job -> needed for CtrlC & Z command
job fgJob;

// Stores the total input given to us
char *inputGiven;

// Stores the list of the tokenised(on basis of space) arguments.
// char *listOfArgs[SIZE];
char *listOfArgs[SIZE];

char *listOfCommands[SIZE];

// Current Working directory - "/home/lavisha/github/Linux-C-Shell/OTHER_FOLDERS"
char currentDir[SIZE];

// The directory from where I am starting - "/home/lavisha/github/Linux-C-Shell"
// Just initialized only once
char pseudoHome[SIZE];

// Prints the directory (relative part)
char directory[SIZE];

// Stores the argument of the last cd command
char lastCD[SIZE];

// For echo command
char copyOfInput[SIZE];


// For storing Foreground processes
int foreProcessesID[SIZE];
ll noOfForeProcesses;

// For history
char historyArray[20][100];
ll elementsInHistory;

// void getCommand();
void getInputToTerminal();
void getCurrentDirectory();
void getPseudoHome();

#endif