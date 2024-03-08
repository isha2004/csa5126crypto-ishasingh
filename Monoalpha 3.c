#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate letter frequencies in the given text
void calculateFrequencies(const char *text, int *frequencies) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            frequencies[letter - 'a']++;
        }
    }
}

// Function to print letter frequencies
void printFrequencies(int *frequencies) {
    printf("Letter Frequencies:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %d\n", 'a' + i, frequencies[i]);
    }
    printf("\n");
}

// Function to perform letter frequency attack
void letterFrequencyAttack(const char *ciphertext) {
    int frequencies[ALPHABET_SIZE] = {0};
    calculateFrequencies(ciphertext, frequencies);

    printFrequencies(frequencies);

    // Sorting the frequencies and identifying potential mappings
    int sortedIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i;
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequencies[sortedIndices[i]] < frequencies[sortedIndices[j]]) {
                // Swap indices
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }

    // Mapping potential plaintext letters based on frequency
    char mapping[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[sortedIndices[i]] = 'a' + i;
    }

    // Print potential plaintexts
    printf("Potential Plaintexts:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("Mapping %c -> %c: ", 'a' + sortedIndices[i], mapping[sortedIndices[i]]);
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            if (isalpha(ciphertext[j])) {
                char letter = tolower(ciphertext[j]);
                printf("%c", isupper(ciphertext[j]) ? toupper(mapping[letter - 'a']) : mapping[letter - 'a']);
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    const char *ciphertext = "Uifsf jt b tfdsfu mfuufs.";

    printf("Ciphertext:\n%s\n\n", ciphertext);

    letterFrequencyAttack(ciphertext);

    return 0;
}

