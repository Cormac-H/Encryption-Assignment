#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_SIZE 260
#define MAX_STRING_SIZE 100

/* Main user prompts */
void sortMain(void);

/* Main sorting functions */
void insertionSort(char fileContents[][MAX_STRING_SIZE], 
                    const int fileLineCount); 

void bubbleSort(char fileContents[][MAX_STRING_SIZE], const int fileLineCount); 

void quickSort(char fileContents[][MAX_STRING_SIZE], int low, int high); 

/* Helper functions for quick sorting */
int partition(char fileContents[][MAX_STRING_SIZE], int low, int high);

void swap(char fileContents[][MAX_STRING_SIZE], const int a, const int b); 

#endif
