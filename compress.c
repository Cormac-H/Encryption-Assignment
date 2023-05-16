#include "compress.h"
#include "menu.h"

/*******************************************************************************
 * This function initiates huffman file compression on a file provided by a user
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Cormac
*******************************************************************************/
void compressionMain()
{
    int userSelection;
    printCompressionMenu();
    printf("Enter your choice for compression>");
    scanf("%d", &userSelection);
    clearInputBuffer();

    while(1) /* Loop requires user provided val of 2 to exit */
    {
        switch(userSelection)
        {
            case 1:
                printf("Please enter compression target filename>");
                
                char fileName[MAX_FILENAME_SIZE];
                scanf("%s", fileName);
                clearInputBuffer();
                /* Compressed files are appended with c- for ease of finding */
                char compressedFileName[MAX_FILENAME_SIZE] = "compressed-";
                strcpy(compressedFileName + 11, fileName);

                FILE *file = fopen(fileName, "r");
                /* Confirm the provided file is valid */
                if (file == NULL) 
                {
                    printf("\nCannot read file \n");
                    break;
                }

                FILE *compressedFile = fopen(compressedFileName, "a");

                /* Run the compression algorithm */
                compressFile(file, compressedFile);

                printf("\nFile compressed! See: %s\n", compressedFileName);

                /* Close files for safety & security */
                fclose(file);
                fclose(compressedFile);

                break;
            case 2:
                return;
            default:
                printf("Invalid choice. %d", userSelection);
                break;
        }
        /* Loop over prompting user input */
        printCompressionMenu();
        printf("Enter your choice for compression>");
        scanf("%d", &userSelection);
        clearInputBuffer();
    }
}

/*******************************************************************************
 * This function decompresses a file provided by a user using a fixed huffman
 * encoding
 *
 * inputs:
 * - none
 * outputs:
 * - none
 * author: Cormac
*******************************************************************************/

void decompressionMain()
{
    int userSelection;

    printCompressionMenu();
    printf("Enter your choice for decompression>");
    scanf("%d", &userSelection);
    clearInputBuffer();

    while(1) /* Loop requires user provided val of 2 to exit */
    {
        switch(userSelection)
        {
            case 1:
                printf("Please enter decompression target filename>");
                char compressedFileName[MAX_FILENAME_SIZE];
                scanf("%s", compressedFileName);
                clearInputBuffer();
                /* Append decompressed file with d- for ease of finding */
                char decompressedFileName[MAX_FILENAME_SIZE] = "decompressed";
                strcpy(decompressedFileName + 12, compressedFileName + 10);

                FILE *compressedFile = fopen(compressedFileName, "r");
                
                /* Confirm the decompression target is valid */
                if (compressedFile == NULL) 
                {
                    printf("\nCannot read file\n");
                    break;
                }
                /* Run decompression algorithm */
                FILE *decompressedFile = fopen(decompressedFileName, "a+");

                decompressFile(compressedFile, decompressedFile);

                /* Check edge case where the buffer is not correctly decoded */
                fseek(decompressedFile, 0, SEEK_END);
                int size = ftell(decompressedFile);

                /* If the target is empty re-run the decompression */
                if (0 == size) {
                    rewind(decompressedFile);
                    rewind(compressedFile);
                    decompressFile(compressedFile, decompressedFile);
                }
                /* File has now been decompressed with certainty */
                printf("\nFile decompressed! See: %s\n", decompressedFileName);

                /* Close files for safety and security */
                fclose(decompressedFile);
                fclose(compressedFile);
                break;
            case 2:
                return;
            default:
                printf("Invalid choice.");
                break;
        }
        /* Loop over prompting user input */
        printCompressionMenu();
        printf("Enter your choice for decompression>");
        scanf("%d", &userSelection);
        clearInputBuffer();
    }
}

