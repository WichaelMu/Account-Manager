#include <stdio.h>
#include <string.h>

#include "filehandler.h"
#include "account.h"
#include "vigenerecipher.h"
#include "input.h"

/* Implemented by MW; Wednesday, 13/10/2021 15:55. */
/*******************************************************************************
Saves Accounts from accountList into the file: dbFileName, encrypted with
masterPassword.

Inputs:
    - accountList: The accounts to save into dbFileName.
    - numberOfAccounts: The number of Acconts that need to be saved into
    dbFileName.
    - dbFileName: The name of the file to save accountList to.
    - masterPassword: The password used to encrypt the Accounts into dbFileName.
Outputs:
    - none
*******************************************************************************/
void saveToFile(const account_t accountList[], const unsigned int \
    numberOfAccounts, const char dbFileName[], const char masterPassword[])
{

    if (numberOfAccounts == 0) {
        printf("\nThere are no Accounts to save!\n");
        return;
    }

    FILE* file = fopen(dbFileName, "wb");

    unsigned int i;
    for (i = 0; i < numberOfAccounts; ++i) {
        /*
        When encrypting, ensure that the first parameter is the same length as
        the message.
        
        In this case, set the ciphertext (encryptedX) equal to
        the accountList[i].X before encrypt() is called. Where X is an
        attribute of Account.
        
        We don't want to encrypt the actual data. Separate the actual data
        for encryption.
        */

        char encryptedUsername[MAX_NAME_LENGTH];
        strcpy(encryptedUsername, accountList[i].username);
        
        char encryptedPassword[MAX_PASSWORD_LENGTH];
        strcpy(encryptedPassword, accountList[i].password);
        
        char encryptedEmail[MAX_EMAIL_LENGTH];
        strcpy(encryptedEmail, accountList[i].email);

        char encryptedWebsite[MAX_WEBSITE_LENGTH];
        strcpy(encryptedWebsite, accountList[i].website);

        /* Encrypt this Account's attributes with masterPassword. */
        encrypt(encryptedUsername, accountList[i].username, masterPassword);
        encrypt(encryptedPassword, accountList[i].password, masterPassword);
        encrypt(encryptedEmail, accountList[i].email, masterPassword);
        encrypt(encryptedWebsite, accountList[i].website, masterPassword);

        /* Ensure the encrypted attributes are properly terminated. */
        encryptedUsername[strlen(encryptedUsername)] = '\0';
        encryptedPassword[strlen(encryptedPassword)] = '\0';
        encryptedEmail[strlen(encryptedEmail)] = '\0';
        encryptedWebsite[strlen(encryptedWebsite)] = '\0';

        /* Write the encrypted result to dbFileName. */
        fprintf(file, "%s\n", encryptedUsername);
        fprintf(file, "%s\n", encryptedPassword);
        fprintf(file, "%s\n", encryptedEmail);
        fprintf(file, "%s\n", encryptedWebsite);
    }

    fclose(file);
    
    /* Show how many Accounts were saved into dbFileName. */
    printf("\n%d Account%s saved into %s\n", numberOfAccounts,
        numberOfAccounts == 1
            ? " was"
            : "s were", 
        dbFileName
    );
}

/* Implemented by MW; Monday, 18/10/2021 18:08. */
/*******************************************************************************
Reads and decrypts Accounts from dbFileName and stores them into the program.

Inputs:
    - accountList: The empty list of Accounts that need to be loaded in. Will
    be modified.
    - newNumberOfAccounts: A reference to the new numberOfAccounts.
    - dbFileName: The name of the file where encrypted Accounts are stored.
    - masterPassword: The password used to decrypt the Accounts from dbFileName.
Outputs:
    - none
*******************************************************************************/
void readFromFile(account_t accountList[], unsigned int* newNumberOfAccounts, \
    const char dbFileName[], const char masterPassword[])
{

    FILE* file = fopen(dbFileName, "rb");

    if (file == NULL) {
        printf("Read error.");
        return;
    }

    /* Track the current line when reading from the file. */
    unsigned int readIndex = 0;

    /* Variable to store the encrypted Username. */
    char inUsername[MAX_NAME_LENGTH];
    /* Variable to store the encrypted Password. */
    char inPassword[MAX_PASSWORD_LENGTH];
    /* Variable to store the encrypted E-Mail Address. */
    char inEmail[MAX_EMAIL_LENGTH];
    /* Variable to store the encrypted Website. */
    char inWebsite[MAX_WEBSITE_LENGTH];

    /*
    Recall from saveToFile() that an account is stored in order from
    Username, Password, Email, Website.
    */

    /* Read line readIndex + 0 line from the file. */
    while (fgets(inUsername, MAX_NAME_LENGTH, file)) {
        fgets(inPassword, MAX_PASSWORD_LENGTH, file);
        fgets(inEmail, MAX_EMAIL_LENGTH, file);
        fgets(inWebsite, MAX_WEBSITE_LENGTH, file);

        /*
        Account for UTF-8, UTF-16 characters in the binary file. Add \0 to
        terminate the string.
        */
        inUsername[strlen(inUsername)] = '\0';
        inPassword[strlen(inPassword)] = '\0';
        inEmail[strlen(inEmail)] = '\0';
        inWebsite[strlen(inWebsite)] = '\0';

        /* Decrypt and assign the corresponding Account attributes. */
        decrypt(accountList[readIndex].username, inUsername, masterPassword);
        decrypt(accountList[readIndex].password, inPassword, masterPassword);
        decrypt(accountList[readIndex].email, inEmail, masterPassword);
        decrypt(accountList[readIndex].website, inWebsite, masterPassword);

        /* Remove illegal binary characters may be read. */
        removeIllegalCharacters(accountList[readIndex].username);
        removeIllegalCharacters(accountList[readIndex].password);
        removeIllegalCharacters(accountList[readIndex].email);
        removeIllegalCharacters(accountList[readIndex].website);

        readIndex++;
    }

    /* Set the new numberOfAccounts = the number of Accounts from the file. */
    (*newNumberOfAccounts) = readIndex;
    
    fclose(file);

    /* Show how many Accounts were loaded from dbFileName into accountList. */
    printf("\n%d Account%s loaded from %s into the program.\n", readIndex,
        readIndex == 1
            ? " was"
            : "s were",
        dbFileName
    );
}

/* Implemented by MW; Thursday, 30/9/2021 16:34. */
/*******************************************************************************
Vigenère cipher to encrypt inPlaintext using key. Will modify outCiphertext
as a result.

Inputs:
    - outCiphertext: inPlaintext encrypted with Vigenère using key. Passed as
    reference.
    - inPlaintext: The plaintext to encrypt. Will be modified as reference.
    - key: The password to encrypt plaintext.
Outputs:
    - none
*******************************************************************************/
void encrypt(char outCiphertext[], const char inPlaintext[], const char key[]) {
    vigenere(outCiphertext, inPlaintext, key, 1);
}

/* Implemented by MW; Thursday, 30/9/2021 16:34. */
/*******************************************************************************
Vigenère cipher to decrypt inCiphertext encrypted using key. Will modify
outPlaintext as a result.

Inputs:
    - outPlaintext: inCiphertext decrypted with Vigenère using key. Passed as
    reference.
    - inCiphertext: The ciphertext to decrypt. Presumably encrypted with key.
    - key: The password to decrypt ciphertext to its plaintext equivalent.
Outputs:
    - none
*******************************************************************************/
void decrypt(char outPlaintext[], const char inCiphertext[], const char key[]) {
    vigenere(outPlaintext, inCiphertext, key, 0);
}
