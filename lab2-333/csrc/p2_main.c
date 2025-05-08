#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "p1_lib.h"

#define MAX_NUMBERS 100

typedef struct NodeValue {
    float value;         // The actual floating-point value
    F32Repr* repr;       // The IEEE 754 representation of the value
    float repr_value;    // The value converted back from the IEEE 754 representation
} NodeValue;

// Define the structure for a linked list node
typedef struct Node {
    NodeValue* value;    // Pointer to the value stored in the node
    struct Node* next;   // Pointer to the next node in the list
} Node;

/**
 * Generate a random floating-point number in the range [-100, 100].
 * 
 * @return A random floating-point number.
 */
float generate_random() {
    return ((float)rand() / (float)RAND_MAX) * 200.0f - 100.0f;
}

/**
 * Insert a new node with the given value at the head of the linked list.
 * 
 * @param h Pointer to the head of the linked list.
 * @param t Pointer to the tail of the linked list.
 * @param value Pointer to the value to be stored in the new node.
 */
void insert_node(Node** h, Node** t, NodeValue* value) {
    // Create a new node
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->value = value;
    temp->next = NULL;

    // If the list is empty
    if (*h == NULL) {
        *h = temp;
        *t = temp;
    } else {
        // If the list is not empty, insert the new node at the head
        temp->next = *h;
        *h = temp;
    }
}

/**
 * Print the linked list and write its contents to a file or standard output.
 * 
 * @param h Pointer to the head of the linked list.
 * @param filename The name of the file to write to, or NULL for standard output.
 */
void fprint_list(Node* h, const char* filename) {
    FILE* output;
    if (filename != NULL) {
        output = fopen(filename, "w");
        if (output == NULL) {
            perror("Failed to create file");
            exit(EXIT_FAILURE);
        }
    } else {
        output = stdout;
    }

    if (h == NULL) {
        fprintf(output, "The list is empty.\n");
    } else {
        fprintf(output, "Values in the list are:\n");
        Node* current = h;
        while (current != NULL) {
            fprintf(output, "%.6f\nsign %s exponent %s mantissa %s\n%.6f\n", 
                current->value->value,
                current->value->repr->sign, 
                current->value->repr->exponent,
                current->value->repr->mantissa,
                current->value->repr_value
            );
            current = current->next;
        }
        fprintf(output, "\n");
    }

    if (filename != NULL) {
        fclose(output);
    }
}

/**
 * Free the memory allocated for the linked list.
 * 
 * @param head Pointer to the head of the linked list.
 */
void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->value->repr); // Free the IEEE 754 representation
        free(temp->value);       // Free the NodeValue structure
        free(temp);              // Free the Node structure
    }
}

/**
 * Main function to generate random floating-point numbers, convert them to IEEE 754 format,
 * and store them in linked lists based on their values.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments.
 * @return Exit status.
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_positive> <file_ext>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse command-line arguments
    unsigned int num_positive = atoi(argv[1]);
    char file_ext[100];
    strcpy(file_ext, argv[2]);

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize pointers for the linked lists
    Node* pos = NULL;            // List for positive numbers >= 1
    Node* pos_tail = NULL;
    Node* pos_frac = NULL;       // List for positive fractions < 1
    Node* pos_frac_tail = NULL;
    Node* neg = NULL;            // List for negative numbers <= -1
    Node* neg_tail = NULL;
    Node* neg_frac = NULL;       // List for negative fractions > -1
    Node* neg_frac_tail = NULL;

    unsigned int count = 0;
    while (count < num_positive) {
        float random_value = generate_random();
        F32Repr* repr = (F32Repr*)malloc(sizeof(F32Repr));
        *repr = float_to_IEEE754((long double) random_value); // Convert to IEEE 754 format
        NodeValue* node_value = (NodeValue*)malloc(sizeof(NodeValue));
        node_value->value = random_value;
        node_value->repr = repr;
        node_value->repr_value = IEEE754_to_float(*repr); // Convert back to float

        // Check for conversion error
        if (fabsf(node_value->repr_value - random_value) > 0.0001) {
            fprintf(stderr, "Error: Wrong conversion from ieee754 to float.\n");
            return EXIT_FAILURE;
        }

        // Insert the value into the appropriate list based on its range
        if (random_value >= 1.0) {
            insert_node(&pos, &pos_tail, node_value);
            count++;
        } else if (random_value > 0.0 && random_value < 1.0) {
            insert_node(&pos_frac, &pos_frac_tail, node_value);
        } else if (random_value > -1.0 && random_value < 0.0) {
            insert_node(&neg_frac, &neg_frac_tail, node_value);
        } else if (random_value <= -1.0) {
            insert_node(&neg, &neg_tail, node_value);
        } else {
            fprintf(stderr, "Unexpected value generated: %.2f\n", random_value);
            return EXIT_FAILURE;
        }
    }

    // Print and save the linked lists to files
    fprint_list(pos, strcat(strcpy((char[100]){}, "pos."), file_ext)); // Positive numbers >= 1
    fprint_list(pos_frac, strcat(strcpy((char[100]){}, "pos_frac."), file_ext)); // Positive fractions < 1
    fprint_list(neg, strcat(strcpy((char[100]){}, "neg."), file_ext)); // Negative numbers <= -1
    fprint_list(neg_frac, strcat(strcpy((char[100]){}, "neg_frac."), file_ext)); // Negative fractions > -1

    // Free the memory allocated for the linked lists
    free_list(pos);
    free_list(pos_frac);
    free_list(neg);
    free_list(neg_frac);

    return EXIT_SUCCESS;
}
