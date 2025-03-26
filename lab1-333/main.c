// Author: Gao Junran
// Date: 2024-03-26
// Description: This is a program to convert a floating point number to its IEEE 754 representation.
// My program is tested in https://baseconvert.com/ieee-754-floating-point, and turns out to be accurate.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MANTISSA_SIZE 24
#define EXPONENT_SIZE 8
#define MAX_SIZE 200

typedef struct {
    char sign[2];
    char mantissa[MANTISSA_SIZE + 1];
    char exponent[EXPONENT_SIZE + 1];
} F32Repr;


void pad_zero(char *source, char *target, int size, int isLeading) {
    int len = strlen(source); 

    if (len >= size) {
        strcpy(target, source); 
        return;
    }

    int padCount = size - len; 

    if (isLeading) {
        for (int i = 0; i < padCount; i++) {
            target[i] = '0'; 
        }
        strcpy(target + padCount, source); 
    } else {
        strcpy(target, source); 
        for (int i = 0; i < padCount; i++) {
            target[len + i] = '0'; 
        }
        target[size] = '\0'; 
    }
}

void int_to_binary(long long int num, char *binary) {
    int index = 0;
    char temp[MAX_SIZE] = {0};
    while (num > 0) {
        temp[index++] = (num % 2) + '0';
        num /= 2;
    }
    int len = index;
    for (int i = 0; i < len; i++) {
        binary[i] = temp[len - i - 1];
    }
    binary[len] = '\0';
}

void dec_to_binary(long double dec, char *binary) {
    int index = 0;
    if (dec == 0.0) {
        binary[index++] = '0';
    }
    while (dec > 0.0 && index < 32) {
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

void calculate_mantissa(char *int_binary, char *dec_binary, char *mantissa) {
    char binary[MAX_SIZE] = {0};
    strcpy(binary, int_binary);
    strcat(binary, dec_binary);
    while (binary[0] == '0' && binary[1] != '\0') {
        memmove(binary, binary + 1, strlen(binary));
    }
    if (binary[0] == '\0') {
        strcpy(binary, "1");
    }
    pad_zero(binary, mantissa, MANTISSA_SIZE, 0);  // pad trailing zeros
    mantissa[MANTISSA_SIZE] = '\0';
}

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
    exp_val += 127;
    if (exp_val > 255) {
        exp_val = 255;  // ensure exponent does not exceed 8 bits
    }
    char temp[MAX_SIZE];
    int_to_binary(exp_val, temp);
    pad_zero(temp, exponent, EXPONENT_SIZE, 1);  // pad leading zeros
}

int main() {
    printf("Input a real number: "); fflush(stdout);
    long double real;
    scanf("%Lf", &real);
    
    F32Repr repr;
    repr.sign[0] = (real >= 0.0) ? '0' : '1';
    repr.sign[1] = '\0';
    real = fabs(real);
    
    long long int int_part = (long long int) real;
    long double dec_part = real - int_part;
    
    char int_binary[MAX_SIZE] = {0}, dec_binary[MAX_SIZE] = {0};
    int_to_binary(int_part, int_binary);
    dec_to_binary(dec_part, dec_binary);
    
    calculate_mantissa(int_binary, dec_binary, repr.mantissa);
    calculate_exponent(real, repr.exponent);
    
    if (strcmp(repr.exponent, "11111111") == 0) {
        memset(repr.mantissa, '0', MANTISSA_SIZE);
        repr.mantissa[MANTISSA_SIZE] = '\0';
        printf("The IEEE 754 Single Precision is \nSign: %s\nMantissa (24 bit): %s\nExponent: %s\n", repr.sign, repr.mantissa, repr.exponent);
        fflush(stdout);
        printf("Overflow!!!\n"); fflush(stdout);
    } else {
        printf("The IEEE 754 Single Precision is \nSign: %s\nMantissa (24 bit): %s\nExponent: %s\n", repr.sign, repr.mantissa, repr.exponent);
        fflush(stdout);
    }
    return 0;
}
