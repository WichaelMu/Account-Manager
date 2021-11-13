/*******************************************************************************
 48430 Fundamentals of C Programming - Assignment 3
 Names: MICHAEL WU, LEWYN DSOUZA, PHOEBE LAVAN, ABDULLAH RAJAB, TABOKA TSHUMA
 Student ID: 13938903, 
 Date of submission: 31st of October, 2021.
 
 To compile: call 'make' in the terminal (without quotations).
 To execute: chmod 755 a.out
           : ./a.out
*******************************************************************************/

#include <stdio.h> /* scanf, printf, fopen, fclose, FILE, fgets, getchar */
#include <string.h> /* strcpy, strlen */

/* struct account | account_t */
#include "account.h"

/* saveToFile, readFromFile */
#include "filehandler.h"

/* numberofLetters */
#include "vigenerecipher.h"

/* readEntireLineWithQuestion, readWithQuestionLimit, removeTrailingN */
#include "input.h"

/* quickSort */
#include "quicksort.h"

/* The maximum length of the master password. */
#define MAX_MASTER_PASSWORD_LENGTH 1024
#define VIEW_ACCOUNT_HEADER "\n--------------------  Account: %d  ------------\
--------\n"
#define VIEW_ACCOUNT_FORMAT "Website: \t %s\nUsername: \t %s\nPassword:\t %s\n\
E-Mail Address:\t %s\n"

/*******************************************************************************
Function Prototypes
*******************************************************************************/
void addAccount(account_t accountList[], unsigned int* indexp);
int deleteAccount(int index);
void updateAccount(account_t accountList[], unsigned int numberOfAccounts);

void viewAccount(account_t accountList[], unsigned int numberOfAccounts);
void sortAccounts(account_t accountList[], const unsigned int numberOfAccounts);
void readMasterPassword(char password[]);
void displayMenu();


/*******************************************************************************
Functions
*******************************************************************************/

/* Implemented by PL. */
/*******************************************************************************
Reads user input to create a new Account and add it to the program. Inputs are
separated by \n in the order: Username, Password, Email, Website.

Inputs:
    - accountList: The list of Accounts to append a new Account.
    - index: A reference to the index of accountList to append.
Outputs:
    - none
*******************************************************************************/
void addAccount(account_t accountList[], unsigned int* indexp) {

    if (*indexp >= MAX_NUM_OF_ACCOUNTS) {
        printf("You have reached the maximum number of accounts!");
        return;
    }

    account_t a;
    
    /* Reads an entire line of input into the respective Account attribute. */
    readWithQuestionLimit(
        a.username, "Enter username>", MAX_NAME_LENGTH, " Username"
    );

    readWithQuestionLimit(
        a.password, "Enter password>", MAX_PASSWORD_LENGTH, " Password"
    );

    readWithQuestionLimit(
        a.email, "Enter email address>", MAX_EMAIL_LENGTH, "n E-Mail Address"
    );

    readWithQuestionLimit(
        a.website, "Enter website>", MAX_WEBSITE_LENGTH, " Website"
    );

    /* Remove the trailing \n from the above input to ensure correct display. */
    removeTrailingN(a.username);
    removeTrailingN(a.password);
    removeTrailingN(a.email);
    removeTrailingN(a.website);

    /*save account*/
    accountList[*indexp] = a;

    /* Increment the number of accounts. */
    (*indexp)++;
}

/* Implemented by PL. */
/*******************************************************************************
Deletes the last Account, according to the index.

Inputs:
    - index: The current index of the Accounts, before deletion.
Outputs:
    - The new integer index of the updated last positiono of Accounts.
*******************************************************************************/
int deleteAccount(int index) {
    if(index > 0) {
        index--;
    } else {
        printf("No accounts");
    }

    return index;
} 

/* Implemented by LD. */
/*******************************************************************************
Updates the last Account with new information taken from user input.

Inputs:
    - accountList: The list of Accounts where the last element will be updated.
    - index: The current last index of accountList.
Outputs:
    - none
*******************************************************************************/
void updateAccount(account_t accountList[], unsigned int index) {
    
    index = deleteAccount(index);

    addAccount(accountList, &index);
}

