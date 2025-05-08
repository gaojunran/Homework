#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NUMBERS 100

typedef struct NodeValue {
    float value; // The actual floating-point value
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
 * Print the linked list to standard output.
 *
 * @param h Pointer to the head of the linked list.
 */
void print_list(Node* h, const char* filename) {
    FILE* output = fopen(filename, "w");
    if (output == NULL) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    if (h == NULL) {
        fprintf(output, "The list is empty.\n");
    } else {
        fprintf(output, "Values in the list are: \n");
        Node* current = h;
        while (current != NULL) {
            fprintf(output, "%.6f\n", current->value->value);
            current = current->next;
        }
        fprintf(output, "\n");
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
        free(temp->value);  // Free the NodeValue structure
        free(temp);         // Free the Node structure
    }
}

/**
 * Main function to generate random floating-point numbers and store them in linked lists based on their values.
 *
 * @return Exit status.
 */
int main() {
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

    // Generate and insert random numbers
    for (unsigned int count = 0; count < MAX_NUMBERS; count++) {
        float random_value = generate_random();
        NodeValue* node_value = (NodeValue*)malloc(sizeof(NodeValue));
        node_value->value = random_value;

        // Insert the value into the appropriate list based on its range
        if (random_value >= 1.0) {
            insert_node(&pos, &pos_tail, node_value);
        } else if (random_value > 0.0 && random_value < 1.0) {
            insert_node(&pos_frac, &pos_frac_tail, node_value);
        } else if (random_value > -1.0 && random_value < 0.0) {
            insert_node(&neg_frac, &neg_frac_tail, node_value);
        } else if (random_value <= -1.0) {
            insert_node(&neg, &neg_tail, node_value);
        }
    }

    // Print the linked lists to standard output
    print_list(pos, "pos.txt"); // Positive numbers >= 1
    print_list(pos_frac, "pos_frac.txt"); // Positive fractions < 1
    print_list(neg, "neg.txt"); // Negative numbers <= -1
    print_list(neg_frac, "neg_frac.txt"); // Negative fractions > -1

    // Free the memory allocated for the linked lists
    free_list(pos);
    free_list(pos_frac);
    free_list(neg);
    free_list(neg_frac);

    printf("Lists successfully written to files. \n");
    return EXIT_SUCCESS;
}
