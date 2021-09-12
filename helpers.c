#include "main.h"

// Private function - Only for the programmers(not users)
// tokenises str into token by delimParameter.
long long int tokenizer(char *token[], char *s, char *delimParameter){    
    long long int index = 0;

    token[0] = strtok(s, delimParameter);
    
    while(token[index]!=NULL){
        token[++index] = strtok(NULL, delimParameter);
    }

    // Returns the total no. of commands
    return index;
}

// Public function to return the tokens and split into tokens
long long int addAllCommandsInList() {
   return tokenizer(listOfArgs, inputGiven, " \t");   
}

