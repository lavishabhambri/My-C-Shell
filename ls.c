#include "main.h"
bool listAll = false, listLong = false, dirPresent = false; 

// void printTotal(char filename[], bool listLong ) 
// {   
//     struct dirent **read;
//     long long int n = scandir(filename, &read, NULL, alphasort);
//     int i = 1;
//     struct stat s;
//     stat(filename, &s);
//     long long int total = 0;
//     printf("%s", listLong);
//         if (listLong == true) { // flag if -l is given
//             while (i < n) {
//                 char* temp = (char *) malloc(sizeof(filename)+sizeof(read[i]->d_name));
//                 strcpy(temp, filename); //copy path to temp
//                 stat(strcat(temp, read[i]->d_name), &s); // we pass path to + name of file
//                 total += s.st_blocks;
//                 free(temp);
//                 free(filename[i++]); // optimization rules!
//             }
//             free(filename);
//             printf("total %d\n", total/2);
//         }
//     return;
// }





//extract the file's type and permissions from the file's stats and formats the string to encode it
void getPermissions(struct stat sb, char* permissionString){

	//determine the filetype and add the corresponding character
	permissionString[0] = '-';

    
	if(S_ISDIR(sb.st_mode)){
		permissionString[0] = 'd';
	}

	else if(S_ISCHR(sb.st_mode)){
		permissionString[0] = 'r';
	}

	else if(S_ISBLK(sb.st_mode)){
		permissionString[0] = 'b';
	}
	else if(S_ISFIFO(sb.st_mode)){
		permissionString[0] = 'p';
	}
	else if(S_ISLNK(sb.st_mode)){
		permissionString[0] = 'l';
	}
	else if(S_ISSOCK(sb.st_mode)){
		permissionString[0] = 's';
	}

	//check each permission and set the appropriate character
	permissionString[1] = (sb.st_mode & S_IRUSR) == S_IRUSR ? 'r': '-';
	permissionString[2] = (sb.st_mode & S_IWUSR) == S_IWUSR ? 'w': '-';
	permissionString[3] = (sb.st_mode & S_IXUSR) == S_IXUSR ? 'x': '-';

	permissionString[4] = (sb.st_mode & S_IRGRP) == S_IRGRP ? 'r': '-';
	permissionString[5] = (sb.st_mode & S_IWGRP) == S_IWGRP ? 'w': '-';
	permissionString[6] = (sb.st_mode & S_IXGRP) == S_IXGRP ? 'x': '-';

	permissionString[7] = (sb.st_mode & S_IROTH) == S_IROTH ? 'r': '-';
	permissionString[8] = (sb.st_mode & S_IWOTH) == S_IWOTH ? 'w': '-';
	permissionString[9] = (sb.st_mode & S_IXOTH) == S_IXOTH ? 'x': '-';

	permissionString[10] = '\0';
    return;
}


//list a file's info (Print the filename if listLong is false)
void listFile(char* dirname, char* filename, bool listLong){
	struct stat sb;

	char fullPath[2 * MAX_STR_LENGTH];

    // Stores the permissions
	char permissionString[11]; 

    // Stores the Username and the groupnames
	char username[MAX_STR_LENGTH], groupname[MAX_STR_LENGTH];

    // Stores the time when the file was created
	char timestring[MAX_TIME_LENGTH];


	// check if the -l option was used, show full paths
	if(listLong == true){
		strcpy(fullPath, dirname);
		strcat(fullPath, "/");
		strcat(fullPath, filename);

		if(stat(fullPath, &sb) == -1){
			perror(filename);
			return;
		}
		getPermissions(sb, permissionString);

		getUserName(sb, username);
		getGroupName(sb, groupname);

		getModTime(sb, timestring);

        // 10i -> To give a padding of 10 from left
		printf("%s %i %s %s %10i %s %s\n", permissionString, (int)sb.st_nlink, username, groupname, (int)sb.st_size, timestring, filename);
	}
	else{
		printf("%s\n",filename);
	}
}

//extracts the last modified time from the file stats
void getModTime(struct stat sb, char* timestring){
	struct tm  *timestamp;
	struct tm *currentTime;
	time_t currentTimeRaw;

	int currentYear, fileYear;

	//get the current year
	time(&currentTimeRaw);
	currentTime = localtime(&currentTimeRaw);
	currentYear = (int)currentTime->tm_year;

	timestamp = localtime((time_t*)&sb.st_mtim); //time the file was last modified
	fileYear = (int)timestamp->tm_year; //year the file was last modified

	//if the file was last modified during the current year, show the time, else show the year
	if(currentYear == fileYear){
		strftime(timestring, MAX_TIME_LENGTH, "%b %d %R", timestamp);
	}
	else{
		strftime(timestring, MAX_TIME_LENGTH, "%b %d %Y", timestamp);
	}
}

