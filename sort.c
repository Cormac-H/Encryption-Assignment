#include "sort.h"
/*******************************************************************************
 * This function performs an insertion sort to sort file contents alphabetically
 *
 * inputs:
 * - int n, which is the number of strings in the array
 * - the character array, which has a size of MAX_STRING_SIZE (100 characters)
 * outputs:
 * - none
 * author: Thomas Boardman
*******************************************************************************/
void insertionSort(char arr[][MAX_STRING_SIZE], int n) {
    int a, b;
    char key[MAX_STRING_SIZE];

    for (a = 1; a < n; a++) {
        /* assigns the current element as the key variable */
        strcpy(key, arr[a]);
        b = a - 1;

        /* loops through all elements and compares the key element with the 
         * current */
        while ((b) >= 0 && strcmp(arr[b], key) > 0) {
            /* the previous element is moved ahead one postion if its greater 
             *than the key */
            strcpy(arr[b + 1], arr[b]);
            b = b - 1;
        }
        /* inserts the key element at the correct postion after the while loop 
         * is finished */
        strcpy(arr[b + 1], key);
    }
}

/*******************************************************************************
 * This function performs a bubble sort to sort file contents alphabetically
 *
 * inputs:
 * - the character array, which has a size of MAX_STRING_SIZE (100 characters)
 * - n is an interger that represents the size of an array 
 * outputs:
 * - none
 * author: Thomas Boardman
*******************************************************************************/
void bubbleSort(char arr[][MAX_STRING_SIZE], int n) {
    int a, b;
    char temp[MAX_STRING_SIZE];

    for (a = 0; a < n - 1; a++) {
        for (b = 0; b < n - a - 1; b++) {
            /* comparing strings and swapping them if needed */
            if (strcmp(arr[b], arr[b + 1]) > 0) {
                strcpy(temp, arr[b]);
                strcpy(arr[b], arr[b + 1]);
                strcpy(arr[b + 1], temp);
            }
        }
    }
}

/*******************************************************************************
 * These functions perform a quick sort to sort file contents alphabetically
 *
 * inputs:
 * - the character array, which has a size of MAX_STRING_SIZE (100 characters)
 * - int low is the first index of the element thats sorted
 * - int high is the last index of the element thats sorted 
 * outputs:
 * - none
 * author: Thomas Boardman
*******************************************************************************/

/* swaps the postion of two different elements */
void swap(char arr[][MAX_STRING_SIZE], int a, int b) {
    char temp[MAX_STRING_SIZE];
    strcpy(temp, arr[a]);
    strcpy(arr[a], arr[b]);
    strcpy(arr[b], temp);
}

/* divides an array into two different parts, one that has less than 
 * the value of the pivot and the other with a greater value than the pivot */
int partition(char arr[][MAX_STRING_SIZE], int low, int high) {

    /* pivot is assumed as the last value in array */
    char pivot[MAX_STRING_SIZE];
    strcpy(pivot, arr[high]);

    int a = low - 1;
    int b ; 

    /* compares each value in the array to the central pivot and
     * swaps them if needed */
    for (b = low; b < high; b++) {
        if (strcmp(arr[b], pivot) < 0) {
            a++;
            swap(arr, a, b);
        }
    }

    /* moves the pivot to the correct postion in the string */
    swap(arr, a + 1, high);
    return a + 1;
}

/* sorts the array in non-decreasing order from low to high */
void quickSort(char arr[][MAX_STRING_SIZE], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}
