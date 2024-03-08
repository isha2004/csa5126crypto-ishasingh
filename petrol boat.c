#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to find the position of a letter in the key table
void findPosition(char keyTable[SIZE][SIZE], char letter, int *row, int *col) {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decipher a Playfair code
void decipherPlayfair(char *ciphertext, char keyTable[SIZE][SIZE]) {
    int i, len = strlen(ciphertext);
    int row1, col1, row2, col2;

    for (i = 0; i < len; i += 2) {
        char first = ciphertext[i];
        char second = ciphertext[i + 1];

        findPosition(keyTable, first, &row1, &col1);
        findPosition(keyTable, second, &row2, &col2);

        // Same row, replace with letters to the left
        if (row1 == row2) {
            col1 = (col1 - 1 + SIZE) % SIZE;
            col2 = (col2 - 1 + SIZE) % SIZE;
        }
        // Same column, replace with letters above
        else if (col1 == col2) {
            row1 = (row1 - 1 + SIZE) % SIZE;
            row2 = (row2 - 1 + SIZE) % SIZE;
        }
        // Different row and column, replace with letters in the rectangle defined by the original pair
        else {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        printf("%c%c", keyTable[row1][col1], keyTable[row2][col2]);
    }
}

int main() {
    // The provided Playfair ciphertext
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";

    // The Playfair key table
    char keyTable[SIZE][SIZE] = {
        {'K', 'E', 'Y', 'W', 'O'},
        {'R', 'D', 'A', 'B', 'C'},
        {'F', 'G', 'H', 'I', 'L'},
        {'M', 'N', 'P', 'Q', 'S'},
        {'T', 'U', 'V', 'X', 'Z'}
    };

    // Decrypt the Playfair code
    printf("Deciphered message:\n");
    decipherPlayfair(ciphertext, keyTable);

    return 0;
}

