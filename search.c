#include "search.h"
#include "menu.h"
#include "sort.h"
/*******************************************************************************
 * This function performs a linear search for content found in a file
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Praket Kumar
*******************************************************************************/
 void linearSearch(const char *fileName){
    int i;
    char input[MAX_FILENAME_SIZE];

    while(1){
    for (i = 0; i<MAX_STRING_SIZE;i++){
        if(strcmp(fileName, &fileName[i]) == 0){
            printf("File found: %s\n", fileName);
            return;
            }
        }
        printf("Not found, try again\n");
        printf("Enter file name> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        strncpy((char *) fileName, input, MAX_FILENAME_SIZE);
        
        /*
        fgets(fileName, MAX_FILENAME_SIZE, stdin);
        fileName[strcspn(fileName, "\n")] = '\0';
        */

        }
    
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
void binarySearch(const char *fileName){
    int low = 0, high = MAX_STRING_SIZE - 1, mid;
    char input[MAX_FILENAME_SIZE];

    while(1) {
    while(low <= high) {
        mid = (low + high)/2;
        int res = strcmp(fileName, &fileName[mid]);

        if (res == 0) {
            printf("File found; %s\n", fileName);
            return;
        }

        if(res > 0){
            low = mid + 1;

        } else {
            high = mid - 1;
        }
    }
    printf("File not found, try again\n");
    printf("Enter file name> ");

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    strncpy((char *) fileName, input, MAX_FILENAME_SIZE);

    /*
    fgets((char *) fileName, MAX_FILENAME_SIZE, stdin);
    fileName[strcspn(fileName, "\n")] = '\0';
    */

    }


    /*
    fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        strncpy((char *) fileName, input, MAX_FILENAME_SIZE);
        
        fgets(fileName, MAX_FILENAME_SIZE, stdin);
        fileName[strcspn(fileName, "\n")] = '\0';
        */
}

void searchTypeMenu(){
    int userChoice;
    char fileName[MAX_FILENAME_SIZE];

    while(1) {
        printSearchMenu();
        printf("Enter the type of file searching>");
        scanf("%d", &userChoice);
        clearInputBuffer();

        if(userChoice == 3){
            printf("Going back to the main menu.\n");
            return;
        }
        while(userChoice != 1 && userChoice != 2){
            printf("Invalid input, try again\n");
            printf("Enter the type of file searching>");
            scanf("%d", &userChoice);
            clearInputBuffer();
        }
        printf("Enter file name> ");
        fgets(fileName, MAX_FILENAME_SIZE, stdin);
        fileName[strcspn(fileName, "\n")] = '\0';
        switch (userChoice){
            case 1:
                linearSearch(fileName);
                break;
            case 2:
                binarySearch(fileName);
                break;
        }
    }
}
            
            





