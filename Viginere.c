#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void generateRandomKey(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;
    }
}

void encryptVigenereOneTimePad(const char *plaintext, int *key, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + key[i]) % 26 + base;
        } else {
            // Non-alphabetic characters remain unchanged
            ciphertext[i] = plaintext[i];
        }
    }
}

void decryptVigenereOneTimePad(const char *ciphertext, int *key, char *decryptedText) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            decryptedText[i] = (ciphertext[i] - base - key[i] + 26) % 26 + base;
        } else {
            // Non-alphabetic characters remain unchanged
            decryptedText[i] = ciphertext[i];
        }
    }
}

int main() {
    srand(time(NULL));

    const char *plaintext = "HelloWorld";
    int keyLength = strlen(plaintext);

    int key[keyLength];
    generateRandomKey(key, keyLength);

    char ciphertext[keyLength + 1];
    encryptVigenereOneTimePad(plaintext, key, ciphertext);
    ciphertext[keyLength] = '\0';

    char decryptedText[keyLength + 1];
    decryptVigenereOneTimePad(ciphertext, key, decryptedText);
    decryptedText[keyLength] = '\0';

    printf("Plaintext: %s\n", plaintext);
    printf("Key: ");
    for (int i = 0; i < keyLength; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

