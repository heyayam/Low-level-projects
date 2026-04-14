#include <stdio.h>
#include "../include/uuid.h"

int main() {
    char uuid[37];
    uuid_generate(uuid);
    printf("UUID: %s\n", uuid);
    return 0;
}
