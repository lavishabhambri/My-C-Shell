#ifndef __MAIN_H
#define __MAIN_H

#include "prompt.h"
#include "headers.h"
#include "cd.h"


// char command[SIZE];
char *inputGiven;
char *command;

char homeDir[SIZE];
char currentDir[SIZE];
char previousDir[SIZE];
char pseudoDir[SIZE];

void getCommand();
void getInputToTerminal();
void getCurrentDirectory();
void getHomeDirectory();
void storePreviousPath();
void getPsuedoCurrentDir();

#endif