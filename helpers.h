#ifndef __HELPERS_H
#define __HELPERS_H

long long int addEachCommandsArgs(char *listOfArgs, char *str);
long long int getAllTokenizedCommandsList();
void tokenizer(char *token[], char *s, char *delimParameter, long long int *total);  


#endif