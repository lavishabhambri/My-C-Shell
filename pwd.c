#include "main.h"

void pwd() {
    char myPwd[SIZE];
    if(getcwd(myPwd, SIZE) == NULL) {
        perror("");
        exit(0);
    }
    printf("%s\n", myPwd);
    return;
}