#include <stdio.h>
#include <string.h>

int main() {
    char text[100];

    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);

    int key;
    for (key = 1; key <= 25; key++) {
        char encryptedText[100];
        strcpy(encryptedText, text);

        int i;
        for (i = 0; i < strlen(text); i++) {
            if (text[i] >= 'A' && text[i] <= 'Z') {
                encryptedText[i] = (text[i] - 'A' + key) % 26 + 'A';
            } else if (text[i] >= 'a' && text[i] <= 'z') {
                encryptedText[i] = (text[i] - 'a' + key) % 26 + 'a';
            }
        }

        printf("Key %d: %s", key, encryptedText);
    }

    return 0;
}

