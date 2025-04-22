#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    // Initialize random seed
    srand(time(0));

    // Create an array to hold 100 random numbers
    int randomNumbers[100];
    int sum = 0;

    // Generate 100 random numbers and calculate the sum
    for (int i = 0; i < 100; i++) {
        randomNumbers[i] = rand() % 100; // Generate a random number between 0 and 99
        sum += randomNumbers[i];
    }

    // Print the sum of the array
    printf("Sum of the random numbers: %d\n", sum);

    // Create a file name based on the sum
    char fileName[20];
    sprintf(fileName, "numbers.%04d", sum);

    // Open the file for writing
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the random numbers to the file
    for (int i = 0; i < 100; i++) {
        fprintf(file, "%d\n", randomNumbers[i]);
    }

    // Close the file
    fclose(file);

    printf("Random numbers written to file: %s\n", fileName);

    return 0;
}
