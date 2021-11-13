/*******************************************************************************

This file provides the definitions to read certain types of user input from the
terminal/console, as well as check if inputs meet certain requirements.

Thie file makes frequent use of the ASCII table. The American Standard Code for
Information Interchange. For a table:
https://alpharithms.s3.amazonaws.com/assets/img/ascii-chart/ascii-table-alpharithms-scaled.jpg

With this ASCII table, we can easily check if a character is allowed within the
program for encryption manupulation, or if it should be discarded
character ( < 32).

*******************************************************************************/

#include "input.h" /* Header file. */

#include <stdio.h> /* scanf(), printf(), fgets(), stdin */
#include <string.h> /* strlen(), strcspn(), strncat() */

/* Implemented by MW; Thursday, 30/9/2021 16:34. */
/*******************************************************************************
If char c is an upper case character.

Inputs:
	- c: The char to check if it is an upper-case character in the alphabet.
Outputs:
	- An integer where 1 if c is an upper-case character, 0, otherwise.
*******************************************************************************/
int isUpper(const char c)
{
	return c >= 'A' && c <= 'Z';
}

/* Implemented by MW; Thursday, 30/9/2021 16:34. */
/*******************************************************************************
If char c is a lower case character.

Inputs:
	- c: The char to check if it is a loewr-case character in the alphabet.
Outputs:
	- An integer where 1 if c is a lower-case character, 0, otherwise.
*******************************************************************************/
int isLower(const char c)
{
	return c >= 'a' && c <= 'z';
}

/* Implemented by MW; Thursday, 30/9/2021 16:34. */
/*******************************************************************************
If char c is a letter in the alphabet, upper case or lower case.

Inputs:
	- c: The char to check if it is a letter.
Outputs:
	- An integer where 1 if c is a letter, 0, otherwise.
*******************************************************************************/
int isLetter(const char c)
{
	return isLower(c) || isUpper(c);
}

/* Implemented by MW, Monday 18/10/2021 9:47. */
/*******************************************************************************
Whether or not if the provided char is illegal or now. An illegal char is defined
as being not within the range of ' ' (ASCII-32) and 'z' (ASCII-122). A char that
falls outside of this range is considered illegal.

Inputs:
    - c: The char in question to check for illegalities.
Outputs:
    - An integer where 1 if c is invalid, 0 otherwise.
*******************************************************************************/
int isInvalidChar(const char c) {
    if (c >= ' ' && c <= 'z') {
        return 0;
    }

    return !isLetter(c);
}

/* Implemented by MW, Monday 18/10/2021 9:47. */
/*******************************************************************************
Reads a char from input.

Inputs:
    - inputChar: A reference to the char after input.
Outputs:
    - none
*******************************************************************************/
void readChar(char* inputChar) {
    scanf("%c", inputChar);
}

/* Implemented by MW, Monday 18/10/2021 9:47. */
/*******************************************************************************
Reads a char after asking a question.

Inputs:
    - inputChar: A reference to the char after input.
    - question: The question to ask for the char.
Outputs:
    - none
*******************************************************************************/
void readCharWithQuestion(char* inputChar, const char question[]) {
    printf("%s", question);

    readChar(inputChar);
}

/* Implemented by MW, Monday 18/10/2021 9:47. */
/*******************************************************************************
Reads an entire line from input.

Inputs:
    - inputLine: A reference to the string that will be read.
Outputs:
    - none
*******************************************************************************/
void readEntireLine(char inputLine[]) {
    scanf(" ");
    fgets(inputLine, MAX_READ_LENGTH, stdin);
}

/* Implemented by MW, Monday 18/10/2021 9:47. */
/*******************************************************************************
Reads an entire line after asking a question.

Inputs:
    - inputLine: A reference to the string that will be read.
    - question: The question to ask for input.
Ouputs:
    - none
*******************************************************************************/
void readEntireLineWithQuestion(char inputLine[], const char question[]) {
    printf("%s", question);

    readEntireLine(inputLine);
}

/* Implemented by MW, Monday 18/10/2021 9:47. */
/*******************************************************************************
Reads an entire line of input and check if that input meets limit requirements.

Inputs:
    - inputLine: A reference to the string that will be read.
    - question: The question to ask for input.
    - limit: The limit length of the inputLine.
    - failCategory: If the limit fails, print the provided failing category.
Outputs:
    - none
*******************************************************************************/
void readWithQuestionLimit(char inputLine[], const char question[],
    const unsigned int limit, const char failCategory[]) {
        
    /* Ask the question as normal. */
    readEntireLineWithQuestion(inputLine, question);

    unsigned int lengthOfInputLine = strlen(inputLine);
    
    while (lengthOfInputLine > limit || lengthOfInputLine <= 3) {
	    /* If the limit check fails, show the fail and the required length. */
        printf(FAIL_FORMAT, failCategory, limit);

        /* Ask the question again. */
        readEntireLineWithQuestion(inputLine, question);

        /* Reset the length. */
        lengthOfInputLine = strlen(inputLine);
    }

    addNullTerminationCharacter(inputLine);

    /* inputLine will be the correct input, according to limit. */
}

/* Implemented by MW, Monday 18/10/2021 10:21. */
/*******************************************************************************
Removes the trailing \n character at the end of a string.

Inputs:
    - inputLine: The string with a trailing \n that needs removing.
Outputs:
    - none
*******************************************************************************/
void removeTrailingN(char inputLine[]) {
    inputLine[strcspn(inputLine, "\n")] = 0;
}

/* Implemented by MW, Thusday 21/10/2021 12:57. */
/*******************************************************************************
Adds a trailing \n character at the end of a string.

Inputs:
    - inputLine: The string that needs a trailing \n.
Outputs:
    - none
*******************************************************************************/
void addTrailingN(char inputLine[]) {
    strncat(inputLine, "\n", 2);
}

/* Implemented by MW, Thusday 21/10/2021 12:57. */
/*******************************************************************************
Adds a null termination character (0) or (\0) to the end and end - 1 of a string.

Inputs:
    - inputLine: The string that needs a null termination character.
Outputs:
    - none
*******************************************************************************/
void addNullTerminationCharacter(char inputLine[]) {
    inputLine[strlen(inputLine)] = 0;
    inputLine[strlen(inputLine) - 1] = 0;
}

/* Implemented by MW, Thusday 21/10/2021 12:57. */
/*******************************************************************************
Removes any and all illegal characters from a string.

Input:
    - inputLine: The string to remove any and all illegal characters.
Outputs:
    - none
*******************************************************************************/
void removeIllegalCharacters(char inputLine[]) {
    unsigned int i;
    for (i = 0; i < strlen(inputLine); ++i)
        if (isInvalidChar(inputLine[i])) /* If this character is invalid: */
            inputLine[i] = 0; /* Nullify this character. */
}
