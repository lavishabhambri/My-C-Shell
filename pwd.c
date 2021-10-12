#include "main.h"

// This function is used to print the present working directory
void pwd() {
    char myPwd[SIZE];
    if(getcwd(myPwd, SIZE) == NULL) {
        perror("");
        exit(0);
    }
    printf("%s\n", myPwd);
    return;
}