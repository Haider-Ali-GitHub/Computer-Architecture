#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
// https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>
// https://www.cplusplus.com/reference/cfloat/
#include <float.h>

#define FLOAT_SZ sizeof(float)*CHAR_BIT
#define EXP_SZ (FLOAT_SZ-FLT_MANT_DIG)
#define FRAC_SZ (FLT_MANT_DIG-1)

int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }


    // SETUP

    // first, read the binary number representation of multiplier
    /* ... */

    char c;
    int bits_count = 0;
    bool sign_bit = true;
    char exponent_bits[EXP_SZ];
    char fraction_bits[FRAC_SZ];
    int frac_slots = 0;
    int frac_bits_count = 0;
    bool allZero=true;

    for (int i = EXP_SZ + FRAC_SZ; 0 <= i; i--) {
        fscanf(fp, "%c", &c);
        bits_count += 1;

        if (c == '1') {
            allZero = false;
        }

        if (bits_count == 1) {
            if (c == '1') {
                sign_bit = true;
            } else {
                sign_bit = false;
            }
        } else if (bits_count < 10) {
            exponent_bits[frac_slots] = c;
            frac_slots += 1;
        } else {
            fraction_bits[frac_bits_count] = c;
            frac_bits_count += 1;
        }
    }

    int exponent = EXP_SZ-1;
    int exp_sum = 0;
    for (int i = 0; i < EXP_SZ; i++) {
        if (exponent_bits[i] == '1') {
            exp_sum = exp_sum + pow(2, exponent);
            exponent -= 1;
        } else {
            exponent -= 1;
        }
    }
    exp_sum = exp_sum - 127;

    float frac = 0;
    for (int i = 0; i < FRAC_SZ; i++) {
        if (fraction_bits[i] == '1') {
            frac = frac + pow(2, -(i + 1));
        }
    }
    frac = frac + 1;

    float number = ldexp(frac, exp_sum);
    number = sign_bit ? -number : number;

    fscanf(fp, "%c", &c);

    // notice that you are reading two different lines; caution with reading
    /* ... */

    // first, read the binary number representation of multiplcand
    /* ... */

    char c2;
    int bits_count2 = 0;
    bool sign_bit2 = true;
    char exponent_bits2[EXP_SZ];
    char fraction_bits2[FRAC_SZ];
    int frac_slots2 = 0;
    int frac_bits_count2 = 0;
    for (int i = EXP_SZ + FRAC_SZ; 0 <= i; i--) {
        fscanf(fp, "%c", &c2);
        bits_count2 += 1;

        if (bits_count2 == 1) {
            if (c2 == '1') {
                sign_bit2 = true;
            } else {
                sign_bit2 = false;
            }
        } else if (bits_count2 < 10) {
            exponent_bits2[frac_slots2] = c2;
            frac_slots2 += 1;
        } else {
            fraction_bits2[frac_bits_count2] = c2;
            frac_bits_count2 += 1;
        }
    }

    int exponent2 = EXP_SZ-1;
    int exp_sum2 = 0;
    for (int i = 0; i < EXP_SZ; i++) {
        if (exponent_bits2[i] == '1') {
            exp_sum2 = exp_sum2 + pow(2, exponent2);
            exponent2 -= 1;
        } else {
            exponent2 -= 1;
        }
    }
    exp_sum2 = exp_sum2 - 127;

    float frac2 = 0;
    for (int i = 0; i < FRAC_SZ; i++) {
        if (fraction_bits2[i] == '1') {
            frac2 = frac2 + pow(2, -(i + 1));
        }
    }
    frac2 = frac2 + 1;

    float number2 = ldexp(frac2, exp_sum2);
    number2 = sign_bit2 ? -number2 : number2;

     // multiply the mantissas
    /* ... */
    float finalSum;
    finalSum = number * number2;


    if(allZero)
    {
        finalSum=0;
    }
    float value;
    value = finalSum;


// float product = *(float *) &multiplier * *(float *) &multiplicand; // you are not allowed to print from this.
// unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.

    // SIGN
    /* ... */
    bool sign_bit3 = value<0.0;
    if(1/value < 0){
        sign_bit3 = true;
    }
    printf("%d_",sign_bit3);

    // EXP
    // get the exp field of the multiplier and multiplicand
    /* ... */
    float fraction = sign_bit3 ? -value : value;
    float temporaryValue = fraction;
    int frac_bits_count3 = 0;

    // add the two exp together
    /* ... */
    while( temporaryValue >= 2.0  || (temporaryValue < 1.0 && frac_bits_count3>-127)){
        if (temporaryValue < 1.0){
            temporaryValue  *= 2;
            frac_bits_count3 -= 1;
        }else{
            temporaryValue /= 2;
            frac_bits_count3 += 1;
        }
    }

    // subtract bias
    /* ... */
    unsigned short bias = (1<<(EXP_SZ-1))-1;
   
    signed short exp = frac_bits_count3 + bias;
    int counter = 0;


    // overflow and normalize
    /* ... */

    if (counter == EXP_SZ){
        temporaryValue = temporaryValue/2;
    }


      // rounding
    /* ... */
    bool round[FRAC_SZ+1]; // one extra LSB bit for rounding
    for ( int round_index=FRAC_SZ; 0<=round_index; round_index-- ) {
        round[round_index] = false; // frac set to zero to enable partial credit
    }
    float sum = temporaryValue;

    while(sum >= 1){
        sum = sum -1;
    }

   \
    for( int index = FRAC_SZ; 0 <= index; index-- ){
        sum*=2;
        if(sum >= 1){

            round[index] = true;
            sum = sum - 1;

        }else if(0 <= sum && sum < 1){
            round[index] = false;
        }
      
    }


    // PRINTING
    // print exp
    for ( int bit_index = EXP_SZ-1; 0 <= bit_index; bit_index-- ) {
        bool trial_bit = 1&exp>>bit_index;
        if(trial_bit == 0){
            counter++;
        }
        printf("%d",trial_bit);
        
    }
    printf("_");

     // print frac
    for ( int bit_index = FRAC_SZ-1; 0 <= bit_index; bit_index-- ) {
        bool trial_bit = round[bit_index + 1]; 
        printf("%d", trial_bit);
    }  

    return(EXIT_SUCCESS);

}

