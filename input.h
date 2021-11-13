
/* Preprocessor Directive to ensure only 1 compilation of input. */
#ifndef input_H_
#define input_H_

#define FAIL_FORMAT "Please enter a%s between 3 and %d characters long.\n"
#define MAX_READ_LENGTH 1024

int isUpper(const char c);

int isLower(const char c);

int isLetter(const char c);

int isInvalidChar(const char c);

void readChar(char* inputChar);
void readCharWithQuestion(char* inputChar, const char question[]);

void readEntireLine(char inputLine[]);
void readEntireLineWithQuestion(char inputLine[], const char question[]);

void readWithQuestionLimit(char inputLine[], const char question[],\
    const unsigned int limit, const char fail[]);

void removeTrailingN(char inputLine[]);
void addTrailingN(char inputLine[]);
void addNullTerminationCharacter(char inputLine[]);

void removeIllegalCharacters(char inputLine[]);

#endif
