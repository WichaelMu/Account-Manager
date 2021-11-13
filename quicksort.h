#include "account.h"

/* Preprocessor Directive to ensure only 1 compilation of quicksort. */
#ifndef quicksort_H_
#define quicksort_H_

void swap(account_t* left, account_t* right);

int partition(account_t accountList[], int leftBound, int rightBound);

void quickSort(account_t accountList[], int leftBound, int rightBound);

#endif
