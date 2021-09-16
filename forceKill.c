#include "main.h"

// This kills all the processes stored in the array.
void forceKill () {

    for(ll i=0; i < totalNoOfProcesses; i++) {
        if(processesStatus[i] == -1)
            continue;
        else
            kill(processesIndex[i], SIGKILL);
    }
    return;
}