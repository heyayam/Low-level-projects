#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/uuid.h"

void uuid_generate(char *out) {
    const char *hex = "0123456789abcdef";
    srand(time(NULL));

    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            out[i] = '-';
        } else {
            out[i] = hex[rand() % 16];
        }
    }
    out[36] = '\0';
}