//returns the group name of the file's owner from the stats
void getGroupName(struct stat sb, char* groupname){
	struct group *groupInfo;

	groupInfo = getgrgid(sb.st_gid);	

	strncpy(groupname, groupInfo->gr_name, MAX_STR_LENGTH);
}


//returns the username of the file's owner from the file's stats
void getUserName(struct stat sb, char* username){
	struct passwd *userInfo;

	userInfo = getpwuid(sb.st_uid);	
	strncpy(username, userInfo->pw_name, MAX_STR_LENGTH);
}


// Returns the count of '-' in the command arguments.
int getHiphenCount(long long int argc, char* argv[]) {
    
	int hiphenCount=0;

    //check the number of option arguments (starting with '-')
	for(int i = 1; i < argc; i++){
		if(argv[i][0] == '-'){
			hiphenCount++;
		}
	}
    return hiphenCount;
}

void updateLsBools(long long int argc, char* argv[]) {
    listAll = false, listLong = false, dirPresent = false;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-l"))
            listLong = 1;
        else if (!strcmp(argv[i], "-a"))
            listAll = 1;
        else if (!strcmp(argv[i], "-al") || !strcmp(argv[i], "-la"))
        {
            listLong = 1;
            listAll = 1;
        }
        else if (strcmp(argv[i], ""))
            dirPresent = true;
    }
}



//reads a directory to read each file it contains
void listDir(char* dirname, bool listAll, bool listLong){

    struct dirent **dirEntry;
    DIR* dirp;
	char* filename;
    ll x = 0, count = scandir(dirname, &dirEntry, NULL, alphasort);
    if (count < 0)
        perror("Error: no such file or directory exists\n");
    else {
        while (x < count)
        {   
            filename = dirEntry[x] -> d_name;
            if (filename[0] == '.')
            {   
               
                if(listAll){
					listFile(dirname, filename, listLong);
				}
                x++;
                continue;
            }
            else
            {
                listFile(dirname, filename, listLong);
                x++;
            }
        }
    }
    return;
}



void ls(long long int argc, char* argv[]){

    // Stores information about the files
	struct stat sb;

    // Stores the count of '-'
	int hiphenCount = getHiphenCount(argc, argv);
	
	char filename[MAX_STR_LENGTH];

    // This function update all the bools of the ls function
    updateLsBools(argc, argv);
    
    // Printing the total
    // if(listLong == true){
    //     printf("total %ld\n", sb.st_blocks);

    // }
    
	//if there are no arguments other than '-, 
    // then list what's in the current directory, i.e '.'
	if(argc - hiphenCount == 1){
		listDir(".", listAll, listLong);
	}

    // If the last character ends at '~', then call ls on the pseudoHome.
	else{
        if (strcmp(argv[argc - 1], "~") == 0) {

            strcpy(filename, pseudoHome);
            
            // Check if the file exists or not.
            if(stat(filename, &sb) == -1) {
                perror(filename);
            }
            else{
                
                if((sb.st_mode & S_IFMT) == S_IFDIR){
                        if(argc - hiphenCount > 2){
                            printf("%s:\n", filename);
                        }
                        
                        listDir(filename, listAll, listLong);
                        printf("\n");
                    }
                    // Else print the filename
                    else{
                        listFile(".", filename, listLong);
                    }
            }
        }
        else {

            //go through each command line argument
            for(int i = 1; i < argc; i++){

                strncpy(filename, argv[i], MAX_STR_LENGTH);

                //exclude option arguments
                if(filename[0] == '-') {
                    continue;
                }
                
                //Throw error if filename is invalid
                if(stat(filename, &sb) == -1) {
                    perror(filename);
                }
                else{

                    //if the file is a directory then read it's contents and list the files inside
                    //otherwise just list the file
                    if((sb.st_mode & S_IFMT) == S_IFDIR){
                        if(argc - hiphenCount > 2){
                            printf("%s:\n", filename);
                        }
                        
                        listDir(filename, listAll, listLong);
                        printf("\n");
                    }
                    // Else print the filename
                    else{
                        listFile(".", filename, listLong);
                    }
                    
                }
            }
		}
	}
}