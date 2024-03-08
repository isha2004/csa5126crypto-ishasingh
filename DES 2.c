#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
}

void encryptDecryptDES(const unsigned char *input, unsigned char *output, const DES_cblock *key, int mode) {
    DES_key_schedule schedule;
    DES_set_key(key, &schedule);

    DES_cblock iv;
    DES_random_key(&iv);

    DES_ncbc_encrypt(input, output, 8, &schedule, &iv, mode);
}

int main() {
    DES_cblock key;
    DES_random_key(&key);

    const char *plaintext = "Hello123";
    unsigned char encrypted[8];
    unsigned char decrypted[8];

    // Encrypt
    encryptDecryptDES((const unsigned char *)plaintext, encrypted, &key, DES_ENCRYPT);

    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%02x", encrypted[i]);
    }
    printf("\n");

    // Decrypt
    encryptDecryptDES(encrypted, decrypted, &key, DES_DECRYPT);
    decrypted[8] = '\0';

    printf("Decrypted: %s\n", decrypted);

    return 0;
}

