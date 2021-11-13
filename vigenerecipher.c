/*******************************************************************************

This file provides the main code and logic for the implementation of the
Vigenère cipher as the encryption/decryption medium for this program.

*******************************************************************************/

#include "vigenerecipher.h" /* Header file. */

#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include "input.h" /* isLetter, isLower, isUpper */

#define MAX_VIGENERE_LENGTH 1024 /* The maximum length of Vigenère. */

/* Implemented by MW, Thusday 21/10/2021 12:57. */
/*******************************************************************************
How many letters exist in the provided string?

Inputs:
    - inMessage: The string to count for letters.
Outputs:
    - The number of letters that exist in inMessage as an unsigned integer.
*******************************************************************************/
unsigned int numberOfLetters(const char inMessage[]) {
	unsigned int lettersCount = 0;
	unsigned int i;
	for (i = 0; i < strlen(inMessage); ++i) {
		lettersCount += isLetter(inMessage[i]);
	}

	return lettersCount;
}

/* Implemented by MW; Thursday, 30/9/2021 16:34. */
/*******************************************************************************
Vigenère cipher logic to encrypt or decrypt outMessage using key.
Adapted from https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher#Description.

Inputs:
	- outMessage: The char[] reference that will hold inMessage's encrypted/
	decrypted equivalent using key.
	- inMessage: The message that will be encrypted/decrypted using key.
	- key: String key to encrypt/decrypt message.
	- encrypt: 1 - Encrypt message using key. 0 - Decrypt message using key.
Outputs:
	- none
*******************************************************************************/
void vigenere(char outMessage[], const char inMessage[], const char key[],\
	const int encrypt)
{
	char extendedKey[MAX_VIGENERE_LENGTH];
	/* Key wrap-around tracker variable. */
	unsigned long keyWrapAround = 0;

    /* Vigenère won't work if the key is < 2. */
	if (strlen(key) < 2) {
		printf("The key must be 2 or more letters in length!\n");
	}

	unsigned long i;
	for (i = 0; i < strlen(inMessage); ++i) {
        /* Identical to keyWrapAround % strlen(inMessage). */
		if (keyWrapAround == strlen(key)) {
			keyWrapAround = 0;
		}

		if (isLetter(key[keyWrapAround])) {
            /* Mark this key for Vigenère if it's not a space and is a letter. */
			if (inMessage[i] != ' ' && isLetter(inMessage[i])) {
				extendedKey[i] = key[keyWrapAround];
				keyWrapAround++;
			}
			else  {
				/* Otherwise, ignore spaces, special characters and numbers. */
				extendedKey[i] = inMessage[i];
			}
		}
		else {
			keyWrapAround++;

            /* Identical to keyWrapAround % strlen(inMessage). */
			if (keyWrapAround >= strlen(key)) {
				keyWrapAround = 0;
			}

			/* Ignore this characer in the key, don't ignore the message. */
			--i;
		}
	}
	
	/* ASCII representation of the key. */
	int ascii = 0;

	/* ASCII representation of the message, encoded in Vigenère. */
	int cipher = 0;

	for (i = 0; i < strlen(inMessage); ++i) {
        if (isInvalidChar(inMessage[i])) {
			continue;
        }

		if (isLetter(inMessage[i])) {
			if (isLower(extendedKey[i])) {
				ascii = extendedKey[i] - 97; /* 97 : a. (ASCII). */
			}
			else if (isUpper(extendedKey[i])) {
				ascii = extendedKey[i] - 65; /* 65 : A. (ASCII). */
			}

            /*
                Encryption:
                    Ci = (Mi + Ki) mod 26.
                Decryption:
                    Mi = (26 - Ci + Ki) mod 26.
                Where:
                    C is ciphertext.
                    M is plaintext.
                    K is the key wrapped Kn/M times.
            */
			if (encrypt) {
				cipher = ascii + inMessage[i];
			}
			else {
				cipher = 26 - ascii + inMessage[i];
			}

            /* Wrap the alphabet if cipher is over ASCII z or ASCII Z. */
			if ((cipher > 'z' && isLower(inMessage[i])) ||
				(cipher > 'Z' && isUpper(inMessage[i])))
			{
				/*  Modulo 26, but account for character casing. */
				cipher -= 26;
			}
		}
		else {
            /* If not a letter, ignore it and move on. */
			cipher = inMessage[i];
		}

        /* Modify outMessage in accordance with Vigenère at key. */
		outMessage[i] = cipher;
	}
}
