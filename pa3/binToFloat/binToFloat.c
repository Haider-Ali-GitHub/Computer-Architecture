#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    char buff;
    unsigned int binary = 0;
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        fread(&buff, 1, 1, fp);
        if (buff == '1') {
            binary |= 1 << i; // set the i-th bit to 1
        }
    }

    fclose(fp);
      // float number = *(float *)&binary; // you are not allowed to do this.
    // decode sign bit, exponent bits, and mantissa bits
    bool sign = binary >> 31;
    int exp = (binary >> FRAC_SZ) & ((1 << EXP_SZ) - 1);
    unsigned int frac = binary & ((1 << FRAC_SZ) - 1);

   
    // M
    /* ... */
    double m = 1.0;
    for (int i=0; i<FRAC_SZ; i++) {
        if (frac & (1 << (FRAC_SZ-1-i))) {
            m += pow(2, -i-1);
        }
    }
    // E
    /* ... */
    int e = exp - ((1 << (EXP_SZ-1)) - 1);
    if (e > 0) {
        m *= pow(2, e);
    } else if (e < 0) {
        m *= pow(2, e);
    }
    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = sign ? -m : m;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
