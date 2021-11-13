
/* Preprocessor Directive to ensure only 1 compilation of the filehandler. */
#ifndef filehandler_H_
#define filehandler_H_

#include "account.h"

void saveToFile(const account_t accountList[], const unsigned int
    numberOfAccounts, const char dbFileName[], const char masterPassword[]);
    
void readFromFile(account_t accountList[], unsigned int* indexp,
    const char dbFileName[], const char masterPassword[]);

void encrypt(char outCiphertext[], const char plaintext[], const char key[]);
void decrypt(char outPlaintext[], const char ciphertext[], const char key[]);


#endif
