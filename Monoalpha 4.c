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
void decryptWithKey(char *ciphertext, char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int index = key[ciphertext[i] - base] - 'a';
            ciphertext[i] = 'a' + index;
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

    // Create a mapping of letters sorted by frequency in the ciphertext
    char key[ALPHABET_SIZE + 1];
    key[ALPHABET_SIZE] = '\0';
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int maxIndex = 0;
        for (int j = 1; j < ALPHABET_SIZE; j++) {
            if (frequency[j] > frequency[maxIndex]) {
                maxIndex = j;
            }
        }
        key[maxIndex] = 'a' + i;
        frequency[maxIndex] = -1; // Mark as visited
    }

    printf("\nKey Mapping based on Frequency in Ciphertext:\n%s\n", key);

    // Decrypt with the key to get possible plaintexts
    printf("\nPossible Plaintexts:\n");
    for (int i = 0; i < topN; i++) {
        decryptWithKey(ciphertext, key);
        printf("Key Mapping #%d: %s\n", i + 1, key);
        printf("Plaintext #%d: %s\n\n", i + 1, ciphertext);
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

