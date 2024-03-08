#include <stdio.h>
#include <string.h>

char decryptChar(char c, const char *decryptionKey) {
    if (c >= 'A' && c <= 'Z') {
        return decryptionKey[c - 'A'];
    } else {
        return c;
    }
}

void decryptMessage(const char *ciphertext, const char *decryptionKey) {
    int length = strlen(ciphertext);

    printf("Decrypted Message:\n");
    int i;

    for ( i = 0; i < length; i++) {
        char decryptedChar = decryptChar(ciphertext[i], decryptionKey);
        printf("%c", decryptedChar);
    }

    printf("\n");
}

int main() {
    const char *ciphertext = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 "
                             "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* "
                             ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 "
                             "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";

    // Hints
    const char *decryptionKey = "ETHEIRANSOFQUWL";
    
    decryptMessage(ciphertext, decryptionKey);

    return 0;
}


