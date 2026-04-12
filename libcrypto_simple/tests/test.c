#include <stdio.h>
#include <string.h>
#include "../include/crypto.h"

int main() {
    char text[100] = "HelloWorld";
    char key[] = "key";

    printf("Original: %s\n", text);

    xor_encrypt(text, key);
    printf("Encrypted: %s\n", text);

    xor_decrypt(text, key);
    printf("Decrypted: %s\n", text);

    return 0;
}
