#include <stdio.h>
#include <stdint.h>

// Initial permutation choice 1
int pc1[56] = {
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};

// Initial permutation choice 2
int pc2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

// Function to perform permutation on data according to given permutation table
void permute(uint64_t *data, const int *perm_table, int size) {
    uint64_t result = 0;
    int i;
    for (i = 0; i < size; i++) {
        result <<= 1;
        result |= ((*data >> (64 - perm_table[i])) & 1);
    }
    *data = result;
}

// Function to perform DES round
void des_round(uint32_t *left, uint32_t *right, uint32_t key) {
    uint32_t temp = *right;
    *right = *left ^ (temp & 0xFEFEFEFE) >> 1;
    *left = temp;
    *left ^= ((temp << 1) ^ ((temp & 0x80808080) ? 0x1B : 0)) & 0xFEFEFEFE;
    *left ^= key;
}

// Function to perform DES encryption
void des_encrypt(uint64_t *data, uint64_t *keys) {
    permute(data, pc1, 56);

    uint32_t left = (*data >> 32) & 0xFFFFFFFF;
    uint32_t right = *data & 0xFFFFFFFF;
    int i ;

    for (i = 0; i < 16; i++) {
        des_round(&left, &right, keys[i]);
    }

    *data = ((uint64_t)right << 32) | left;

    permute(data, pc2, 64);
}

// Function to generate encryption keys with specified subsets
void generate_encrypt_keys(uint64_t initial_key, uint64_t *keys) {
    uint32_t left = (initial_key >> 32) & 0xFFFFFFFF;
    uint32_t right = initial_key & 0xFFFFFFFF;

    permute(&initial_key, pc1, 56);
    int i;
    for (i = 0; i < 16; i++) {
        int shift = (i < 2 || (i >= 8 && i < 10)) ? 1 : 2;
        left = (left << shift) | (left >> (28 - shift));
        right = (right << shift) | (right >> (28 - shift));

        uint64_t combined = ((uint64_t)left << 32) | right;

        permute(&combined, pc2, 48);

        keys[i] = combined;
    }
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t initial_key = 0x133457799BBCDFF1;
    uint64_t keys[16];

    generate_encrypt_keys(initial_key, keys);

    des_encrypt(&plaintext, keys);

    printf("Encrypted ciphertext: %016llX\n", plaintext);

    return 0;
}

