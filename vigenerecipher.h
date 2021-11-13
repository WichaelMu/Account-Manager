
/* Preprocessor Directive to ensure only 1 compilation of the vigenerecipher. */
#ifndef vigenerecipher_H_
#define vigenerecipher_H_

unsigned int numberOfLetters(const char inMessage[]);

void vigenere(char outMessage[], const char inMessage[], const char key[],
    const int encrypt);

#endif
