#include <stdio.h>

// Initial permutation table for S-DES
int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};

// 8 S-Boxes for S-DES
int S_BOX[4][4][2][2] = {
    {{{0, 1}, {0, 0}}, {{1, 1}, {1, 0}}, {{1, 0}, {0, 1}}, {{0, 0}, {1, 1}}},
    {{{0, 0}, {0, 1}}, {{1, 0}, {1, 1}}, {{0, 1}, {1, 1}}, {{1, 1}, {0, 0}}},
    {{{1, 1}, {0, 1}}, {{1, 0}, {0, 0}}, {{0, 0}, {1, 0}}, {{0, 1}, {1, 1}}},
    {{{1, 0}, {0, 0}}, {{0, 0}, {1, 1}}, {{1, 1}, {1, 0}}, {{0, 1}, {1, 0}}}
};

// Permutation P4 for S-DES
int P4[] = {2, 4, 3, 1};

// Initial permutation for key generation
int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};

// Left circular shift for key generation
int LS1[] = {2, 4, 1, 3};

// 8-bit block permutation for S-DES
int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};

// Function to perform an 8-bit permutation
void permute8(int *input, int *perm_table, int *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = input[perm_table[i] - 1];
    }
}

// Function to perform a left circular shift on a 5-bit key
void leftCircularShift(int *key, int *shift_table, int size) {
    int temp = key[0];

    for (int i = 0; i < size - 1; i++) {
        key[i] = key[i + 1];
    }

    key[size - 1] = temp;
}

// Function to generate a subkey for S-DES
void generateSubKey(int *key, int *subkey, int *p10, int *ls1, int *p8) {
    int tempKey[10];

    // Apply permutation P10
    permute8(key, p10, tempKey);

    // Apply left circular shift (LS-1)
    leftCircularShift(tempKey, ls1, 5);

    // Apply permutation P8 to get the first subkey
    permute8(tempKey, p8, subkey);
}

// Function to perform an S-Box substitution
void sBoxSubstitution(int *input, int *output) {
    int row = (input[0] << 1) + input[3];
    int col = (input[1] << 1) + input[2];

    output[0] = S_BOX[row][col][0][0];
    output[1] = S_BOX[row][col][0][1];
    output[2] = S_BOX[row][col][1][0];
    output[3] = S_BOX[row][col][1][1];
}

// Function to perform the F function in S-DES
void sDesF(int *input, int *key, int *output) {
    int expanded[8];
    int sBoxOut[4];

    // Expand the 4-bit input to 8 bits
    permute8(input, P4, expanded);

    // XOR the expanded input with the key
    for (int i = 0; i < 8; i++) {
        expanded[i] ^= key[i];
    }

    // Apply S-Box substitution
    sBoxSubstitution(expanded, sBoxOut);

    // Permute the S-Box output
    permute8(sBoxOut, P4, output);
}

// Function to perform S-DES encryption in CBC mode
void encryptSDesCBC(int *plaintext, int *key, int *iv, int *ciphertext) {
    int subkey1[8], subkey2[8];
    int temp[8], temp2[8];
    int xorResult[8];

    // Generate the first and second subkeys
    generateSubKey(key, subkey1, P10, LS1, P8);
    generateSubKey(subkey1, subkey2, P10, LS1, P8);

    // Initial XOR with IV
    for (int i = 0; i < 8; i++) {
        temp[i] = plaintext[i] ^ iv[i];
    }

    // First round
    sDesF(temp, subkey1, temp2);
    for (int i = 0; i < 8; i++) {
        temp2[i] ^= iv[i];
    }

    // Second round
    sDesF(temp2, subkey2, xorResult);

    // Final XOR with IV
    for (int i = 0; i < 8; i++) {
        ciphertext[i] = xorResult[i] ^ iv[i];
    }
}

// Function to convert a binary string to an integer array
void binaryStringToIntArray(const char *binaryStr, int *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = binaryStr[i] - '0';
    }
}

// Function to convert an integer array to a binary string
void intArrayToBinaryString(int *input, char *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = input[i] + '0';
    }
    output[8] = '\0';
}

int main() {
    int plaintext[8], key[10], iv[8], ciphertext[8];
    const char *binaryPlaintext = "0000000100100011";
    const char *binaryKey = "0111111101";
    const char *binaryIV = "10101010";

    // Convert binary strings to integer arrays
    binaryStringToIntArray(binaryPlaintext, plaintext);
    binaryStringToIntArray(binaryKey, key);
    binaryStringToInt

