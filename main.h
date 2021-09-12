#ifndef __MAIN_H
#define __MAIN_H

#include "prompt.h"
#include "headers.h"
#include "cd.h"
#include "run.h"
#include "helpers.h"

// Stores the total input given to us
char *inputGiven;

char *command;

// Stores the list of the tokenised(on basis of space) arguments.
char *listOfArgs[SIZE];


// Current Working directory - "/home/lavisha/github/Linux-C-Shell/OTHER_FOLDERS"
char currentDir[SIZE];

// The directory from where I am starting - "/home/lavisha/github/Linux-C-Shell"
// Just initialized only once
char pseudoHome[SIZE];

// Prints the directory (relative part)
char directory[SIZE];

// Stores the argument of the last cd command
char lastCD[SIZE];

// void getCommand();
void getInputToTerminal();
void getCurrentDirectory();

void getPseudoHome();


#endif