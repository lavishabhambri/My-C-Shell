#include "main.h"

void echo() {
    // Call the tokenizer to tokenize the strings and create an array of all the 
    // space-separated words and return their count.
    int totalWords = tokenizer(listOfArgs, copyOfInput, " \t"); 

    // Now print the words.
    for (int i = 1; i < totalWords; i++) {
        printf("%s ", listOfArgs[i]);
    }
    printf("\n");
    return;
}