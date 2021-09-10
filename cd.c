#include "main.h"

void cd(long long int numArgs, char *commandArgument) {

    // Throw an error if numArgs > 2
    if (numArgs > 2) {
        printf(stderr, "cd : too many arguments have been passed!");
        return;
    }
    // Means we have to move to the home directory
    else if (numArgs == 1) {
        getCurrentDirectory();
        strcpy(previousDir,currentDir);
        if(chdir(homeDir)<0){
            perror("cd ");
        }
        getCurrentDirectory();
        printf("%s", currentDir);
    }else {


        getCurrentDirectory();
    }
    return;

}



// void cd(ll n,char *commarg[]){                                                            // cd
//     if(n > 2){
//         fprintf(stderr,"cd : too many arguments!\n");
//         latest_status=0;
//         return;
//     }
//     else if(n==1){
//         getcurdir();
//         strcpy(prevdir,currdir);
//         if(chdir(homedir)<0){
//             latest_status=0;
//             perror("cd ");
//         }
//     }
//     else {
//         char path[MA];
//         strcpy(path,commarg[1]);
//         if(strcmp(commarg[1],"-")==0){
//             strcpy(path,prevdir);
//             printf("%s\n",prevdir);
//         }
//         getcurdir();
//         strcpy(prevdir,currdir);

//         tilda_remover(path);
//         if(chdir(path)<0){
//             latest_status=0;
//             perror("cd ");
//         }
//     }
//     getcurdir();
//     return;
// }