#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[CHAR_BIT];// suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=CHAR_BIT-1; 0<=i; i--) // read MSB first as that is what comes first in the file
    {
        fscanf(fp, " %c", &buff);
        minuend[i] = buff == '1'; // store bit as true if char is '1', false otherwise
    }

    // notice that you are reading two different lines; caution with reading
    /* ... */

    // second, read the subtrahend (number to subtract)
    bool subtrahend[CHAR_BIT];
    for (int i=CHAR_BIT-1; 0<=i; i--) 
    {
       fscanf(fp, " %c", &buff);
       subtrahend[i] = buff == '1';  // store bit as true if char is '1', false otherwise
    }
    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    // flip all bits
    bool neg_subtrahend[CHAR_BIT];
    for (int i=0; i<CHAR_BIT; i++)
    {
        neg_subtrahend[i] = !subtrahend[i];  // negate bit (i.e., flip value from true to false or vice versa)
    }

    // add one
    bool carry = true; ; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i=0; i<CHAR_BIT; i++)// iterate from LSB to MSB
     {

        bool a = minuend[i];  // get bit from minuend
        bool b = neg_subtrahend[i]; // get bit from negated subtrahend

        bool sum = a ^ b ^ carry;  // compute sum bit using full adder logic
        
        carry = (a & b) | (b & carry) | (a & carry);  // compute carry bit using full adder logic

        minuend[i] = sum;
    }

    // Add the minuend and the negated subtrahend
    bool difference[CHAR_BIT];

    for (int i=0; i<CHAR_BIT; i++) 
    {

        difference[i] = minuend[i];

    }

    // print the difference bit string
    for (int i=CHAR_BIT-1; 0<=i; i--) 
    {

        printf("%d", difference[i]);

    }

    return EXIT_SUCCESS;

}

