#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateCipherSequence(char *keyword, char *cipherSequence) {
    int i, j, len, k;

    // Initialize the cipher sequence with the keyword
    len = strlen(keyword);
    strcpy(cipherSequence, keyword);

    // Mark letters used in the keyword
    for (i = 0; i < len; i++) {
        if (isalpha(keyword[i])) {
            keyword[i] = toupper(keyword[i]);
        }
    }

    // Fill in the remaining unused letters in normal order
    k = 'A';
    for (i = len; i < 26; i++) {
        while (strchr(keyword, k)) {
            k++;
        }

        cipherSequence[i] = k;
        k++;
    }

    cipherSequence[i] = '\0';
}

void encryptMonoalphabetic(char *plaintext, char *cipherSequence, char *ciphertext) {
    int i, len;

    len = strlen(plaintext);

    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = cipherSequence[plaintext[i] - base];
        } else {
            // Non-alphabetic characters are left unchanged
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipherSequence[27];
    char plaintext[100];
    char ciphertext[100];

    // Generate the cipher sequence from the keyword
    generateCipherSequence(keyword, cipherSequence);

    printf("Cipher Sequence: %s\n", cipherSequence);

    printf("Enter a message to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove newline character from input
    strtok(plaintext, "\n");

    // Encrypt the plaintext using the monoalphabetic cipher
    encryptMonoalphabetic(plaintext, cipherSequence, ciphertext);

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}