/* Implemented by AR; Monday, 11/10/2021 3:00. */
/*******************************************************************************
Prints a list of accounts in ASCII-alphabetical order, by website, in the format:

--- Account: %d ---
Website:        %s
Username:       %s
Password:       %s
E-Mail Address: %s

Inputs:
    - accountList: The list of Accounts to print.
    - numberOfAccounts: The number of Accounts to print from accountList.
Output:
    - none
*******************************************************************************/
void viewAccount(account_t accountList[], unsigned int numberOfAccounts)
{
    if (numberOfAccounts == 0)
    {
        printf("\nNo Accounts have been added to system!\n");
        return;
    }

    /* Sort accountList in order for viewing. */
    sortAccounts(accountList, numberOfAccounts);

    unsigned int i;
    
    for (i = 0; i < numberOfAccounts; ++i) {
        printf(VIEW_ACCOUNT_HEADER, i + 1);

        printf(VIEW_ACCOUNT_FORMAT,
            accountList[i].website,
            accountList[i].username,
            accountList[i].password,
            accountList[i].email
        );
    }
}

/* Implemented by AR; Monday, 11/10/2021 2:34. Modified 11/10/2021 4:00. */
/*******************************************************************************
Sorts accountList according to its website, in ASCII-alphabetical order.

Inputs:
    - accountList: The accounts to sort.
    - numberOfAccounts: The number of Accounts to sort.
Outputs:
    none
*******************************************************************************/
void sortAccounts(account_t accountList[], const unsigned int numberOfAccounts)
{
    if (numberOfAccounts > 0) {
        quickSort(accountList, 0, numberOfAccounts - 1);
    }
}

/* Implemented by AR; Momday 11/10/2021 2:34. */
/*******************************************************************************
Displays the selection options that operate this program.

Inputs:
    - none
Outputs:
    - none
*******************************************************************************/
void displayMenu(void)
{
    printf("\n"          
        "1. add account\n"
        "2. delete account\n"
        "3. update account\n"
        "4. view account\n"
        "5. sort account\n"
        "6. save to file\n"
        "7. read from file\n"
        "8. re-enter master password\n"
        "9. exit program\n"
        "Enter Choice (1-9)> "
    );
}

/* Implemented by MW; Thusday, 14/10/2021 14:52. */
/*******************************************************************************
Sets the master password for the program.

Inputs:
    - outPassword: A reference to the master password.
Outputs:
    - none
*******************************************************************************/
void readMasterPassword(char outPassword[]) {
    /* Reads the entire line from user input. */
    readEntireLineWithQuestion(outPassword, "Enter the master password>");

    /* The master password needs to be greater than 2 characters. */
    while (strlen(outPassword) < 3 || numberOfLetters(outPassword) < 2) {
        readEntireLineWithQuestion(outPassword, \
            "\nThe master password must have 2 or more alphabetical characters.\
            \nEnter the master password>"
        );
    }
}

/* Implemented by LD. */
/*******************************************************************************
This is the main function. The program begins and terminates here.

Inputs:
    - none
Outputs:
    - The integer exit code after this program terminates.
*******************************************************************************/
int main(void) /*Lewyn*/
{
    /* Read the master password. */
    char password[MAX_MASTER_PASSWORD_LENGTH];
    readMasterPassword(password);

    const char dbFileName[] = "AccountList"; /* File to save/read Accounts. */

    unsigned int index = 0; /* Current number of Accounts. */
    account_t accountList[MAX_NUM_OF_ACCOUNTS]; /* Array of every Account. */

    char entry; /* User input variable. */

    while (1) {
        displayMenu();
        scanf(" %c", &entry);

        if (entry == '1') {
            addAccount(accountList, &index);
        } else if (entry == '2') {
            index = deleteAccount(index);
        } else if (entry == '3') {
           updateAccount(accountList, index);
        } else if (entry == '4') {
            viewAccount(accountList, index);
        } else if (entry == '5') {
            sortAccounts(accountList, index);
        } else if (entry == '6') {
            saveToFile(accountList, index, dbFileName, password);
        } else if (entry == '7') {
            readFromFile(accountList, &index, dbFileName, password);
        } else if (entry == '8') {
            getchar();
            readMasterPassword(password);
        } else if (entry == '9') {
            break;
        }
    }
    
    return 0;
}
