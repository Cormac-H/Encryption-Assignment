#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LENGTH 200

/*******************************************************************************
 * This function performs a linear search for content found in a file
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: 
*******************************************************************************/
void linearSearch(char* fileName, char* content)
{
    FILE* file = fopen(fileName, "r");
    char buffer[MAX_FILE_LENGTH];
    int lineNumber = 0;
    int found = 0;

    while(fgets (buffer, MAX_FILE_LENGTH)){
        lineNumber++;
        if(strstr(buffer, content)){
            printf("'%s' found on line %d using linear search\n", content, lineNumber);
            found = 1;
        }
    }
    if(!found){
        printf("'%s' not found in the file using linear search\n", content);
    }
    fclose(file);
}

/*******************************************************************************
 * This function performs a binary search for content found in a file
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: 
*******************************************************************************/
void binarySearch()
{

}
