#include "sort.h"
#include "menu.h"

/*******************************************************************************
 * This function initiates file sorting on a file provided by a user
 *
 * inputs:
 * - a 1 or 0 value indicating whether the program is in default sorting Mode
 * - this will flag that insertion sort is automatically used
 * outputs:
 * - none
 * author: Cormac Hegarty
*******************************************************************************/
void sortMain(int defaultSortMode) 
{
    int userSelection;
    char fileName[MAX_FILENAME_SIZE];

    /* Prompt user to begin sorting */
    printSortMenu();

    printf("Enter your choice for sorting>");
    scanf("%d", &userSelection);
    clearInputBuffer();

    while(1) /* Loop requires user provided val of 3 to exit */
    {
        switch(userSelection)
        {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                clearInputBuffer();

                FILE* file = fopen(fileName, "r");
                if (file == NULL) {
                    printf("Error when opening the file\n");
                    return;
                }
                
                char contents[MAX_STRING_SIZE][MAX_STRING_SIZE];

                int i = 0;

                /* Read file contents in an array of strings */
                char buffer[MAX_STRING_SIZE];
                while (fgets(buffer, MAX_STRING_SIZE, file)) 
                {
                    strcpy(contents[i], buffer);
                    i++;
                }

                int numLines = i;

                /* Close the file before reopening the file for the writing */
                fclose(file); 

                if(defaultSortMode == 1)
                {
                    insertionSort(contents, numLines);
                    printf("Insertion Sort has been used by default\n");
                }
                else
                {
                    int sortChoice = 0;
                    printf(
                        "\n == Sort Selection ==\n"
                        "1. Insertion sort\n"
                        "2. Bubble sort\n"
                        "3. Quick sort\n"
                        "Enter sort type>\n"
                    );
                    scanf("%d", &sortChoice);
                    clearInputBuffer();

                    switch(sortChoice) /* Choose a sort based on a user prompt */
                    {
                        case 1:
                            insertionSort(contents, numLines);
                            printf("File contents have been sorted alphabetically"
                                    " with Insertion Sort\n");
                            break;
                        case 2:
                            bubbleSort(contents, numLines);
                            printf("File contents have been sorted alphabetically"
                                    " with Bubble Sort\n");
                            break;
                        case 3:
                            quickSort(contents, 0, numLines - 1);
                            printf("File contents have been sorted alphabetically"
                                    " with Insertion Sort\n");
                            break;
                        default:
                            insertionSort(contents, numLines);
                            printf("Option not recognized: "
                                "Insertion Sort has been selected by default\n");

                    }
                }
                
                /* writes the stored contents from file back into the file */
                file = fopen(fileName, "w");
                for (i = 0; i < numLines; i++)
                    fprintf(file, "%s", contents[i]);

                fclose(file);
                
                break;
            case 2:
                char fileName[MAX_FILENAME_SIZE];

                /* Get the first file name */
                printf("Enter a file name>");
                scanf("%s", fileName);
                clearInputBuffer();

                /* Create a linked list and keep track of the current node */
                node_t* currentFile = malloc(sizeof(node_t));
                strcpy(currentFile->fileName, fileName);
                currentFile->nextFile = NULL;

                /* Track the beginning of the list for iterating */
                node_t* firstFile = currentFile;
                
                int userChoice;
                printf("1. Enter another file name\n"
                        "2. Sort listed files\n"
                        "Please choose>");

                scanf("%d", &userChoice);
                clearInputBuffer();
                /* Loop over user input */
                while(1)
                {
                    switch(userChoice)
                    {
                        case 1:
                            char fileName[MAX_FILENAME_SIZE];
                            /* with case one add a new node to the list */
                            printf("Enter a file name>");
                            scanf("%s", fileName);
                            clearInputBuffer();

                            node_t* newFile = malloc(sizeof(node_t));
                            strcpy(newFile->fileName, fileName);
                            newFile->nextFile = NULL;

                            currentFile->nextFile = newFile;
                            currentFile = newFile;
                            break;
                        case 2:
                            /* Perform an insertion sort on every file*/
                            while(firstFile != NULL)
                            {
                                FILE* file = fopen(firstFile->fileName, "r");
                                if (file == NULL)
                                {
                                    printf("Error opening %s\n", firstFile->fileName);
                                    firstFile = firstFile->nextFile;
                                }
                                else
                                {
                                char contents[MAX_STRING_SIZE][MAX_STRING_SIZE];

                                int i = 0;

                                /* Read file contents in array of strings */
                                char buffer[MAX_STRING_SIZE];

                                while (fgets(buffer, MAX_STRING_SIZE, file)) 
                                {
                                    strcpy(contents[i], buffer);
                                    i++;
                                }
                                int numLines = i;

                                insertionSort(contents, numLines);

                                file = fopen(firstFile->fileName, "w");

                                for (i = 0; i < numLines; i++)
                                    fprintf(file, "%s", contents[i]);

                                fclose(file);

                                firstFile = firstFile->nextFile;
                                }
                            }
                            printf("Attempted to sort all files\n");
                            return;
                        default:
                            printf("Invalid choice.\n");
                            break;
                    }
                printf("1. Enter another file name\n"
                        "2. Sort listed files\n"
                        "Please choose>");

                scanf("%d", &userChoice);
                clearInputBuffer();
                }
                break;
            case 3:
                return;
            default:
                printf("Invalid choice.\n");
                break;
        }
        /* Loop over prompting user input */
        printSortMenu();
        printf("Enter your choice for sorting>");
        scanf("%d", &userSelection);
        clearInputBuffer();
    }
}

