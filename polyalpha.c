#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptVigenere(char *plaintext, char *key) {
    int i, j, keyLen, textLen;
    char encryptedText[100];

    keyLen = strlen(key);
    textLen = strlen(plaintext);

    for (i = 0, j = 0; i < textLen; i++) {
        char currentChar = plaintext[i];

        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';

            // Apply the Vigenère cipher formula
            encryptedText[i] = (currentChar - base + key[j] - 'A') % 26 + base;

            // Move to the next key character
            j = (j + 1) % keyLen;
        } else {
            // Non-alphabetic characters are left unchanged
            encryptedText[i] = currentChar;
        }
    }

    encryptedText[i] = '\0';

    // Copy the encrypted text back to the original variable
    strcpy(plaintext, encryptedText);
}

int main() {
    char plaintext[100];
    char key[100];

    printf("Enter a message to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newline characters from input
    strtok(plaintext, "\n");
    strtok(key, "\n");

    encryptVigenere(plaintext, key);

    printf("Encrypted message: %s", plaintext);

    return 0;
}

