#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

// Function to perform DES encryption in ECB mode
void encrypt_ecb_des(const char *input, const char *key, char *output) {
    DES_cblock des_key;
    DES_key_schedule ks;

    // Set the DES key
    memcpy(des_key, key, 8);

    // Set up the key schedule
    DES_set_key_unchecked(&des_key, &ks);

    int input_len = strlen(input);
    int num_blocks = (input_len + 7) / 8;  // Calculate the number of blocks

    for (int i = 0; i < num_blocks; ++i) {
        char input_block[8];
        char output_block[8];

        // Copy the current block of plaintext
        memcpy(input_block, input + i * 8, 8);

        // Encrypt the block using DES
        DES_ecb_encrypt((DES_cblock *)input_block, (DES_cblock *)output_block, &ks, DES_ENCRYPT);

        // Copy the encrypted block to the output buffer
        memcpy(output + i * 8, output_block, 8);
    }

    // Null-terminate the output string
    output[input_len] = '\0';
}

// Function to perform DES encryption in CBC mode
void encrypt_cbc_des(const char *input, const char *key, const char *iv, char *output) {
    DES_cblock des_key, des_iv;
    DES_key_schedule ks;

    // Set the DES key
    memcpy(des_key, key, 8);

    // Set the IV (Initialization Vector)
    memcpy(des_iv, iv, 8);

    // Set up the key schedule
    DES_set_key_unchecked(&des_key, &ks);

    int input_len = strlen(input);
    int num_blocks = (input_len + 7) / 8;  // Calculate the number of blocks

    char previous_block[8];
    memcpy(previous_block, des_iv, 8);

    for (int i = 0; i < num_blocks; ++i) {
        char input_block[8];
        char output_block[8];

        // XOR the current block with the previous ciphertext block (or IV for the first block)
        for (int j = 0; j < 8; ++j) {
            input_block[j] = input[i * 8 + j] ^ previous_block[j];
        }

        // Encrypt the XOR result with DES
        DES_ecb_encrypt((DES_cblock *)input_block, (DES_cblock *)output_block, &ks, DES_ENCRYPT);

        // Copy the ciphertext block to the output buffer
        memcpy(output + i * 8, output_block, 8);

        // Update the previous block for the next iteration
        memcpy(previous_block, output_block, 8);
    }

    // Null-terminate the output string
    output[input_len] = '\0';
}

// Function to perform DES encryption in CFB mode
void encrypt_cfb_des(const char *input, const char *key, const char *iv, char *output) {
    DES_cblock des_key, des_iv;
    DES_key_schedule ks;

    // Set the DES key
    memcpy(des_key, key, 8);

    // Set the IV (Initialization Vector)
    memcpy(des_iv, iv, 8);

    // Set up the key schedule
    DES_set_key_unchecked(&des_key, &ks);

    int input_len = strlen(input);
    int num_blocks = (input_len + 7) / 8;  // Calculate the number of blocks

    char feedback_block[8];
    memcpy(feedback_block, des_iv, 8);

    for (int i = 0; i < num_blocks; ++i) {
        char input_block[8];
        char output_block[8];

        // Encrypt the feedback block using DES
        DES_ecb_encrypt((DES_cblock *)feedback_block, (DES_cblock *)output_block, &ks, DES_ENCRYPT);

        // XOR the encrypted feedback block with the current plaintext block
        for (int j = 0; j < 8; ++j) {
            output[i * 8 + j] = input[i * 8 + j] ^ output_block[j];
        }

        // Update the feedback block for the next iteration
        memcpy(feedback_block, output + i * 8, 8);
    }

    // Null-terminate the output string
    output[input_len] = '\0';
}

int main() {
    const char *plaintext = "Hello123";  // Replace with your plaintext
    const char *key = "SecretKey";      // Replace with your DES key (8 bytes)
    const char *iv = "IV123456";        // Replace with your initialization vector (8 bytes)

    int input_len = strlen(plaintext);
    char ciphertext_ecb[input_len + 1];
    char ciphertext_cbc[input_len + 1];
    char ciphertext_cfb[input_len + 1];

    // Encrypt the plaintext using ECB mode
    encrypt_ecb_des(plaintext, key, ciphertext_ecb);

    // Encrypt the plaintext using CBC mode
    encrypt_cbc_des(plaintext, key, iv, ciphertext_cbc);

    // Encrypt the plaintext using CFB mode
    encrypt_cfb_des(plaintext, key, iv, ciphertext_cfb);

    // Print the ciphertexts
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext (ECB): %s\n", ciphertext_ecb);
    printf("Ciphertext (CBC): %s\n", ciphertext_cbc);
    printf("Ciphertext (CFB): %s\n", ciphertext_cfb);

    return 0;
}

