
/* Preprocessor Directive to ensure only 1 compilation of the account struct. */
#ifndef account_H_
#define account_H_

#define MAX_NAME_LENGTH 50 /* The maximum supported length of a username. */
#define MAX_PASSWORD_LENGTH 50 /* The maximum supported length of a password. */
#define MAX_EMAIL_LENGTH 50 /* The maximum supported length of an e-mail. */
#define MAX_WEBSITE_LENGTH 50 /* The maximum supported length of a website. */
#define MAX_NUM_OF_ACCOUNTS 20 /* A fixed maximum number of accounts to store. */

/*******************************************************************************
The struct holding relevant information about an account.

Attributes:
    - username: The username of the account to log in with.
    - password: The password of the account to protect against unauthorised
    access.
    - email: The E-Mail Address associated with the creation of this account.
    - website: The website this account is associated with.
*******************************************************************************/
struct account {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char website[MAX_WEBSITE_LENGTH];
};
typedef struct account account_t;

#endif
