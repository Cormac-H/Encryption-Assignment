#include "menu.h"
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
void printSortMenu(void)
{
    printf("\n==========File Sorting==========\n");
    printf(
        "1. Enter File Name to sort\n"
        "2. Enter Batch of File Names\n"
        "3. Go Back\n"
    );
}

/*******************************************************************************
 * This function prints menu for file searching functionality
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Praket Kumar
*******************************************************************************/
void printSearchMenu(void)
{
    printf("\n==========File Searching==========\n");
    printf(
        "1. Linear Search\n"
        "2. Binary Search\n"
        "3. Go Back\n"
    );
}

/*******************************************************************************
 * This function clears the standard input buffer until the next newline
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Cormac
*******************************************************************************/
void clearInputBuffer(void)
{
    while(getchar() != '\n');
}
