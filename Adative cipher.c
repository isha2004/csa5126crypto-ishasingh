#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to count the frequency of each letter in the given text
void countLetterFrequency(char *text, int *frequency) {
    int len = strlen(text);
    int i;

    for ( i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            frequency[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to decrypt a message using the additive cipher with a given shift
void decryptAdditiveCipher(char *ciphertext, int shift, char *decryptedText) {
    int len = strlen(ciphertext);
    int base;
    int i;

    for ( i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            base = isupper(ciphertext[i]) ? 'A' : 'a';
            decryptedText[i] = ((ciphertext[i] - base - shift + 26) % 26) + base;
        } else {
            decryptedText[i] = ciphertext[i];
        }
    }

    decryptedText[len] = '\0';
}

// Function to perform a letter frequency attack on an additive cipher
void letterFrequencyAttack(char *ciphertext, int topPlaintexts) {
    int frequency[26] = {0};
    countLetterFrequency(ciphertext, frequency);

    // Find the most frequent letter in the ciphertext
    int maxFrequency = 0;
    int maxFrequencyIndex = 0;
    int i;
    for (i = 0; i < 26; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            maxFrequencyIndex = i;
        }
    }

    // Calculate the shift value based on the most frequent letter
    int shift = (maxFrequencyIndex + 26 - ('E' - 'A')) % 26;

    // Decrypt the ciphertext with the calculated shift
    char decryptedText[100];
    decryptAdditiveCipher(ciphertext, shift, decryptedText);

    // Print the decrypted text
    printf("Decrypted text with shift %d:\n%s\n", shift, decryptedText);
}

int main() {
    // Given ciphertext
    char ciphertext[] = "WKLV LV D WHVW PHVVDJH";

    // Specify the number of top possible plaintexts to generate
    int topPlaintexts = 10;

    // Perform a letter frequency attack on the additive cipher
    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

