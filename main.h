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

// void getCommand();
void getInputToTerminal();
void getCurrentDirectory();
void getPseudoHome();


#endif