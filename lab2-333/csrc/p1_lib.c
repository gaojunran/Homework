/*
 * Author: Gao Junran
 * Date: 2024-03-26
 * Description: This program converts a floating-point number into its IEEE 754 single-precision representation.
 *              The program has been tested against https://baseconvert.com/ieee-754-floating-point for accuracy.
 */

 #include "p1_lib.h"  // 加了这一行

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 
 /*
  * Function: pad_zero
  * -------------------
  * Pads a binary string with leading or trailing zeros to ensure a fixed size.
  *
  *  source: The input binary string.
  *  target: The output string with padding applied.
  *  size:   The fixed size to pad to.
  *  isLeading: If 1, pads with leading zeros; if 0, pads with trailing zeros.
  */
 void pad_zero(char *source, char *target, int size, int isLeading) {
     int len = strlen(source);
 
     if (len >= size) {
         strcpy(target, source);
         return;
     }
 
     int padCount = size - len;
 
     if (isLeading) {
         // Add leading zeros
         for (int i = 0; i < padCount; i++) {
             target[i] = '0';
         }
         strcpy(target + padCount, source);
     } else {
         // Copy source and add trailing zeros
         strcpy(target, source);
         for (int i = 0; i < padCount; i++) {
             target[len + i] = '0';
         }
         target[size] = '\0';
     }
 }
 
 /*
  * Function: int_to_binary
  * ------------------------
  * Converts an integer to its binary representation.
  *
  *  num: The integer to convert.
  *  binary: The output binary string.
  */
 void int_to_binary(long long int num, char *binary) {
     int index = 0;
     char temp[MAX_SIZE] = {0};
 
     while (num > 0) {
         temp[index++] = (num % 2) + '0';
         num /= 2;
     }
 
     int len = index;
     for (int i = 0; i < len; i++) {
         binary[i] = temp[len - i - 1]; // Reverse the binary string
     }
     binary[len] = '\0';
 }
 
 /*
  * Function: dec_to_binary
  * ------------------------
  * Converts a fractional decimal to its binary representation.
  *
  *  dec: The fractional part of a number.
  *  binary: The output binary string.
  */
 void dec_to_binary(long double dec, char *binary) {
     int index = 0;
 
     if (dec == 0.0) {
         binary[index++] = '0';
     }
 
     while (dec > 0.0 && index < 32) { // Limit to 32-bit precision
         dec *= 2.0;
         if (dec >= 1.0) {
             binary[index++] = '1';
             dec -= 1.0;
         } else {
             binary[index++] = '0';
         }
     }
     binary[index] = '\0';
 }
 
 /*
  * Function: calculate_mantissa
  * -----------------------------
  * Computes the mantissa from integer and fractional binary parts.
  *
  *  int_binary: Binary representation of the integer part.
  *  dec_binary: Binary representation of the decimal part.
  *  mantissa: The output mantissa string.
  */
 void calculate_mantissa(char *int_binary, char *dec_binary, char *mantissa) {
     char binary[MAX_SIZE] = {0};
     strcpy(binary, int_binary);
     strcat(binary, dec_binary);
 
     // Normalize by removing leading zeros
     while (binary[0] == '0' && binary[1] != '\0') {
         memmove(binary, binary + 1, strlen(binary));
     }
 
     if (binary[0] == '\0') {
         strcpy(binary, "1");
     }
 
     pad_zero(binary, mantissa, MANTISSA_SIZE, 0); // Pad with trailing zeros
     mantissa[MANTISSA_SIZE] = '\0';
 }
 
 /*
  * Function: calculate_exponent
  * -----------------------------
  * Computes the exponent value for IEEE 754 representation.
  *
  *  real: The input floating-point number.
  *  exponent: The output exponent string.
  */
 void calculate_exponent(long double real, char *exponent) {
     int exp_val = 0;
 
     if (real >= 1.0) {
         while (real >= 2.0) {
             real /= 2.0;
             exp_val++;
         }
     } else {
         while (real < 1.0) {
             real *= 2.0;
             exp_val--;
         }
     }
 
     exp_val += 127; // Biasing exponent
     if (exp_val > 255) {
         exp_val = 255; // Clamp overflow
     }
 
     char temp[MAX_SIZE];
     int_to_binary(exp_val, temp);
     pad_zero(temp, exponent, EXPONENT_SIZE, 1); // Pad with leading zeros
 }

 
 F32Repr float_to_IEEE754(long double real) {
     F32Repr repr;
     repr.sign[0] = (real >= 0.0) ? '0' : '1'; // Determine sign bit
     repr.sign[1] = '\0';
     real = fabs(real);

     long long int int_part = (long long int) real;
     long double dec_part = real - int_part;

     char int_binary[MAX_SIZE] = {0}, dec_binary[MAX_SIZE] = {0};
     int_to_binary(int_part, int_binary);
     dec_to_binary(dec_part, dec_binary);

     calculate_mantissa(int_binary, dec_binary, repr.mantissa);
     calculate_exponent(real, repr.exponent);

     if (strcmp(repr.exponent, "11111111") == 0) { // Check for overflow
         memset(repr.mantissa, '0', MANTISSA_SIZE);
         repr.mantissa[MANTISSA_SIZE] = '\0';
     }
     return repr;
 }
 
//  int main() {
//      printf("Input a real number: "); fflush(stdout);
//      long double real;
//      scanf("%Lf", &real);
 
//      F32Repr repr;
//      repr.sign[0] = (real >= 0.0) ? '0' : '1'; // Determine sign bit
//      repr.sign[1] = '\0';
//      real = fabs(real);
 
//      long long int int_part = (long long int) real;
//      long double dec_part = real - int_part;
 
//      char int_binary[MAX_SIZE] = {0}, dec_binary[MAX_SIZE] = {0};
//      int_to_binary(int_part, int_binary);
//      dec_to_binary(dec_part, dec_binary);
 
//      calculate_mantissa(int_binary, dec_binary, repr.mantissa);
//      calculate_exponent(real, repr.exponent);
 
//      if (strcmp(repr.exponent, "11111111") == 0) { // Check for overflow
//          memset(repr.mantissa, '0', MANTISSA_SIZE);
//          repr.mantissa[MANTISSA_SIZE] = '\0';
//          printf("Overflow!!!\n");
//      }
 
//      printf("IEEE 754 Representation:\nSign: %s\nMantissa (24-bit): %s\nExponent: %s\n", repr.sign, repr.mantissa, repr.exponent);
 
//      return 0;
//  }
 