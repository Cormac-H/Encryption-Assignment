#include "compress.h"
#include "menu.h"

void compressionMain()
{
    int userSelection;
    printCompressionMenu();
    printf("What would you like to do?\n");
    scanf("%d", &userSelection);
    clearInputBuffer();

    while(1) /* Loop requires user provided val of 6 to exit */
    {
        switch(userSelection)
        {
            case 1:
                printf("Please enter compression target filename>");
                
                char fileName[MAX_FILENAME_SIZE];
                scanf("%s", fileName);
                clearInputBuffer();

                char compressedFileName[MAX_FILENAME_SIZE] = "c-";
                strcpy(compressedFileName + 2, fileName);

                FILE *file = fopen(fileName, "r");
                FILE *compressedFile = fopen(compressedFileName, "a");

                if (file == NULL) 
                {
                    printf("\nCannot read file \n");
                    break;
                }

                compressFile(file, compressedFile);

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
        printf("What would you like to do?\n");
        scanf("%d", &userSelection);
    }
}

void decompressionMain()
{
    int userSelection;

    printCompressionMenu();
    printf("What would you like to do?\n");
    clearInputBuffer();
    scanf("%d", &userSelection);

    while(1) /* Loop requires user provided val of 6 to exit */
    {
        switch(userSelection)
        {
            case 1:
                printf("Please enter decompression target filename>");
                char compressedFileName[MAX_FILENAME_SIZE];
                scanf("%s", compressedFileName);
                clearInputBuffer();

                char decompressedFileName[MAX_FILENAME_SIZE];
                strcpy(decompressedFileName, compressedFileName + 3);

                FILE *compressedFile = fopen(compressedFileName, "r");
                FILE *decompressedFile = fopen(decompressedFileName, "a+");
                
                if (compressedFile == NULL) 
                {
                    printf("\nCannot read file \n");
                    break;
                }

                decompressFile(compressedFile, decompressedFile);

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
        printf("What would you like to do?\n");
        scanf("%d", &userSelection);
        clearInputBuffer();

    }
}

/*function to compress the input*/
void compressFile(FILE *input, FILE *output)
{
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

    unsigned char buffer = 0;
    int bitsWritten = 0, i;
    char c;
    char* code;

    while ((c = fgetc(input)) != EOF) 
    {
        if (c == 32) /* Space */
            code = (char*)letterEncodings[26];
        else if (c == 10) /* Newline */
            code = (char*)letterEncodings[27];
        else if (c < 97) /* Upper-case */
            code = (char*)letterEncodings[(int)c - 65];
        else /* Lower-case */
            code = (char*)letterEncodings[(int)(c - 'a')];

        for (i = 0; i < strlen(code); i++) 
        {
            if (code[i] == '0')
                buffer = (buffer << 1);
            else
                buffer = (buffer << 1) | 1;

            ++bitsWritten;
            if (bitsWritten == 8) 
            {
                fputc(buffer, output);
                buffer = 0;
                bitsWritten = 0;
            }
        }
    }

    if (bitsWritten > 0) 
    {
        buffer = buffer << (8 - bitsWritten);
        fputc(buffer, output);
    }
}

/*function to decompress the input*/
void decompressFile (FILE *input, FILE *output)
{
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
    
    char* buffer = NULL;
    int bufferSize = 0;
    int i, j;
    char c;

    while ((c = fgetc(input)) != EOF) 
    {
        for (i = 7; i >= 0; i--) 
        {
            int bit = (c >> i) & 1;   
            buffer = (char*)realloc(buffer, (bufferSize + 1) * sizeof(char));
            buffer[bufferSize] = (char)(bit + 48);
            ++bufferSize;
            printf("Buffer: %s\n", buffer);
            for (j = 0; j < 28; j++) 
            {
                if (strncmp(buffer, letterEncodings[j], 9) == 0) 
                {
                    if(j == 26)
                    {
                        printf("space\n");
                        fputc(32, output);
                    }
                    else if (j == 27)
                    {
                        printf("newline\n");
                        fputc(10, output);
                    }
                    else
                        fputc(j + 97, output);
    
                    memset(buffer, 0, 9);
                    bufferSize = 0;
                    break;
                }
            }
        }
    }
    free(buffer);
}







