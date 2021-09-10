#include "main.h"

void welcomePrompt() {
    printf(RED);
    printf("-----------------------------------------------------------\n");
    printf("Hey! I am ");
    printf(CYAN);
    printf("Angel, ");
    printf(RED);
    printf("your Psuedo Shell\n");
    printf("-----------------------------------------------------------\n\n");   
}

// This function checks if I have to add telda(~) or not.
// If we are at the home directory or the length of the pseudoDir = 0 then no need to add ~.
int ifAddTelda() {
    return strlen(pseudoDir) == 0;
}

// This function finds the left part of the directory.
void getPsuedoCurrentDir() {
    // strcat(currentDir, "/abc");
    int l1 = strlen(currentDir);
    int l2 = strlen(homeDir);
    if (l1 == l2) {
        strcpy(pseudoDir, "");
        return;
    }else {
        for (int i = l2; i < l1; i++) {
            pseudoDir[i-l2] = currentDir[i];
        }
    }
}

// This function prints the prompt.
void promptPrint() {
    getlogin_r(username, sizeof(username)); //Getting the username of the current active user
    gethostname(systemname, sizeof(systemname));
    printf(GREEN); 
    printf("<%s@%s",username, systemname);
    printf(WHITE);
    printf(":");
    printf(BLUE);
    getPsuedoCurrentDir();
    printf("%s", pseudoDir);

    // Checking if I have to add telda(~) or not
    if (ifAddTelda() == 1) {
        printf("~");
    }

    printf("> ");
    printf(WHITE);
}


