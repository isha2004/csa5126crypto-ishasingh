#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 2

// Function to find the position of a letter in the alphabet
int getPosition(char letter) {
    return toupper(letter) - 'A';
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int a, int b, int c, int d) {
    return a * d - b * c;
}

// Function to find the modular multiplicative inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    int x;  // Declare x outside the for loop
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  // Inverse doesn't exist
}

// Function to perform a known-plaintext attack on the Hill cipher
void knownPlaintextAttack(char *plaintext, char *ciphertext, int *key) {
    int p1 = getPosition(plaintext[0]);
    int p2 = getPosition(plaintext[1]);
    int c1 = getPosition(ciphertext[0]);
    int c2 = getPosition(ciphertext[1]);

    // Solve the system of linear equations to find the key matrix
    int detInverse = modInverse(determinant(p1, p2, p1, p2), 26);
    if (detInverse == -1) {
        printf("Inverse does not exist. Known-plaintext attack failed.\n");
        return;
    }

    // Calculate the key matrix
    key[0] = (detInverse * c1 - detInverse * c2 + 26) % 26;
    key[1] = (detInverse * -p2 + detInverse * p1 + 26) % 26;
    key[2] = (detInverse * -p1 + detInverse * p2 + 26) % 26;
    key[3] = (detInverse * c2 - detInverse * c1 + 26) % 26;
}

int main() {
    // Given plaintext and corresponding ciphertext
    char plaintext[] = "ME";
    char ciphertext[] = "HN";

    // Key matrix variables
    int key[SIZE * SIZE];

    // Perform known-plaintext attack
    knownPlaintextAttack(plaintext, ciphertext, key);

    // Print the recovered key matrix
    printf("Recovered key matrix:\n");
    printf("%d %d\n", key[0], key[1]);
    printf("%d %d\n", key[2], key[3]);

    return 0;
}

