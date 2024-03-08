#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareKey(char *key, char keyMatrix[SIZE][SIZE]) {
    int i, j, k, flag = 0;
    char keySet[26] = {0};

    // Copy the key into keySet, removing duplicate letters
    for (i = 0; i < strlen(key); i++) {
        if (key[i] != ' ' && keySet[key[i] - 'A'] == 0) {
            keySet[key[i] - 'A'] = 1;

            if (key[i] == 'I' || key[i] == 'J') {
                keySet['J' - 'A'] = 1;
            }
        }
    }

    // Fill the key matrix with the key
    for (i = 0, k = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            while (keySet[k] == 0) {
                k++;
            }

            keyMatrix[i][j] = 'A' + k;

            // Handle 'I' and 'J' as one letter
            if (keyMatrix[i][j] == 'J') {
                keySet['I' - 'A'] = 1;
            }

            k++;
        }
    }
}

void findPosition(char ch, int *row, int *col, char keyMatrix[SIZE][SIZE]) {
    int i, j;

    if (ch == 'J') {
        ch = 'I';
    }

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPlayfair(char *plaintext, char keyMatrix[SIZE][SIZE]) {
    int i, len, row1, col1, row2, col2;

    len = strlen(plaintext);

    for (i = 0; i < len; i += 2) {
        findPosition(plaintext[i], &row1, &col1, keyMatrix);
        findPosition(plaintext[i + 1], &row2, &col2, keyMatrix);

        if (row1 == row2) {
            plaintext[i] = keyMatrix[row1][(col1 + 1) % SIZE];
            plaintext[i + 1] = keyMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            plaintext[i] = keyMatrix[(row1 + 1) % SIZE][col1];
            plaintext[i + 1] = keyMatrix[(row2 + 1) % SIZE][col2];
        } else {
            plaintext[i] = keyMatrix[row1][col2];
            plaintext[i + 1] = keyMatrix[row2][col1];
        }
    }
}

int main() {
    char key[100], plaintext[100], keyMatrix[SIZE][SIZE];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    prepareKey(key, keyMatrix);
    encryptPlayfair(plaintext, keyMatrix);

    printf("Encrypted message: %s", plaintext);

    return 0;
}

