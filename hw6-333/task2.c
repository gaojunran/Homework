#include <stdio.h>
#include <stdlib.h>  // For atoi()

int main(int argc, char *argv[]) {
    // Check if a number was passed as a command-line argument
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    // Convert the input string to an integer
    int number = atoi(argv[1]);

    printf("Your number was %d\n", number);

    int count = 0;  // This will store the number of 1s in binary

    // Loop through all bits of the number
    while (number > 0) {
        // Use bitwise AND to check if the least significant bit is 1
        if (number & 1) {
            count++;
        }

        // Right shift the number by 1 bit to check the next bit
        number = number >> 1;
    }

    // Output the result
    printf("In %s, there are %d bits set to 1.\n", argv[1], count);

    return 0;
}
