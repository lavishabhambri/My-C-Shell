#include "main.h"

// Function that prints the Welcome in prompt.
void welcomePrompt() {
    clear;
    printf(RED);
    printf("********************************************************\n");
    printf(CYAN);
    printf("Hey! %s I am Angel, your Shell\n",username);
    printf(RED);
    printf("********************************************************\n\n");

}

// This function checks if I have to add telda(~) or not.
// If we are at the home directory or the length of the pseudoHome == currentDirectory then add ~.
int ifAddTelda() {
    if (strcmp(currentDir, pseudoHome) == 0) {
        strcpy(directory, "~");
    }
}

// This updates the relative path stored in directory that we have to move.
void updateRelativePathToMove() {
    
    // Add ~ if needed.
    ifAddTelda();

    // If the paths are not equal, then we aren't at the home directory.
    if (strcmp(currentDir, pseudoHome) != 0) {

        // This is the first non-matched index
        int nonMatchedIndex = 0;

        int index = 0;
        for (index; pseudoHome[index]; index++)
        {
            if (pseudoHome[index] != currentDir[index])
            {
                nonMatchedIndex = index;
                break;
            }
        }

        // If the value of the first non-matched index = 0 then we have to copy the currentpath to directoty.
        if (nonMatchedIndex != 0) {
            strcpy(directory, currentDir);
        }
        else {
            // Else found the relative path
            directory[0] = '~';
            ll p, j;
            for (p = 1, j = index; currentDir[j]; p++, j++)
            {
                directory[p] = currentDir[j];
            }
            directory[p] = '\0';
        }
    }
}

// Main function to print the content
void printInPrompt() {
    strcpy(directory, "");
    getCurrentDirectory();
    
    // Update the path
    updateRelativePathToMove();

    // Printing everything
    printMaterial();

}

// Prints the material/content to the prompt.
void printMaterial() {
    printf(GREEN);
    printf("<%s@%s", username, systemname);
    printf(WHITE);
    printf(":");
    printf(BLUE);
    printf("%s> ", directory);
    printf(WHITE);
}


