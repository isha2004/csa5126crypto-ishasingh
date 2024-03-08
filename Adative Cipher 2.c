#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the frequency distribution of letters in the text
void calculateFrequency(char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            frequency[index]++;
        }
    }
}

// Function to decrypt the ciphertext using a given key
void decryptWithKey(char *ciphertext, int key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            ciphertext[i] = ((ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        }
    }
}

// Function to perform a letter frequency attack and print possible plaintexts
void letterFrequencyAttack(char *ciphertext, int topN) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    printf("Frequency Distribution in Ciphertext:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %d\n", 'A' + i, frequency[i]);
    }

    // Find the most common letter in English
    int mostCommonIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > frequency[mostCommonIndex]) {
            mostCommonIndex = i;
        }
    }

    // Calculate the key based on the most common English letter 'e'
    int key = (mostCommonIndex + ALPHABET_SIZE - ('e' - 'a')) % ALPHABET_SIZE;

    printf("\nPossible Plaintexts:\n");
    for (int i = 0; i < topN; i++) {
        decryptWithKey(ciphertext, key);
        printf("Key = %d: %s\n", key, ciphertext);
        key = (key + 1) % ALPHABET_SIZE; // Try the next possible key
    }
}

int main() {
    char ciphertext[1000];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    letterFrequencyAttack(ciphertext, topN);

    return 0;
}

