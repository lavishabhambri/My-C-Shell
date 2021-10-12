#include "main.h"

int MAX_HIS_SIZE = 20;
int ALLOWED_SIZE = 10;

int ifNotReachedMaxSize(int words) {
    return words < MAX_HIS_SIZE;
}

//  Loads the history file
void loadHistory()
{ 
    char angelHistory[SIZE];
    
    strcpy(angelHistory, pseudoHome);
    strcat(angelHistory, "/angelHistory.txt");

    // Opening the history file in read mode
    FILE *fp = fopen(angelHistory, "r");

    // words present till now
    long long int words = 0;
    if (fp != NULL)
    {
        while ( ifNotReachedMaxSize(words) && fgets(historyArray[words], SIZE, fp) != NULL)
            words++;
        
        elementsInHistory = words;
        // for (; words < MAX_HIS_SIZE; words++)
        while (ifNotReachedMaxSize(words)) {
            strcpy(historyArray[words], "");
            words++;
        }
        fclose(fp);
    }

    // Else open the file in Write mode
    else
    {
        FILE *fp = fopen(angelHistory, "w");
        fclose(fp);
    }
}

void history(long long int n, char *listOfArgs[])
{   
    // Check for valid arguments
    if (n > 2) {
        printf("Too many arguments\n");
        return;
    }

    long long int totalElems = 0;
    if (n == 1)
        totalElems = ALLOWED_SIZE;

    else
    {   
        ll lengthOfArgs = strlen(listOfArgs[1]);
        if (lengthOfArgs > 2)
        {
            printf("Put a number between 1 to 20!\n");
            return;
        }
        int var  = listOfArgs[1][0] - '0';
        if (lengthOfArgs == 1)
            totalElems = var;
        
        else
            totalElems = (var * ALLOWED_SIZE) + (listOfArgs[1][1] - '0');
    }
    if (totalElems < 1)
    {
        printf("Enter a value between 1 to 20\n");
        return;
    }

    if (totalElems > MAX_HIS_SIZE)
    {
        printf("Enter a value between 1 to 20\n");
        return;
    }

    if (totalElems > elementsInHistory)
        totalElems = elementsInHistory;


    ll columnNo = totalElems;
    for(ll i = totalElems-1; i >= 0; i--){
        if(strcmp(historyArray[i], "") != 0){
            printf(" %lld.  %s\n", columnNo, historyArray[i]);
            columnNo -= 1;
        }
    }
    return;
}

// changes history after evry input i.e. listOfArgs[0]
int changeHistory() { 

    char angelHistory[SIZE];
    // sprintf(angelHistory,"%s/angelHistory.txt", pseudoHome);

    strcpy(angelHistory, pseudoHome);
    strcat(angelHistory, "/angelHistory.txt");
    
    if (strcmp(listOfArgs[0], "") == 0 || strcmp(listOfArgs[0], "\n") == 0)
        return 0;
    
    // Means we don't have to push into history as present elem = prev elem.
    if (strcmp(listOfArgs[0], historyArray[0]) == 0)
        return 1;


    long long int length = strlen(listOfArgs[0]);
    bool isDelimeterPresent = false;

    int i = 0;
    while (i < length)
    {
        if (listOfArgs[0][i] != ' ' && listOfArgs[0][i] != '\t' && listOfArgs[0][i] != '\n')
            isDelimeterPresent = true;
        i++;
    }

    if (!isDelimeterPresent) 
        return 0;

    // if (elementsInHistory < MAX_HIS_SIZE)
    if (ifNotReachedMaxSize(elementsInHistory))
        elementsInHistory++;
        
    // Shifting of elements
    // for (long long int i = 18; i >= 0; i--)
    for (ll i = 19; i >= 1; i--)
        strcpy(historyArray[i], historyArray[i - 1]);

    // Put the current element
    strcpy(historyArray[0], listOfArgs[0]);
    
    // Opening in write mode
    FILE *fp = fopen(angelHistory, "w");
    if (fp != NULL)
    {   
        // Writing to the array
        for (ll i = 0; i < elementsInHistory; i++)
            fprintf(fp, "%s", historyArray[i]);
        
        fclose(fp);
    }
    return 1;
}


