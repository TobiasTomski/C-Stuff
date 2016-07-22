/*!
*       @author:        Tobias Tomski (info@tobias-tomski.de)
*       @date:          22.07.2016
*       @description:
*
*       This program generates pi to the nth decimal, with n given by the user.
*       This is the solution to one of the problems given by Karan Goel (https://github.com/karan/Projects/).
*
*       @compile:       gcc -lgmp -o pi_to_n_digits pi_to_n_digits.c
*       @execute:       ./pi_to_n_digits <number_of_digits>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#define MAX 1000
#define DIGITS_PER_ITERATION 14.1816474627254776555

char *chudnovsky(int N);

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Usage: ./pi_to_n_digits <number of digits>\n");
        return -1;
    }
    int N = atoi(argv[1]);
    /* Minimum decimal is 1, maximum decimal is MAX.*/
    if (N < 1) {
        printf("The number of digits should be at least 1. Calculating 1 digit of pi.\n");
        N = 1;
    } else if (N > MAX){
        printf("The number of digits should't be greater than %d. Calculating %d digits of pi.\n", MAX, MAX);
        N = MAX;
    }

    char *pi = chudnovsky(N);
    printf("%.1s.%s\n", pi, pi+1);
}

char *chudnovsky(int N){
    // Single parts of a_k for easier calculation. Given as gmp integer.
    mpz_t a, b, c, d, e;
    // Parts of the equation for the sum. Given as gmp floats.
    mpf_t term, A, B, a_k, sum;
    // Laterly returned char containing pi with N digits as string.
    char *output;
    mp_exp_t exp;

    // Helping variables.    
    double bits_per_digit;
    unsigned long int k, threek;
    unsigned long iterations = (N/DIGITS_PER_ITERATION)+1;
    unsigned long precision_bits;

    // Circa bits needed for one digit (= integer), ca. log2(10).
    bits_per_digit = 3.32192809488736234789;
    // Precision bits needed for N decimals, meaning decimals * number of bits per decimal + 1.
    precision_bits = (N * bits_per_digit) + 1;
    // Setting gmp precision for this program.
    mpf_set_default_prec(precision_bits);
    
    // Allocate gmp variables.
    mpf_inits(term, A, B, a_k, sum, NULL);
    mpz_inits(a, b, c, d, e, NULL);

    // Set sum to 0 initially.
    mpf_set_ui(sum, 0);

    // Generating sum for the necessary number of iterations to get N decimals.
    for (k = 0; k < iterations; k++) {
        threek = 3*k;

        mpz_fac_ui(a, 6*k); // (6k)!
        mpz_set_ui(b, 545140134);
        mpz_mul_ui(b, b, k);
        mpz_add_ui(b, b, 13591409); // 13591409 + 545140134k

        mpz_fac_ui(c, threek); // (3k)!
        mpz_fac_ui(d, k);
        mpz_pow_ui(d, d, 3); // pow(k!, 3)
        mpz_ui_pow_ui(e, 640320, threek);
        if((threek&1) == 1) { mpz_neg(e, e); } // pow(-640320, 3k)

        // Numerator saved in A = a * b.
        mpz_mul(a, a, b);
        mpf_set_z(A, a);

        // Denominator saved in B = c * d * e.
        mpz_mul(c, c, d);
        mpz_mul(c, c, e);
        mpf_set_z(B, c);

        // Calculating element ak as a_k = A/B.
        mpf_div(a_k, A, B);
        // Calculating sum for current iteration k as sum += a_k
        mpf_add(sum, sum, a_k);
    }
    // Setting term, constant sqrt part from the formula.
    mpf_sqrt_ui(term, 10005);
    mpf_mul_ui(term, term, 426880);
    // Calculating pi by pi = term/sum
    mpf_div(sum, term, sum);
    // Getting result in base 10 as string. Allocating space for output, too.
    output = mpf_get_str(NULL, &exp, 10, N, sum);
    // Free gmp variables.
    mpf_clears(term, A, B, a_k, sum, NULL);
    mpz_clears(a, b, c, d, e, NULL);

    return output;
}
