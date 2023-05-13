#include "menu.h"
#include "sort.h"
/*******************************************************************************
 * This function prints the main menu shown to a user for accessing functions
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Cormac
*******************************************************************************/
void printMainMenu(void) {
    printf("\n==========Secure Compact Disk==========\n"
    "Please choose a service\n");

    printf(
        "1. File Encryption\n"
        "2. File Decryption\n"
        "3. File Compression\n"
        "4. File Decompression\n"
        "5. File Sorting\n"
        "6. Search Files\n"
        "7. Exit\n"
    );
}

/*******************************************************************************
 * This function prints menu for encryption functionality
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Cormac
*******************************************************************************/
void printEncryptionMenu(void)
{
    printf("\n==========RSA Encryption/Decryption==========\n");
    printf(
        "1. Enter File Name\n"
        "2. Display Current Keys\n"
        "3. Set New Keys\n"
        "4. Go Back\n"
    );
}

/*******************************************************************************
 * This function prints menu for compression functionality
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Cormac
*******************************************************************************/
void printCompressionMenu(void)
{
    printf("\n==========Huffman Compression/Decompression==========\n");
    printf(
        "1. Enter File Name to Compress/Decompress\n"
        "2. Go Back\n"
    );
}

/*******************************************************************************
 * This function prints menu for file sorting functionality
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Thomas Boardman
*******************************************************************************/
void printSortMenu(void) {
    char fileName[MAX_FILENAME_SIZE];

    printf("Enter file name: ");
    scanf("%s", fileName);

    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error when opening the file\n");
        return;
    }

    char contents[MAX_STRING_SIZE][MAX_STRING_SIZE];
    int a = 0;

    /* read file contents in a array of strings */
    char buffer[MAX_STRING_SIZE];
    while (fgets(buffer, MAX_STRING_SIZE, file)) {
        strcpy(contents[a], buffer);
        a++;
    }

    int numLines = a;
    fclose(file); /*closes the file before reopening the file for the writing */

    int choice = 0;
    printf("Which type of sorting would you like?:\n"
           "1) Insertion sort\n"
           "2) Bubble sort\n"
           "3) Quick sort\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            insertionSort(contents, numLines);
            printf("File contents have been sorted alphabetically with Insertion Sort\n");
            break;
        case 2:
            bubbleSort(contents, numLines);
            printf("File contents have been sorted alphabetically with Bubble Sort \n");
            break;
        case 3:
            quickSort(contents, 0, numLines - 1);
            printf("File contents have been sorted alphabetically with Quick Sort \n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    /* writes the stored contents from file back into the file */
    file = fopen(fileName, "w");
    for (a = 0; a < numLines; a++) {
        fprintf(file, "%s", contents[a]);
    }

    fclose(file);
}

/*******************************************************************************
 * This function prints menu for file searching functionality
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Cormac
*******************************************************************************/
void printSearchMenu(void)
{

}

void clearInputBuffer(void)
{
    while(getchar() != '\n');
}
