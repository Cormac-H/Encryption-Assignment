#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "menu.h"
/*******************************************************************************
 * Pre-processing Directives
*******************************************************************************/
#define PRIMES 50
#define MAX_FILENAME_SIZE 260

/* return a value between total number of primes and 0 to index lookup table */
#define getRandomPosition (rand() % (PRIMES + 1 - 0) + 0)

/* Lookup table for a random series of confirmed prime numbers */
/* Sieve of eratosthenes confirms the primality of these numbers */
/* Coded in lookup table to save significant resources by not having to 
* compute numbers or test their primality */
static const int primeLookup[PRIMES] = 
{
    1283, 9103, 5113, 4937, 1861, 4783, 5653, 5813, 4903, 3539, 
    2851, 8389, 5333, 4357, 4013, 4243, 6719, 4583, 2417, 6571, 
    7703, 8311, 4001, 9311, 6151, 5827, 7333, 6089, 7669, 5807, 
    9781, 3407, 1327, 5527, 6211, 3391, 3307, 5237, 7477, 1123, 
    4733, 9293, 1217, 4133, 9769, 4027, 2017, 4049, 1091, 6173
};

/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
/* Functions for main user interaction */
void encryptionMain();
void decryptionMain();

/* Setup an RSA key for a user*/
void generateKeys(int seed, long* publicKey, long* privateKey);

/* Functions to encrypt/decrypt provided user has a valid RSA key */
void encryptFile(char fileName[], long* publicKey);
void decryptFile(char encryptedFileName[], long* publicKey, long privateKey);

/* Functions to for the Euclidean math behind the RSA encryption */
long generateLargePrime(int* seed);
long modularInverse(const long x, const long y);
long modularExponentation(long base, long exponent, long modulo);

#endif
