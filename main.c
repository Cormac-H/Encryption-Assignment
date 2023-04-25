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

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    long publicKey[2], privateKey;
    generateKeys(50, publicKey, &privateKey);
    
    printf("Public: %ld %ld, Private: %ld\n", publicKey[0], publicKey[1], privateKey);
    
    const char fileName[MAX_FILENAME_SIZE] = "test_file.txt";
    
    encryptFile(fileName, publicKey); 
    
    const char encryptedFileName[MAX_FILENAME_SIZE] = "e-test_file.txt";

    decryptFile(encryptedFileName, publicKey, privateKey);

    return 0;
}


