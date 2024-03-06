#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

// Function to perform CBC mode encryption using 3DES
void encrypt_cbc_3des(const char *input, const char *key, const char *iv, char *output) {
    DES_cblock des_key1, des_key2, des_key3, des_iv;
    DES_key_schedule ks1, ks2, ks3;

    // Set the 3DES keys
    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key + 16, 8);

    // Set the IV (Initialization Vector)
    memcpy(des_iv, iv, 8);

    // Set up the key schedules
    DES_set_key_unchecked(&des_key1, &ks1);
    DES_set_key_unchecked(&des_key2, &ks2);
    DES_set_key_unchecked(&des_key3, &ks3);

    // Perform CBC mode encryption
    int input_len = strlen(input);
    char *previous_block = des_iv;

    int i, j;  // Declare i and j outside the for loop

    for (i = 0; i < input_len; i += 8) {
        char input_block[8];
        char output_block[8];

        // XOR the current block with the previous ciphertext block (or IV for the first block)
        for (j = 0; j < 8; ++j) {
            input_block[j] = input[i + j] ^ previous_block[j];
        }

        // Encrypt the XOR result with 3DES
        DES_ecb3_encrypt((DES_cblock *)input_block, (DES_cblock *)output_block, &ks1, &ks2, &ks3, DES_ENCRYPT);

        // Copy the ciphertext to the output buffer
        memcpy(output + i, output_block, 8);

        // Update the previous block for the next iteration
        memcpy(previous_block, output_block, 8);
    }

    // Null-terminate the output string
    output[input_len] = '\0';
}

int main() {
    const char *input = "Hello123";  // Replace with your input data
    const char *key = "SecretKey";   // Replace with your 3DES key (24 bytes)
    const char *iv = "IV123456";     // Replace with your initialization vector (8 bytes)

    int input_len = strlen(input);
    char *output = (char *)malloc(input_len + 1);

    encrypt_cbc_3des(input, key, iv, output);

    printf("Input: %s\n", input);
    printf("Encrypted output: %s\n", output);

    free(output);

    return 0;
}

