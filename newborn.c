#include "main.h"

// This function implements the functionality of newborn
void newborn(long long totalArgsInEachCommand, char *c[]) {
    ll time = atoi(c[2]);
    int pos = 0;

    // Inputkey - continue the loop until q is pressed
    char inputKey;

    while(pos == 0) {
        char array[100];
        ll numProc;

        FILE * file = fopen("/proc/loadavg","r");
        if(!file) {
            perror("Error ");
            return;
        }
        
        fscanf(file, "%s %s %s %s %lld", array, array, array, array, &numProc);
        printf("%lld\n", numProc);
        fclose(file);
        pos = endingCondition(time, c);
        if(pos != 0) {
			inputKey = fgetc(stdin);
			if(inputKey != 'q') pos = 0;
			else pos = 1;
		}
    }
}