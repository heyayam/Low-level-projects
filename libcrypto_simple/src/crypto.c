#include <string.h>
#include "../include/crypto.h"

void xor_encrypt(char *data, const char *key) {
    int len = strlen(data);
    int klen = strlen(key);

    for (int i = 0; i < len; i++) {
        data[i] ^= key[i % klen];
    }
}

void xor_decrypt(char *data, const char *key) {
    xor_encrypt(data, key);
}
