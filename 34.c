#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
}

void encryptDecrypt(const char *plaintext, const EVP_CIPHER *cipher, const unsigned char *key, const unsigned char *iv, int mode) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        handleErrors();
    }

    if (EVP_CipherInit_ex(ctx, cipher, NULL, key, iv, mode) != 1) {
        handleErrors();
    }

    int len;
    int ciphertext_len;
    unsigned char ciphertext[128];  // Adjust the size based on your needs

    if (EVP_CipherUpdate(ctx, ciphertext, &len, (const unsigned char *)plaintext, strlen(plaintext)) != 1) {
        handleErrors();
    }
    ciphertext_len = len;

    if (EVP_CipherFinal_ex(ctx, ciphertext + len, &len) != 1) {
        handleErrors();
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    printf("Ciphertext: ");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
}

int main() {
    // Replace these keys and IVs with your own values
    const unsigned char key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x75, 0x46, 0x20, 0x63, 0xed};
    const unsigned char iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    const char *plaintext = "This is a sample message for encryption and decryption using padding.";

    printf("Plaintext: %s\n\n", plaintext);

    // ECB Mode
    printf("ECB Mode:\n");
    const EVP_CIPHER *cipher_ecb = EVP_des_ecb();
    encryptDecrypt(plaintext, cipher_ecb, key, iv, EVP_ENCRYPT);
    encryptDecrypt(plaintext, cipher_ecb, key, iv, EVP_DECRYPT);

    // CBC Mode
    printf("\nCBC Mode:\n");
    const EVP_CIPHER *cipher_cbc = EVP_des_cbc();
    encryptDecrypt(plaintext, cipher_cbc, key, iv, EVP_ENCRYPT);
    encryptDecrypt(plaintext, cipher_cbc, key, iv, EVP_DECRYPT);

    // CFB Mode
    printf("\nCFB Mode:\n");
    const EVP_CIPHER *cipher_cfb = EVP_des_cfb8();
    encryptDecrypt(plaintext, cipher_cfb, key, iv, EVP_ENCRYPT);
    encryptDecrypt(plaintext, cipher_cfb, key, iv, EVP_DECRYPT);

    return 0;
}

