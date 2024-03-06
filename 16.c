#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to count the frequency of each letter in the given text
void countLetterFrequency(char *text, int *frequency) 
{
	
    int len = strlen(text);
    int i;

    for ( i = 0; i < len; i++) 
	{
        if (isalpha(text[i])) 
		{
            frequency[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to perform a letter frequency attack on a monoalphabetic substitution cipher
void letterFrequencyAttack(char *ciphertext, int topPlaintexts) 
{
    int frequency[26] = {0};
    countLetterFrequency(ciphertext, frequency);

    // Create a mapping of letters to their frequencies
    struct LetterFrequency 
	{
        char letter;
        int count;
    };

    struct LetterFrequency letterFrequencies[26];
    int i;
    for ( i = 0; i < 26; i++) 
	{
        letterFrequencies[i].letter = 'A' + i;
        letterFrequencies[i].count = frequency[i];
    }

    // Sort the mapping based on frequency in descending order

    for ( i = 0; i < 25; i++) 
	{
    	int j;
        for ( j = 0; j < 25 - i; j++) 
		{
            if (letterFrequencies[j].count < letterFrequencies[j + 1].count) 
			{
                struct LetterFrequency temp = letterFrequencies[j];
                letterFrequencies[j] = letterFrequencies[j + 1];
                letterFrequencies[j + 1] = temp;
            }
        }
    }

    // Print the sorted letter frequencies
    printf("Letter frequencies in descending order:\n");
   
    for (i = 0; i < 26; i++) {
        printf("%c: %d\n", letterFrequencies[i].letter, letterFrequencies[i].count);
    }

    // Attempt to create a mapping for decryption based on common English letter frequencies
    char mapping[26];
   
    for (i = 0; i < 26; i++) 
	{
        mapping[letterFrequencies[i].letter - 'A'] = 'E' - i;
    }

    // Decrypt the ciphertext using the mapping
    char decryptedText[100];
    int len = strlen(ciphertext);
  
    for ( i = 0; i < len; i++) 
	{
        if (isalpha(ciphertext[i])) 
		{
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            decryptedText[i] = mapping[ciphertext[i] - base] + base;
        } else 
		{
            decryptedText[i] = ciphertext[i];
        }
    }
    decryptedText[len] = '\0';

    // Print the decrypted text
    printf("\nDecrypted text with letter frequency attack:\n%s\n", decryptedText);
}

int main() {
    // Given ciphertext
    int i, j;
    char ciphertext[] = "WKLV LV D WHVW PHVVDJH";

    // Specify the number of top possible plaintexts to generate
    int topPlaintexts = 10;

    // Perform a letter frequency attack on the monoalphabetic substitution cipher
    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

