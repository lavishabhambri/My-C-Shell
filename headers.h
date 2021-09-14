#include <stdio.h>   
#include<string.h>
#include<stdlib.h>
#include<unistd.h> 
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// Colors
#define ll long long int
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define WHITE "\033[0m"
#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define clear printf("\033[H\033[J")

// SIZE 
#define SIZE 1000000

char systemname[SIZE];
char username[SIZE];
