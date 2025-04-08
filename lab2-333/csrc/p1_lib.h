#ifndef P1_LIB_H
#define P1_LIB_H

#include <stdio.h>

// Constants
#define MANTISSA_SIZE 24
#define EXPONENT_SIZE 8
#define MAX_SIZE 200

// Structure to store IEEE 754 representation
typedef struct {
    char sign[2];                          // Sign bit (0 for positive, 1 for negative)
    char mantissa[MANTISSA_SIZE + 1];       // 24-bit Mantissa
    char exponent[EXPONENT_SIZE + 1];       // 8-bit Exponent
} F32Repr;

/*
 * Pads a binary string with leading or trailing zeros to ensure a fixed size.
 */
void pad_zero(char *source, char *target, int size, int isLeading);

/*
 * Converts an integer to its binary representation.
 */
void int_to_binary(long long int num, char *binary);

/*
 * Converts a fractional decimal to its binary representation.
 */
void dec_to_binary(long double dec, char *binary);

/*
 * Computes the mantissa from integer and fractional binary parts.
 */
void calculate_mantissa(char *int_binary, char *dec_binary, char *mantissa);

/*
 * Computes the exponent value for IEEE 754 representation.
 */
void calculate_exponent(long double real, char *exponent);

/**
 * Converts a floating-point number to its IEEE 754 representation.
 */
F32Repr float_to_IEEE754(long double real);

/**
 * Converts an IEEE 754 representation to a floating-point number.
 */
float IEEE754_to_float(F32Repr repr);

#endif
