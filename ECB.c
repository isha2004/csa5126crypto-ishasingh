#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

// Function to perform ECB mode encryption using DES
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

// Function to perform ECB mode decryption using DES
void decrypt_ecb_des(const char *input, const char *key, char *output) {
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

        // Copy the current block of ciphertext
        memcpy(input_block, input + i * 8, 8);

        // Decrypt the block using DES
        DES_ecb_encrypt((DES_cblock *)input_block, (DES_cblock *)output_block, &ks, DES_DECRYPT);

        // Copy the decrypted block to the output buffer
        memcpy(output + i * 8, output_block, 8);
    }

    // Null-terminate the output string
    output[input_len] = '\0';
}

int main() {
    const char *plaintext = "Hello123";  // Replace with your plaintext
    const char *key = "SecretKey";      // Replace with your DES key (8 bytes)

    int input_len = strlen(plaintext);
    char ciphertext[input_len + 1];
    char decrypted_text[input_len + 1];

    // Encrypt the plaintext using ECB mode
    encrypt_ecb_des(plaintext, key, ciphertext);

    // Print the ciphertext
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext using ECB mode
    decrypt_ecb_des(ciphertext, key, decrypted_text);

    // Print the decrypted plaintext
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}

