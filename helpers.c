#include "main.h"

// Private function - Only for the programmers(not users)
// tokenises str into token by delimParameter.
void tokenizer(char *token[], char *s, char *delimParameter, long long int *total){    
    long long int index = 0;

    token[0] = strtok(s, delimParameter);
    
    while(token[index]!=NULL){
        token[++index] = strtok(NULL, delimParameter);
    }

    // Returns the total no. of commands
    *total = index;
}


