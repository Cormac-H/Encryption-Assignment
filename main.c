/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Group Members: Alex Sitkowski, Cormac Hegarty, Praket Kumar, Thomas Boardman
 * Alex Sitkowski: 
 * Cormac Hegarty: 13562121
 * Praket Kumar: 13798677
 * Thomas Boardman: 24820122
 * Date of submission: 21/05/2023
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files
*******************************************************************************/
#include "encrypt.h"
#include "compress.h"

#include "menu.h"
#include "sort.h"
/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /* Prompt user to select a function */
    int userSelection; 
    printMainMenu();
    printf("Enter your choice>");
    scanf("%d", &userSelection);

    while(1) /* Loop requires user provided val of 6 to exit */
    {
        switch(userSelection)
        {
            case 1:
                encryptionMain();
                break;
            case 2:
                decryptionMain();
                break;
            case 3:
                compressionMain();
				break;
            case 4:
                decompressionMain();
                break;
            case 5:
                printSortMenu();
                break;
            case 6: 
                break;
            case 7: /* Exit program given correct user value */
                return 0;
            default:
                printf("Invalid choice.");
        }
        /* Loop over prompting user input */
        printMainMenu();
        printf("Enter your choice>");
        scanf("%d", &userSelection);
    }

    return 0;

}


