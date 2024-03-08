#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

// Function to encrypt a message using the Hill cipher
void encryptHill(char *plaintext, int key[SIZE][SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    int i, j, k;
    int sum;

    for (i = 0; i < len; i += 2) {
        // Convert pairs of letters to numbers (A=0, B=1, ..., Z=25)
        int pair1 = toupper(plaintext[i]) - 'A';
        int pair2 = toupper(plaintext[i + 1]) - 'A';

        // Calculate the corresponding ciphertext pairs
        for (j = 0; j < SIZE; j++) {
            sum = 0;
            for (k = 0; k < SIZE; k++) {
                sum += key[j][k] * ((k == 0) ? pair1 : pair2);
            }
            ciphertext[i + j] = (sum % 26) + 'A';
        }
    }

    ciphertext[i] = '\0';
}

// Function to find the modular multiplicative inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  // Inverse doesn't exist
}

// Function to decrypt a message using the Hill cipher
void decryptHill(char *ciphertext, int key[SIZE][SIZE], char *decryptedText) {
    int len = strlen(ciphertext);
    int i, j, k;
    int sum;

    // Find the modular inverse of the determinant of the key matrix
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int detInverse = modInverse(det, 26);

    if (detInverse == -1) {
        printf("Decryption failed. Determinant inverse does not exist.\n");
        return;
    }

    // Calculate the adjugate of the key matrix
    int adjugate[SIZE][SIZE];
    adjugate[0][0] = key[1][1];
    adjugate[0][1] = -key[0][1];
    adjugate[1][0] = -key[1][0];
    adjugate[1][1] = key[0][0];

    // Calculate the inverse of the key matrix
    int inverse[SIZE][SIZE];
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            inverse[i][j] = (adjugate[i][j] * detInverse) % 26;
            if (inverse[i][j] < 0) {
                inverse[i][j] += 26;
            }
        }
    }

    // Decrypt the ciphertext using the inverse key matrix
    for (i = 0; i < len; i += 2) {
        // Convert pairs of letters to numbers (A=0, B=1, ..., Z=25)
        int pair1 = toupper(ciphertext[i]) - 'A';
        int pair2 = toupper(ciphertext[i + 1]) - 'A';

        // Calculate the corresponding decrypted pairs
        for (j = 0; j < SIZE; j++) {
            sum = 0;
            for (k = 0; k < SIZE; k++) {
                sum += inverse[j][k] * ((k == 0) ? pair1 : pair2);
            }
            decryptedText[i + j] = (sum % 26) + 'A';
        }
    }

    decryptedText[i] = '\0';
}

int main() {
    // Provided key matrix
    int key[SIZE][SIZE] = {
        {9, 4},
        {5, 7}
    };

    // Given plaintext
    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";

    // Encrypt the plaintext using the Hill cipher
    char ciphertext[100];
    encryptHill(plaintext, key, ciphertext);

    // Print the encrypted message
    printf("Encrypted message:\n%s\n", ciphertext);

    // Decrypt the ciphertext using the Hill cipher
    char decryptedText[100];
    decryptHill(ciphertext, key, decryptedText);

    // Print the decrypted message
    printf("Decrypted message:\n%s\n", decryptedText);

    return 0;
}

