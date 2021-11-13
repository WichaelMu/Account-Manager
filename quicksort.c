/*******************************************************************************

This file provides the main code and logic for the quick sort algorithm.

*******************************************************************************/

#include "quicksort.h" /* Header file. */

#include <string.h> /* strcmp() */
#include "account.h" /* struct account | account_t */

/* Implemented by MW, Thusday 21/10/2021 12:57. */
/*******************************************************************************
Swaps Account left with Account right, as references. Order is irrelevant.

Inputs:
    - left: The Account to swap.
    - right: The Account to swap.
Outputs:
    - none
*******************************************************************************/
void swap(account_t* left, account_t* right) {
    account_t temp = *left;
    *left = *right;
    *right = temp;
}

/* Implemented by MW, Thusday 21/10/2021 12:57. */
/*******************************************************************************
Partitions an Account sub-tree, sorts that sub-tree according to the Account's
website and then reassembles the sub-tree/s, with respect to left and
rightBound.

Inputs:
    - accountList: The array of Accounts to sort, according to their website.
    - leftBound: The minimum limit of accountList to partition towards
    rightBound.
    - rightBound: The maximum limit of accountList to partition.
Outputs:
    - The new updated bound/limit of the current recurisve call to quick sort.
*******************************************************************************/
int partition(account_t accountList[], int leftBound, int rightBound) {
    account_t anchor = accountList[rightBound];
    int i = leftBound - 1, k;

    for (k = leftBound; k < rightBound; ++k) {
        /* If k < anchor (ASCII-alphabetically). */
        /* Use ( < 0) for ASCII-ascending order. ( > 0), otherwise. */
        if (strcmp(accountList[k].website, anchor.website) < 0) {
            i++;
            swap(&accountList[i], &accountList[k]);
        }
    }
    
    /* Swap left|right sub-trees to be less|greater than pivot. */
    /* Re-assemble this current partition of Accounts. */
    swap(&accountList[i + 1], &accountList[rightBound]);

    /* Update the anchor's bounds to continue recursive calls to quickSort. */
    return i + 1;
}

/* Implemented by MW, Thusday 21/10/2021 12:57. */
/*******************************************************************************
Sorts accountList with respect to the Account's website and ASCII values.

Inputs:
    - accountList: The list of Accounts to sort.
    - leftBound: The starting index of where to begin sorting.
    - rightBound: The ending index of where to end sorting.
Outputs:
    - none
*******************************************************************************/
void quickSort(account_t accountList[], int leftBound, int rightBound) {

    /* Accounts are not sorted if leftBound is >= rightBound. */
    if (leftBound < rightBound) {
        /* The anchoring position for the recursive sub-tree. */
        int anchor = partition(accountList, leftBound, rightBound);

        /* Recursively sort Accounts left of the anchor. */
        quickSort(accountList, leftBound, anchor - 1);

        /* Recursively sort Accounts right of the anchor. */
        quickSort(accountList, anchor + 1, rightBound);
    }
}
