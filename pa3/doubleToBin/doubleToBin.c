#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[]) {

    // SETUP

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    double value;
    fscanf(fp, "%lf", &value);

    // the reference solution ('the easy way')
    // you are not allowed to print from this casted 'ref_bits' variable below
    // but, it is helpful for validating your solution
    unsigned long int ref_bits = *(unsigned long int*) &value;

    // THE SIGN BIT
    bool sign = value<0.0;
    if(1/value < 0){
        sign = true;
    }
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ))); // validate your result against the reference

    // THE EXP FIELD
    // find the exponent E such that the fraction will be a canonical fraction:
    // 1.0 <= fraction < 2.0
    double fraction = sign ? -value : value;
    //signed short trial_exp=(1<<(EXP_SZ-1))-1; // start by assuming largest possible exp (before infinity)
    // do trial division until the proper exponent E is found
    double temporary = fraction;
    int counter = 0;
    while((  counter >-1023 && temporary < 1.0) || temporary >= 2.0)
    {
        if (temporary < 1.0){
            counter-=1;
            temporary *= 2;
        }else{
            counter += 1;
            temporary /= 2;
            
        }
    }

    int counterTwo = 0;
    unsigned short bias = (1<<(EXP_SZ-1))-1;
    signed short exp = bias + counter;
    for ( int exp_index=EXP_SZ-1; 0<=exp_index; exp_index-- ) {

        bool exp_bit = 1&exp>>exp_index;
        if(exp_bit == 0){
            counterTwo += 1;
        }
        printf("%d",exp_bit);
        assert (exp_bit == (1&ref_bits>>(exp_index+FRAC_SZ))); // validate your result against the reference
    }
    printf("_");

    // you get partial credit by getting the exp field correct
    // even if you print zeros for the frac field next
    // you should be able to pass test cases 0, 1, 2, 3

    // THE FRAC FIELD
    // prepare the canonical fraction such that:
    // 1.0 <= fraction < 2.0
    /* ... */
    if (counterTwo == 11)
    {
        temporary = temporary/2;
    }

    bool frac_array[FRAC_SZ+1]; // one extra LSB bit for rounding
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        frac_array[frac_index] = false; // frac set to zero to enable partial credit
    }
    double sum = temporary;

    while(sum >= 1)
    {
        sum = sum -1;
    }
    for( int frac_index =FRAC_SZ; 0<=frac_index; frac_index-- )
    {
        sum *= 2;
        if(sum >= 1)
        {
            sum = sum - 1;
            frac_array[frac_index] = true;
            

        }
        else 
            if(sum < 1 && 0 <= sum )
            {
              frac_array[frac_index] = false;
            }

    }

    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
        //assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }

}
