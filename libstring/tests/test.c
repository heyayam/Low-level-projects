#include <stdio.h>
#include "../include/string.h"

int main() {
    String *s = string_create();

    string_append(s, "Hello");
    string_append(s, " ");
    string_append(s, "World");
    string_append_char(s, '!');

    printf("%s\n", string_cstr(s));

    string_free(s);
    return 0;
}
