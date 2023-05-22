/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Group Members: Alex Sitkowski, Cormac Hegarty, Praket Kumar, Thomas Boardman
 * Alex Sitkowski: 14277127
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
#include "sort.h"
#include "search.h"
#include "menu.h"
/*******************************************************************************
 * Main
*******************************************************************************/
int main(int argc, char *argv[])
{
    
    int seed = 50;
    int verboseMode = 0;
    int defaultSortMode = 0;

    size_t i;
    for (i = 1; i < argc && argv[i][0] == '-'; i++) 
    {
        switch (argv[i][1]) 
        {
            case 's': 
                if(argc <= i+1)
                {
                    printf("Error: Seed argument requires value\n");
                    exit(EXIT_FAILURE);
                }
                int j;
                if(strlen(argv[i+1]) > 6)
                {
                    printf("Error: \"%s\" is too large for a seed, max 6 digits"
                            "\n", argv[i+1]);
                    exit(EXIT_FAILURE);
                }
                for(j = 0; j < strlen(argv[i+1]); j++)
                {
                    if(argv[i+1][j] < '0' || argv[i+1][j] > '9')
                    {
                        printf("Error: \"%s\" is an invalid seed value\n",
                                argv[i+1]);
                        exit(EXIT_FAILURE);
                    }
                }
                seed = atoi(argv[i+1]);
                break;
            case 'v':
                verboseMode = 1;
                break;
            case 'd':
                defaultSortMode = 1;
                break;
        default:
            printf("Usage: [-s 1234 -d -w]\n");
            exit(EXIT_FAILURE);
        }   
    }
    
    printf("\n===============Arguments===============\n");
    printf("1. Seed = %d \n", seed);
    if(verboseMode == 0)
        printf("2. Verbose Mode = False\n");
    else
        printf("2. Verbose Mode = True\n");

    if(defaultSortMode == 0)
        printf("2. Default Sort Mode = False\n");
    else
        printf("2. Default Sort Mode = True\n");

    
    /* Prompt user to select a function */
    int userSelection; 
    printMainMenu();
    printf("Enter your choice>");
    scanf("%d", &userSelection);
    clearInputBuffer();

    while(1) /* Loop requires user provided val of 6 to exit */
    {
        switch(userSelection)
        {
            case 1:
                encryptionMain(seed);
                break;
            case 2:
                decryptionMain(seed);
                break;
            case 3:
                compressionMain();
				break;
            case 4:
                decompressionMain();
                break;
            case 5:
                sortMain(defaultSortMode);
                break;
            case 6: 
                searchMain();
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
        clearInputBuffer();
    }

    return 0;

}


