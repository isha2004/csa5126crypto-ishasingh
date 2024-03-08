#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encrypt a message using the Vigenère cipher with a one-time pad
void encryptVigenereOneTimePad(char *plaintext, int *keyStream, char *ciphertext) {
    int len = strlen(plaintext);
    int i;

    for (i = 0; i < len; i++) {
        if (plaintext[i] != ' ') {
            // Encrypt each letter with a shift based on the key stream
            ciphertext[i] = ((plaintext[i] - 'A' + keyStream[i % len]) % 26) + 'A';
        } else {
            // Preserve spaces in the ciphertext
            ciphertext[i] = ' ';
        }
    }

    ciphertext[i] = '\0';
}

// Function to decrypt a message using the Vigenère cipher with a one-time pad
void decryptVigenereOneTimePad(char *ciphertext, int *keyStream, char *decryptedText) {
    int len = strlen(ciphertext);
    int i;

    for (i = 0; i < len; i++) {
        if (ciphertext[i] != ' ') {
            // Decrypt each letter with a shift based on the key stream
            decryptedText[i] = ((ciphertext[i] - 'A' - keyStream[i % len] + 26) % 26) + 'A';
        } else {
            // Preserve spaces in the decrypted text
            decryptedText[i] = ' ';
        }
    }

    decryptedText[i] = '\0';
}

int main() {
    // Given plaintext
    char plaintext[] = "send more money";

    // Given key stream
    int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};

    // Encrypt the plaintext using the one-time pad Vigenère cipher
    char ciphertext[100];
    encryptVigenereOneTimePad(plaintext, keyStream, ciphertext);

    // Print the encrypted message
    printf("Encrypted message:\n%s\n", ciphertext);

    // Decrypt the ciphertext to recover the original plaintext
    char decryptedText[100];
    decryptVigenereOneTimePad(ciphertext, keyStream, decryptedText);

    // Print the decrypted message
    printf("Decrypted message:\n%s\n", decryptedText);

    // Attempt to find a key that decrypts the ciphertext to "cash not needed"
    int possibleKey[13];
    int i;
    for (i = 0; i < 13; i++) {
        possibleKey[i] = ((ciphertext[i] - 'A' - (decryptedText[i] - 'A') + 26) % 26);
    }

    // Print the possible key
    printf("Possible key for 'cash not needed':\n");
    for (i = 0; i < 13; i++) {
        printf("%d ", possibleKey[i]);
    }

    return 0;
}

