#include "main.h"

// This comapres the 2 structs of jobs array
int comparator(const void *p, const void *q) 
{
    return strcmp(((job*)p)->jobsNames, ((job*)q)->jobsNames);
}

// This is the function for the command - jobs
void jobs(ll totalArgsInEachCommand, char *listOfArgs[]) {

    if(totalArgsInEachCommand > 2) {
        printf("Too many arguments!\n");
    }
    else {
        
        // Sort the array of structs
        qsort(myJobsTemp, totalNoOfJobs, sizeof(myJobsTemp[0]), comparator);

        // When the input command = jobs
        if (totalArgsInEachCommand == 1) {
            for(ll i = 0; i < totalNoOfJobs; i++){
                if (myJobsTemp[i].jobsStatus == -1)
                    continue;

                char procFile[1000];
                sprintf(procFile, "/proc/%lld/stat", myJobsTemp[i].pid);
                char status;
                FILE  *procfd = fopen(procFile, "r");
                if (procfd == NULL) 
                    continue;
                fscanf(procfd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
                
                fclose(procfd);
                printf("[%lld] ",myJobsTemp[i].jobsIndex + 1);
                if(status == 'T'){
                    printf("Stopped ");
                }
                else{
                    printf("Running ");
                }
                
                printf("%s [%lld]\n", myJobsTemp[i].jobsNames, myJobsTemp[i].pid);
            }
        } else {
            // When the flags are also passed ie -r and -s

            // Running
            if (strcmp(listOfArgs[1], "-r") == 0) {

                for(ll i = 0; i < totalNoOfJobs; i++){
                    if (myJobsTemp[i].jobsStatus == -1)
                        continue;

                    char procFile[1000];
                    sprintf(procFile, "/proc/%lld/stat", myJobsTemp[i].pid);
                    char status;
                    FILE  *procfd = fopen(procFile, "r");
                    if (procfd == NULL) 
                        continue;
                    fscanf(procfd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
                    
                    fclose(procfd);
                    if(status == 'S'){
                        printf("[%lld] ", myJobsTemp[i].jobsIndex + 1);
                        printf("Running ");
                        printf("%s [%lld]\n", myJobsTemp[i].jobsNames, myJobsTemp[i].pid);
                    }
                    
                }
            }

            // Stopped
            else if (strcmp(listOfArgs[1], "-s") == 0) {
                
                for(ll i = 0; i < totalNoOfJobs; i++){
                    if (myJobsTemp[i].jobsStatus == -1)
                        continue;

                    char procFile[1000];
                    sprintf(procFile, "/proc/%lld/stat", myJobsTemp[i].pid);
                    char status;
                    FILE  *procfd = fopen(procFile, "r");
                    if (procfd == NULL) 
                        continue;
                    fscanf(procfd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
                    
                    fclose(procfd);
                    if(status == 'T'){
                        printf("[%lld] ", myJobsTemp[i].jobsIndex + 1);
                        printf("Stopped ");
                        printf("%s [%lld]\n", myJobsTemp[i].jobsNames, myJobsTemp[i].pid);
                    }
                    
                }
            }
            else {
                // Check error
                printf("Invalid arguments!\n");

            }
        }
    }
}