/*******************************************************************************
 * This function executes the huffman compression algorithm to compress a 
 * target file. The function uses a fixed table of binary values to encode
 * based on the frequency of each letter's occurrence generally in English.
 * This avoids the overhead of constructing a personalized min-heap for each
 * file.
 *
 * inputs:
 * - a filestream to the beginning of a valid text file
 * - the text file should only contain lowercase characters, spaces and newlines
 * outputs:
 * - a filestream to the beginning of an empty output file
 * author: Cormac
*******************************************************************************/
void compressFile(FILE *input, FILE *output)
{
    /* Declare a table of fixed encodings used to convert each ascii letter
    *  value 26 is reserved for space, and value 27 is reserved for newline
    */
    const char* letterEncodings[28] = {
    /* A - G */
    "1001", "101010", "11100", "0000", "1100", "01011", "111011",
    /* H - N */
    "0001", "0111", "00101010", "1010111", "11111", "10100", "0110",
    /*O - U */
    "1000", "111010", "0010100", "0011", "0100", "1011", "11110",
    /*V - Z */
    "001011", "00100", "1010110", "01010", "001010111",
    /* 26 = space */
    "1101",
    /* 27 = newline */
    "001010110"
    };
    /* declare a buffer character to convert into bits */
    unsigned char buffer = 0;
    /* declare a variable to keep track of when an entire byte is written */
    int bitCount = 0, i, originalTotalBits = 0, newTotalBits = 0;
    char c;
    /* A char* variable to assign to a letter's encoding */
    char* code;

    /* Iterate through the input file character by character */
    while ((c = fgetc(input)) != EOF) 
    {
        /* Track original bits for compression ratio */
        originalTotalBits += 8;

        /* Find the character's encoding */
        if (c == 32) /* Space */
            code = (char*)letterEncodings[26];
        else if (c == 10) /* Newline */
            code = (char*)letterEncodings[27];
        else if (c < 97) /* Upper-case gets converted to lower */
            code = (char*)letterEncodings[(int)c - 65];
        else /* Lower-case */
            code = (char*)letterEncodings[(int)(c - 'a')];

        newTotalBits += strlen(code);
        /* For each 1 or 0 in the encoding, write this as an individual 
        * bit to the output file
        */
        for (i = 0; i < strlen(code); i++) 
        {
            if (code[i] == '0') /* Use left-shift bitwise to obtain the 0 bit */
                buffer = (buffer << 1);
            else /* Use left-shift bitwise OR 1 to obtain the 1 bit */
                buffer = (buffer << 1) | 1;

            ++bitCount;
            /* At any point even if mid-way through a char, the buffer fills
            * to 8 bits, write this as an individual character to file */
            if (bitCount == 8) 
            {
                fputc(buffer, output);
                /* reset the buffer and bit count */
                buffer = 0;
                bitCount = 0;
            }
        }
    }
    /* After writing all encodings, pad the remaining byte if < 8 bits */
    if (bitCount > 0) 
    {
        buffer = buffer << (8 - bitCount);
        fputc(buffer, output);
    }

    printf("Compression Ratio of %.2f%%",((float)newTotalBits/(float)originalTotalBits)*100);
}

/*******************************************************************************
 * This function decompresses a file that has been compressed with huffman
 * encoding. This assumes the file has been encoded using the fixed table of
 * encodings used by the above compression algorithm.
 *
 * inputs:
 * - a filestream to the beginning of a valid text file
 * - the text file should only contain lowercase characters, spaces and newlines
 * outputs:
 * - a filestream to the beginning of an empty output file
 * author: Cormac
*******************************************************************************/
void decompressFile (FILE *input, FILE *output)
{
    /* Declare a table of fixed encodings used to convert each ascii letter
    *  value 26 is reserved for space, and value 27 is reserved for newline
    */
    const char* letterEncodings[28] = {
    /* A - G */
    "1001", "101010", "11100", "0000", "1100", "01011", "111011",
    /* H - N */
    "0001", "0111", "00101010", "1010111", "11111", "10100", "0110",
    /*O - U */
    "1000", "111010", "0010100", "0011", "0100", "1011", "11110",
    /*V - Z */
    "001011", "00100", "1010110", "01010", "001010111",
    /* 27 = space */
    "1101",
    /* 28 = newline */
    "001010110"
    };
    
    /* Declare a buffer to store popped bits*/
    char* buffer = NULL;
    /* Keep track of its size to dynamically allocate memory */
    int bufferSize = 0;
    int i, j;
    char c;

    /* Iterate over the compressed binary data 1 byte at a time */
    while ((c = fgetc(input)) != EOF) 
    {
        /* Loop protection against large or incorrectly compressed files */
        if(bufferSize > 50)
            return;
        /* Process the byte as individual bits */
        for (i = 7; i >= 0; i--) 
        {
            /* Perform a bitwise right shift OR 1 to get the bit value */
            int bit = (c >> i) & 1;   

            /* Extend the buffer to store the new bit */
            buffer = (char*)realloc(buffer, (bufferSize + 1) * sizeof(char));

            /* Store the bit as its ASCII 1 or 0 format */
            buffer[bufferSize] = (char)(bit + 48);
            ++bufferSize;

            printf("Buffer: %s\n", buffer);
            /* For every bit popped, see if it matches an encoding */
            for (j = 0; j < 28; j++) 
            {
                /* Strcmp to check the encoding, 9 is the max size of a code */
                if (strncmp(buffer, letterEncodings[j], 9) == 0) 
                {
                    if(j == 26) /* Position 26 is reserved for space */
                    {
                        printf("space\n");
                        fputc(32, output);
                    }
                    else if (j == 27) /* 27 is reserved for newline */
                    {
                        printf("newline\n");
                        fputc(10, output);
                    }
                    else /* default is lowercase (will convert upper to lower)*/
                        fputc(j + 97, output);
                    
                    /* Reset the buffer */
                    memset(buffer, 0, 9);
                    bufferSize = 0;
                    break;
                }
            }
        }
    }
    free(buffer);
}







