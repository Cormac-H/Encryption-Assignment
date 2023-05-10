#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_SIZE 260
#define MAX_STRING_SIZE 100

void insertionSort(char arr[][MAX_STRING_SIZE], int n); 

void bubbleSort(char arr[][MAX_STRING_SIZE], int n); 

void quickSort(char arr[][MAX_STRING_SIZE], int low, int high); 

void printSortMenu(void); 
