#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a file has a .txt or .TXT extension
int is_txt_file(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return 0;
    return strcmp(dot, ".txt") == 0 || strcmp(dot, ".TXT") == 0;
}

// Function to perform bitwise inversion on each byte and write to destination
void process_file(const char *src, const char *dst) {
    FILE *fin = fopen(src, "rb");
    if (fin == NULL) {
        perror("Error opening source file");
        exit(1);
    }

    FILE *fout = fopen(dst, "wb");
    if (fout == NULL) {
        perror("Error opening destination file");
        fclose(fin);
        exit(1);
    }

    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        fputc(~ch, fout); // Bitwise inversion
    }

    fclose(fin);
    fclose(fout);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <encrypt|decrypt> <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    const char *action = argv[1];
    const char *source_file = argv[2];
    const char *destination_file = argv[3];

    // Validate action parameter
    if (strcmp(action, "encrypt") != 0 && strcmp(action, "decrypt") != 0) {
        printf("Invalid action. Use 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    // Validate source file extension
    if (!is_txt_file(source_file)) {
        printf("Source file must have a .txt or .TXT extension.\n");
        return 1;
    }

    process_file(source_file, destination_file);

    printf("%sion completed successfully.\n", 
          strcmp(action, "encrypt") == 0 ? "Encrypt" : "Decrypt");
    return 0;
}
