#include <stdio.h>

/**
 * Sets the parity bit for an 8-bit value.
 * 
 * @param byte         The 8-bit input value (0-255), stored in an unsigned int.
 * @param even_parity  If non-zero, use even parity; otherwise, use odd parity.
 * @return             A 9-bit value stored in an unsigned int, with the parity bit as the 9th (MSB).
 */
unsigned int set_parity_bit(unsigned int byte, int even_parity) {
    unsigned int count = 0;

    // Count number of 1s in the byte (only consider the lowest 8 bits)
    for (int i = 0; i < 8; i++) {
        if (byte & (1 << i)) {
            count++;
        }
    }

    // Determine the parity bit (1 or 0)
    unsigned int parity_bit = 0;
    if (even_parity) {
        // Set parity bit to make total number of 1s even
        parity_bit = (count % 2 != 0) ? 1 : 0;
    } else {
        // Set parity bit to make total number of 1s odd
        parity_bit = (count % 2 == 0) ? 1 : 0;
    }

    // Shift the parity bit to the 9th bit (bit 8), then OR it with the original byte
    unsigned int result = (parity_bit << 8) | (byte & 0xFF);
    return result;
}

// Example usage
int main() {
    unsigned int data = 0b10101100; // 0xAC
    unsigned int result = set_parity_bit(data, 1); // Use even parity

    printf("Original byte: 0x%02X\n", data);
    printf("With parity bit: 0x%03X\n", result); // Print result as 3-digit hex (9-bit)
    return 0;
}
