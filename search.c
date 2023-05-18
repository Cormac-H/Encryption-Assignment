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
    for (i = 0; i<MAX_STRING_SIZE;i++){
        if(strcmp(fileName, fileNames[i]) == 0){
            printf("File found: %s\n", fileName);
            return;
        }
    }
        printf("File not found, try again\n");
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
    while(low <= high) {
        mid = (low + high)/2;
        int res = strcmp(fileName, fileNames[mid]);

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
}

    void searchTypeMenu(void){
        int userChoice;
        char fileName[MAX_FILENAME_SIZE];

        while(1) {
            printSearchMenu();
            printf("Enter the type of file searching>");
            scanf("%d", &userChoice);
            clearInputBuffer();
            
            switch (userChoice){
                case 1:
                    printf("Enter file name> ");
                    fgets(fileName, MAX_FILENAME_SIZE, stdin);
                    fileName[strcspn(fileName, "\n")] = '\0';
                    linearSearch(fileName);
                    break;
                case 2:
                    printf("Enter file name> ");
                    fgets(fileName, MAX_FILENAME_SIZE, stdin);
                    fileName[strcspn(fileName, "\n")] = '\0';
                    binarySearch(fileName);
                    break;
                case 3:
                    printf("Going back to the main menu.\n");
                    return;
                default:
                    printf("Invalid input, try again\n");
            }
        } while (userChoice != 3)
    }   






