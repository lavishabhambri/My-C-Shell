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

// void tokenizer(char *token[], char *str, char *delim, ll *total){     // tokenises str into token by delim
//     token[0] = strtok(str,delim);
//     ll index = 0;
//     while(token[index]!=NULL){
//         token[++index] = strtok(NULL,delim);
//     }
//     *total = index;
// }

// Public function to return the tokens and split into tokens
// long long int addEachCommandsArgs(char *listOfArgs, char *str) {
//     tokenizer(listOfArgs, str, " \t", ); 
// }

// void getAllTokenizedCommandsList() {
//     tokenizer(listOfCommands, inputGiven, ";\n", noOfCommands);
// }