/*******************************************************************************
 * This function performs an insertion sort to sort file contents alphabetically
 *
 * inputs:
 * - contents of a file divided line by line into a matrix of strings
 * - the number of lines contained within a file, also serves as the max length
 *   of fileContents[][]
 * outputs:
 * - none
 * author: Thomas Boardman
*******************************************************************************/
void insertionSort(char fileContents[][MAX_STRING_SIZE], 
                    const int fileLineCount) 
{
    int a, b;
    char key[MAX_STRING_SIZE];

    for (a = 1; a < fileLineCount; a++) 
    {
        /* assigns the current element as the key variable */
        strcpy(key, fileContents[a]);
        b = a - 1;

        /* loops through all elements and compares the key element with the 
         * current */
        while ((b) >= 0 && strcmp(fileContents[b], key) > 0) 
        {
            /* the previous element is moved ahead one postion if its greater 
             *than the key */
            strcpy(fileContents[b + 1], fileContents[b]);
            b = b - 1;
        }
        /* inserts the key element at the correct postion after the while loop 
         * is finished */
        strcpy(fileContents[b + 1], key);
    }

}

/*******************************************************************************
 * This function performs a bubble sort to sort file contents alphabetically
 *
 * inputs:
 * - contents of a file divided line by line into a matrix of strings
 * - the number of lines contained within a file, also serves as the max length
 *   of fileContents[][]
 * outputs:
 * - none
 * author: Thomas Boardman
*******************************************************************************/
void bubbleSort(char fileContents[][MAX_STRING_SIZE], const int fileLineCount) 
{
    int a, b;
    char temp[MAX_STRING_SIZE];

    for (a = 0; a < fileLineCount - 1; a++) 
    {
        for (b = 0; b < fileLineCount - a - 1; b++) 
        {
            /* comparing strings and swapping them if needed */
            if (strcmp(fileContents[b], fileContents[b + 1]) > 0) 
            {
                strcpy(temp, fileContents[b]);
                strcpy(fileContents[b], fileContents[b + 1]);
                strcpy(fileContents[b + 1], temp);
            }
        }
    }
}

/*******************************************************************************
 * This function perform a quick sort to sort file contents alphabetically
 *
 * inputs:
 * - contents of a file divided line by line into a matrix of strings
 * - low is the first index of the element thats sorted
 * - int high is the last index of the element thats sorted 
 * outputs:
 * - none
 * author: Thomas Boardman
*******************************************************************************/
void quickSort(char fileContents[][MAX_STRING_SIZE], int low, int high) 
{
    if (low < high) {
        int pivotIndex = partition(fileContents, low, high);
        quickSort(fileContents, low, pivotIndex - 1);
        quickSort(fileContents, pivotIndex + 1, high);
    }
}

/*******************************************************************************
 * This function divides an array into two different parts, one that has less 
 * than the value of the pivot and the other with a greater value than the pivot
 * 
 * inputs:
 * - contents of a file divided line by line into a matrix of strings
 * - low is the first index of the element thats sorted
 * - int high is the last index of the element thats sorted 
 * outputs:
 * - the index of the value that best pivots the array to be sorted around
 * author: Thomas Boardman
*******************************************************************************/
int partition(char fileContents[][MAX_STRING_SIZE], int low, int high) 
{

    /* pivot is assumed as the last value in array */
    char pivot[MAX_STRING_SIZE];
    strcpy(pivot, fileContents[high]);

    int a = low - 1;
    int b ; 

    /* compares each value in the array to the central pivot and
     * swaps them if needed */
    for (b = low; b < high; b++) {
        if (strcmp(fileContents[b], pivot) < 0) 
        {
            a++;
            swap(fileContents, a, b);
        }
    }

    /* moves the pivot to the correct postion in the string */
    swap(fileContents, a + 1, high);

    return a + 1;
}

/*******************************************************************************
 * This function swaps two rows in a matrix of strings
 * 
 * inputs:
 * - contents of a file divided line by line into a matrix of strings
 * - low is the first index of the element thats sorted
 * - int high is the last index of the element thats sorted 
 * outputs:
 * - the index of the value that best pivots the array to be sorted around
 * author: Thomas Boardman
*******************************************************************************/
void swap(char fileContents[][MAX_STRING_SIZE], const int a, const int b) 
{
    char temp[MAX_STRING_SIZE];
    strcpy(temp, fileContents[a]);
    strcpy(fileContents[a], fileContents[b]);
    strcpy(fileContents[b], temp);
}

