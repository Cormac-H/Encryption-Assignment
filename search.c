#include "search.h"
#include "menu.h"
#include "sort.h"

/* #define DEBUG */

/*******************************************************************************
 * This function initiates file sorting on a file provided by a user
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Praket Kumar
*******************************************************************************/

void searchMain()
{
    int userSelection;
    char fileName[MAX_FILENAME_SIZE];
    char contents[MAX_FILENAME_SIZE];
    /* Prompt user to begin searching */
    printSearchMenu();

    printf("Enter your choice for searching>");
    scanf("%d", &userSelection);
    clearInputBuffer();

    while(1) /* Loop requires user provided val of 2 to exit */
    {
        switch(userSelection)
        {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                clearInputBuffer();
                
                printf("Enter phrase to search for (max 260 characters)>");
                scanf("%s", contents);
                clearInputBuffer();

                linearSearch(fileName, contents);            
                break;
            case 2:
                return;
            default:
                printf("Invalid choice.\n");
                break;
        }
        /* Loop over prompting user input */
        printSearchMenu();
        printf("Enter your choice for searching>");
        scanf("%d", &userSelection);
        clearInputBuffer();
    }
}

/*******************************************************************************
 * This function searches a file for a phrase and declares the number of
 * instances found.
 *
 * inputs:
 * - name of input file to be searched
 * outputs:
 * - phrase to search for
 * author: Cormac Hegarty
*******************************************************************************/
void linearSearch(const char *fileName, const char* contents)
{
    char buffer[2000];

    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: %s not found\n", fileName);
        return;
    }
    int count = 0;

    while (fscanf(file, "%s", buffer) == 1)
    { 
        #ifdef DEBUG
            printf("Searching ->%s\n", buffer);
        #endif
        if(strstr(buffer, contents) != 0)
            count++;
    }
    printf("%s found in %s %d times\n", fileName, contents, count);

    fclose(file);
}
 
        
            





