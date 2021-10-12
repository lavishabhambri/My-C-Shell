#include"main.h"
#define DIRTYSIZE 50
#define BUFSIZE 10000


void blockDesc(int state)
{	
	// Holds block description
	struct termios nextState;

	// Put the state of FD into termios
	tcgetattr(0, &nextState);
	if (state != 0) { 
		nextState.c_lflag |= ICANON;
		tcsetattr(0, 0, &nextState);
	}
	else {
		nextState.c_lflag &= ~ICANON;
		nextState.c_cc[6] = 1;
		tcsetattr(0, 0, &nextState);

	}
}

// Prints error each time
void printDirtyError() {
	printf("Invalid command\n");
}

// To print the dirty memory size
void printDirtySize()
{	
	// Open file
	FILE* file = fopen("/proc/meminfo", "r");

	// Check error
	if (file == NULL) {
		perror("File ");
		return;
	}

	// Scan in the buffer
	char buffer[BUFSIZE];
	for(int i=0; i < DIRTYSIZE;i++)
		fscanf(file,"%s",buffer);
	printf("%s kB\n",buffer);
}


int kbDescription()
{	
	// Holds description of each memory unit
    struct timeval timeValue;
    fd_set fds;

	// Initialise value = 0
    timeValue.tv_usec = 0;
    timeValue.tv_sec = 0;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    select(1, &fds, NULL, NULL, &timeValue);
    return FD_ISSET(0, &fds);
}

int checkDirtyError(ll totalArgsInEachCommand, char *c[]) {
	// Checking errors
	if(!(totalArgsInEachCommand==2 || totalArgsInEachCommand==4)) {
		printDirtyError();
		return 0;
	}
	return 1;
}


int getInputTime(ll totalArgsInEachCommand, char *c[], int *inputTime) {
	
	// Get the input time based on values
	if(strcmp(c[1], "dirty") == 0 && totalArgsInEachCommand == 2) inputTime = 2;
	else
	{
		if(strcmp(c[1], "-n") == 0 && totalArgsInEachCommand == 4) {
			if(strcmp(c[3],"dirty")==0) inputTime = atoi(c[2]);

			// Error
			else {
				printDirtyError();
				return 0;
			}
		}
		else {
			printDirtyError();
			return 0;
		}
	}
	return 1;
}

// Function to implement dirty
void dirty(ll totalArgsInEachCommand, char *c[])
{	
	// Check error
	if(checkDirtyError(totalArgsInEachCommand, c) == 0) {
		return;
	}
	int inputTime;
	if(totalArgsInEachCommand == 2 && strcmp(c[1], "dirty") == 0) inputTime = 2;
	else
	{
		if(totalArgsInEachCommand == 4 && strcmp(c[1], "-n") == 0) {
			if(strcmp(c[3],"dirty") == 0) inputTime = atoi(c[2]);

			else {
				printDirtyError();
				return ;
			}
		}
		else {
			printDirtyError();
			return ;
		}
	}
	// int inputTime;
	// if (getInputTime(totalArgsInEachCommand, c, &inputTime) == 0) return;
	long long int prevTime = -1;
    long long int initime = time(0);
	long long middleTime;
    char inputKey;
    int pos = 0;

    blockDesc(0);
	while(pos == 0) {
		pos = kbDescription();
		middleTime = time(0);
		if(prevTime != middleTime && (middleTime - initime) % inputTime == 0) {
			prevTime = middleTime;
			printDirtySize();
		}
		// Take input from stdin until user presses 'q'
		if(pos != 0) {
			inputKey = fgetc(stdin);
			if(inputKey != 'q') pos = 0;
			else pos = 1;
		}
	}
    blockDesc(1);
}