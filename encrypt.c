/*******************************************************************************
 * RSA encryption
 * 
*******************************************************************************/
#include "encrypt.h"

/*******************************************************************************
 * This function generates a large prime number from a pre-selected randomly
 * generated list of 50
 *
 * inputs:
 * - pointer to a seed variable
 * outputs:
 * - prime number generated
 * author: Cormac
*******************************************************************************/
long generateLargePrime(int* seed)
{
    srand(*seed);
    /* Randomly select a prime number based on the given seed*/
    long temp = primeLookup[getRandomPosition];

    (*seed) *= 2;
    return temp;
}

/*******************************************************************************
 * This function calculates the modular inverse of 2 numbers using Bezout's 
 * identity derived from the extended Euclidean algorithm. This repeatedly 
 * divides the large primes by each other, keeping only the remainders
 * until the greatest common divisor is found. The coefficients maintained
 * from this process can then be used to find the modular inverse of the 2
 * inputs.
 *
 * inputs:
 * - One value
 * - The second value for the equation
 * outputs:
 * - The modular inverse of the 2 input values
 * author: Cormac
*******************************************************************************/
long modularInverse(const long x, const long y)
{
    long prevRemainder = x, remainder = y, prevBezoutCoefficient = 1, 
         bezoutCoefficient = 0, quotient, temp;

    while(remainder != 0)
    {
        /* Calculate the remainder given by integer divison */
        quotient = prevRemainder / remainder;

        /* update the remainder by multiplying the quotient */
        /* the final remainder is the greatest common divisor of x and y */
        temp = prevRemainder;
        prevRemainder = remainder;
        remainder = temp - (quotient * remainder);

        /* Track bezout's coefficients with each Euclidean divison */
        /* Only the first coefficient is needed to calcualte the mod inverse */
        temp = prevBezoutCoefficient;
        prevBezoutCoefficient = bezoutCoefficient;
        bezoutCoefficient = temp - (quotient * bezoutCoefficient);
    }

    /* The inverse can now be calculated from the modulo of the second value */
    return (prevBezoutCoefficient % y + y) % y;
}

/*******************************************************************************
 * This function calculates the modular exponent of a base, exponent and modulo.
 * This works by continually taking an exponent, calculating the modulo and then
 * halving the value until the modular exponent is achieved. Thus resulting
 * in the remainder of the exponentiation.
 * inputs:
 * - a base
 * - an exponent
 * - the modulo
 * outputs:
 * - the modular exponent of the three inputs
 * author: Cormac
*******************************************************************************/
long modularExponentation(long base, long exponent, long modulo)
{
    long result = 1;
    
    /* Reduce the base so that it is < modulo */
    base = base % modulo; 
   
    while (exponent > 0)
    {
        /* Compute modulo given an odd exponent */
        if (exponent % 2 == 1) 
        {
            result *= base; 
            result = result % modulo;
        }
        /* halve the exponent and repeat */
        exponent /= 2;
        base = ((long)pow(base, 2)) % modulo;
    }
    return result;
}

/*******************************************************************************
 * This function generates a 2-part public key and a 1-part public key based on
 * the RSA encryption algorithm. This works by generating 3 random prime numbers
 * . the first two are multiplied to get one part of the public key. The last 
 * number is the final part of the public key. The private key is then taken ASCII
 * the modular inverse of carmichael's totient of the first two prime values, 
 * and the third prime value.
 *
 * inputs:
 * - a random seed for prime value generation
 * - storage for a public key
 * - storage for a private key
 * outputs:
 * - none
 * author: Cormac
*******************************************************************************/
void generateKeys(int seed, long* publicKey, long* privateKey)
{
    /* Generate p, q, and e as co-prime numbers from random seed */
    long p = generateLargePrime(&seed);
    long q = generateLargePrime(&seed);
    long e = generateLargePrime(&seed);
    /* First portion of RSA public key = p * q */
    publicKey[0] = p * q;

    /* Use carmichael's totient function to for private key computation */
    long totient = (p-1) * (q-1);

    /* ensure e < totient */
    while(e > totient) e = generateLargePrime(&seed);

    /* second half of RSA public key is e */
    publicKey[1] = e;

    /* decryption key given by mod inverse of e & totient*/
    *privateKey = modularInverse(e, totient);
}

/*******************************************************************************
 * This function encrypts a file using the properties of RSA encryption. Given
 * a public key it encrypts each ASCII value of a txt file and stores it.
 * Encryption is the modular exponent of the message and the public keys.
 *
 * inputs:
 * - a filename to encrypt
 * - a 2 part array of a public key
 * outputs:
 * - none
*******************************************************************************/
void encryptFile(const char fileName[], long* publicKey)
{
    /* Create a new file to store the encrypted message */
    char encryptedFileName[MAX_FILENAME_SIZE] = "e-";
    
    strcpy(encryptedFileName + 2, fileName);
    
    FILE *file = fopen(fileName, "r");
    FILE *encryptedFile = fopen(encryptedFileName, "a");

    /* Attempt to open the provided file */
	if (file == NULL) 
    {
		printf("\nCannot read file: ");
        while(*fileName != '\0')
        {
            printf("%c", *fileName);
            fileName++;
        }
        printf("\n");
		return;
	}

    char currentChar;
    int message;

    while ((currentChar = fgetc(file)) != EOF) 
    {
        /* implicitly cast the ASCII to it's decimal val */
        message = currentChar;
        /* Message encryption = mod exponent (M ^ e) % n */
        fprintf(encryptedFile, "%ld ", modularExponentation(message, publicKey[1], publicKey[0]));
        fseek(encryptedFile, 0, SEEK_END);
    }
    /* Close file for safety & security */
    fclose(file);
    fclose(encryptedFile);

    remove(fileName);
}

/*******************************************************************************
 * This function decrypts a file using the properties of RSA encryption. Given
 * a public and private key it decrypts each ASCII value of a txt file.
 * Decryption is the modular exponent of the message and the two keys.
 *
 * inputs:
 * - a filename to decrypt
 * - a 2 part array of a public key
 * - a private key
 * outputs:
 * - none
*******************************************************************************/
void decryptFile(const char encryptedFileName[], long* publicKey, long privateKey)
{
    char fileName[MAX_FILENAME_SIZE];
    
    strcpy(fileName, encryptedFileName + 2);
    
    FILE *file = fopen(fileName, "a");
    FILE *encryptedFile = fopen(encryptedFileName, "r");

	if (encryptedFile == NULL) 
    {
		printf("\nCannot read file: ");
        while(*encryptedFileName != '\0')
        {
            printf("%c", *encryptedFileName);
            encryptedFileName++;
        }
        printf("\n");
		return;
	}

    long cipher = 0;
    char c;

    while (fscanf(encryptedFile, "%ld ", &cipher) != EOF) 
    {
        /* Message decryption = mod exponent (C ^ d) % n */
        c = modularExponentation(cipher, privateKey, publicKey[0]);
        fprintf(file, "%c", c);
        fseek(file, 0, SEEK_END);
    }
    /* Close file for safety & security */
    fclose(file);
    fclose(encryptedFile);

    remove(encryptedFileName);
}















