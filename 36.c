#include <stdio.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

int affineEncrypt(int a, int b, int p) {
    return (a * p + b) % 26;
}

int affineDecrypt(int a, int b, int c) {
    int aInverse = modInverse(a, 26);
    if (aInverse == -1) {
        printf("Error: Modular inverse does not exist for the given 'a'.\n");
        return -1;
    }

    return (aInverse * (c - b + 26)) % 26;
}

int main() {
    int a = 3; // Choose a value for 'a'
    int b = 5; // Choose a value for 'b'

    // Check if 'a' has a modular inverse
    int aInverse = modInverse(a, 26);
    if (aInverse == -1) {
        printf("Error: Modular inverse does not exist for the given 'a'.\n");
        return 1;
    }

    const char *plaintext = "HELLO";
    int ciphertext[5];

    // Encryption
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int p = (int)toupper(plaintext[i]) - 'A';
            ciphertext[i] = affineEncrypt(a, b, p);
        } else {
            // Non-alphabetic characters remain unchanged
            ciphertext[i] = plaintext[i];
        }
    }

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            printf("%c", (char)(ciphertext[i] + 'A'));
        } else {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

    // Decryption
    printf("Decrypted Text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int decrypted = affineDecrypt(a, b, ciphertext[i]);
            if (decrypted != -1) {
                printf("%c", (char)(decrypted + 'A'));
            } else {
                return 1; // Error in decryption
            }
        } else {
            // Non-alphabetic characters remain unchanged
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

    return 0;
}

