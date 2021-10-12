#include "main.h"
#define MYARRSIZE 3

int endingCondition(ll time, char *c[]){
    struct timeval tv;
    tv.tv_usec = 0;
    tv.tv_sec = time;
    fd_set fd;
    FD_ZERO(&fd);
    FD_SET(0, &fd);
    select(1, &fd, NULL, NULL, &tv);
    return FD_ISSET(0, &fd);
}

void interrupt(long long totalArgsInEachCommand, char *c[]) {
    // Openfile
    FILE * file = fopen("/proc/interrupts","r"); 
    if(!file) {
        perror("Error ");
        return;
    }
    // Stores each line in the file
    char CPU_line[SIZE];
    ll time = atoi(c[2]);
    
    fgets(CPU_line, SIZE, file);

    printf("%s\n", CPU_line);
    fclose(file);

    ll lenCPU = strlen(CPU_line);
    int i = lenCPU - 1;
    while(i >= 0) {
        if(!(CPU_line[i] == '\n' || CPU_line[i] == '\t' || CPU_line[i] == ' ')) {
            i--;
            break;
        }
        else {
            CPU_line[i] =  '\0';
            i--;
        }
    }

    int pos = 0;
    char inputKey;
    lenCPU = strlen(CPU_line);
    while(pos == 0) {
        file = fopen("/proc/interrupts", "r"); 
        if(!file) {
            perror("Error ");
            return;
        }
        char myArr[MYARRSIZE][SIZE];
        i = 0;
        while(i < MYARRSIZE) {
            fgets(myArr[i], SIZE - 1, file);
            i++;
        }

        myArr[MYARRSIZE - 1][lenCPU] = '\0';

        i = 0;
        while(i < lenCPU) {
            if(myArr[MYARRSIZE - 1][i] == ':'){
                myArr[MYARRSIZE - 1][i] = ' ';
                myArr[MYARRSIZE - 1][i-1] = ' ';
                i++;
                break;
            }
            else {
                myArr[MYARRSIZE - 1][i] = ' ';
                i++;
            }
        }
        printf("%s\n", myArr[MYARRSIZE - 1]);
        fclose(file);
        pos = endingCondition(time, c);
        if(pos != 0) {
			inputKey = fgetc(stdin);
			if(inputKey != 'q') pos = 0;
			else pos = 1;
		}
    }
}