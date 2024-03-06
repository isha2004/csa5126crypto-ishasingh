#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptMonoalphabetic(char *plaintext, char *substitutionKey) {
    int i;

    for (i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            char originalChar = tolower(plaintext[i]);
            char substitutionChar = substitutionKey[originalChar - 'a'];

            if (isupper(plaintext[i])) {
                plaintext[i] = toupper(substitutionChar);
            } else {
                plaintext[i] = substitutionChar;
            }
        }
    }
}

int main() {
    char plaintext[100];
    char substitutionKey[26];

    // Example substitution key (you can customize it)
    strcpy(substitutionKey, "zyxwvutsrqponmlkjihgfedcba");

    printf("Enter a message to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    encryptMonoalphabetic(plaintext, substitutionKey);

    printf("Encrypted message: %s", plaintext);

    return 0;
}

