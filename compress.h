#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_FILENAME_SIZE 260
#define CHAR_MAX 127

void compressionMain(const int verbose);

void decompressionMain(const int verbose);

/*function to compress the input*/
void compressFile(FILE *input, FILE *output, const int verbose);

/*function to decompress the input*/
void decompressFile (FILE *input, FILE *output, const int verbose);

#endif







