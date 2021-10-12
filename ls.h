#ifndef __LS_H
#define __LS_H

#include "headers.h"

#define MAX_STR_LENGTH 256
#define MAX_TIME_LENGTH 20

// These functions are useful for the ls command implementation
void listDir(char*, bool, bool);
void listFile(char*, char*, bool);
void getPermissions(struct stat, char*);
void getUserName(struct stat, char*);
void getGroupName(struct stat, char*);
void getModTime(struct stat, char*);
void ls(long long int argc, char* argv[]);

#endif