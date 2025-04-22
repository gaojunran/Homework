#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_INTS 100

// Function to process each file: open, read, sum, print, and close
void processFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int sum = 0;
    int number;
    for (int i = 0; i < MAX_INTS; i++) {
        if (fscanf(file, "%d", &number) != 1) {
            fprintf(stderr, "Error reading file %s\n", filename);
            fclose(file);
            return;
        }
        sum += number;
    }

    printf("Filename: %s, Sum: %d\n", filename, sum);
    fclose(file);
}

int main() {
    DIR *dir;
    struct dirent *entry;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return EXIT_FAILURE;
    }

    // Loop over the directory entries
    while ((entry = readdir(dir)) != NULL) {
        char filename[MAX_FILENAME_LENGTH];
        snprintf(filename, sizeof(filename), "%s", entry->d_name);

        // Check if the filename matches the pattern "numbers.XXXX"
        if (strncmp(filename, "numbers.", 7) == 0) {
            processFile(filename);
        }
    }

    // Close the directory
    closedir(dir);
    return EXIT_SUCCESS;
}
