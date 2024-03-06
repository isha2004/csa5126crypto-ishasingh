#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/err.h>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
}

void dsaSignAndVerify() {
    DSA *dsa = DSA_generate_parameters(2048, NULL, 0, NULL, NULL, NULL, NULL);
    if (!dsa) {
        handleErrors();
    }

    if (!DSA_generate_key(dsa)) {
        handleErrors();
    }

    // Message to sign
    const char *message = "Hello, this is a message to sign.";

    // DSA signature
    unsigned char dsa_signature[DSA_size(dsa)];
    unsigned int dsa_signature_length;

    // Sign the message
    if (DSA_sign(0, (const unsigned char *)message, strlen(message), dsa_signature, &dsa_signature_length, dsa) != 1) {
        handleErrors();
    }

    printf("DSA Signature: ");
    for (unsigned int i = 0; i < dsa_signature_length; i++) {
        printf("%02x", dsa_signature[i]);
    }
    printf("\n");

    // Verify the signature
    if (DSA_verify(0, (const unsigned char *)message, strlen(message), dsa_signature, dsa_signature_length, dsa) != 1) {
        printf("DSA Signature Verification Failed!\n");
    } else {
        printf("DSA Signature Verified Successfully.\n");
    }

    DSA_free(dsa);
}

void rsaSignAndVerify() {
    // RSA key generation
    RSA *rsa_key = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    if (!rsa_key) {
        handleErrors();
    }

    // Message to sign
    const char *message = "Hello, this is a message to sign.";

    // RSA signature
    unsigned char rsa_signature[2048];
    unsigned int rsa_signature_length;

    // Sign the message
    if (RSA_sign(NID_sha256, (const unsigned char *)message, strlen(message), rsa_signature, &rsa_signature_length, rsa_key) != 1) {
        handleErrors();
    }

    printf("RSA Signature: ");
    for (unsigned int i = 0; i < rsa_signature_length; i++) {
        printf("%02x", rsa_signature[i]);
    }
    printf("\n");

    // Verify the signature
    if (RSA_verify(NID_sha256, (const unsigned char *)message, strlen(message), rsa_signature, rsa_signature_length, rsa_key) != 1) {
        printf("RSA Signature Verification Failed!\n");
    } else {
        printf("RSA Signature Verified Successfully.\n");
    }

    RSA_free(rsa_key);
}

int main() {
    printf("DSA Sign and Verify:\n");
    dsaSignAndVerify();

    printf("\nRSA Sign and Verify:\n");
    rsaSignAndVerify();

    return 0;
}

