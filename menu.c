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
        "5. File sorting\n"
        "6. Search for files\n"
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
    printf("\n==========RSA Encryption==========\n");
    printf(
        "1. Enter File Name to Encrypt/Decrypt\n"
        "2. Go Back\n"
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
    printf("\n==========File Compression==========\n");
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
 * author: Cormac
*******************************************************************************/
void printSortMenu(void)
{

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
