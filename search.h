#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_SIZE 260
#define MAX_STRING_SIZE 100


void linearSearch(const char* fileName);
void binarySearch(const char* fileName);
void searchTypeMenu(void);

#endif


