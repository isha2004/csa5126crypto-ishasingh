#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to find the position of a letter in the Playfair matrix
void findPosition(char matrix[SIZE][SIZE], char letter, int *row, int *col) {
	int i,j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a message using the Playfair cipher
void encryptPlayfair(char *plaintext, char matrix[SIZE][SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    int i, x, y, row1, col1, row2, col2;

    for (i = 0; i < len; i += 2) {
        char first = plaintext[i];
        char second = (i + 1 < len) ? plaintext[i + 1] : 'X'; // Use 'X' for odd-length messages

        findPosition(matrix, toupper(first), &x, &y);
        row1 = x;
        col1 = y;

        findPosition(matrix, toupper(second), &x, &y);
        row2 = x;
        col2 = y;

        // Same row, replace with letters to the right
        if (row1 == row2) {
            col1 = (col1 + 1) % SIZE;
            col2 = (col2 + 1) % SIZE;
        }
        // Same column, replace with letters below
        else if (col1 == col2) {
            row1 = (row1 + 1) % SIZE;
            row2 = (row2 + 1) % SIZE;
        }
        // Different row and column, replace with letters in the rectangle defined by the original pair
        else {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        ciphertext[i] = matrix[row1][col1];
        ciphertext[i + 1] = matrix[row2][col2];
    }

    ciphertext[i] = '\0';
}

int main() {
    char matrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[100];

    // Encrypt the message using the Playfair cipher
    encryptPlayfair(plaintext, matrix, ciphertext);

    // Print the encrypted message
    printf("Encrypted message:\n%s\n", ciphertext);

    return 0;
}

