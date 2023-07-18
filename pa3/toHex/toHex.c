#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    fscanf(fp, "%d", &input);

    // print bits; you will see this kind of for loop often in this assignment
    // for ( int bit=sizeof(signed int)*8-1; 0<=bit; bit-- ) {
    //     size_t bit_val = ((1<<1)-1) & input>>bit*1; // shift and mask
    //     char character = bit_val ? '1' : '0';
    //     printf("%c",character);
    // }
    // printf("\n");

//     for (int nibble=3; nibble>=0; nibble--) {
//     // Extract the value of the current nibble
//     unsigned int value = (input >> (4 * nibble)) & 0xF;
//     // Map the value to its hexadecimal equivalent using a lookup table
//     static const char* hex_digits = "0123456789ABCDEF";
//     char digit = hex_digits[value];
//     // Print the hexadecimal digit
//     printf("%c", digit);  
//   }
//  printf("\n");

     printf("%04hX\n", input);

    return EXIT_SUCCESS;

}
