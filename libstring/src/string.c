#include <stdlib.h>
#include <string.h>
#include "../include/string.h"

#define INITIAL_CAP 16

static void ensure_capacity(String *s, size_t needed) {
    if (s->capacity >= needed) return;

    while (s->capacity < needed)
        s->capacity *= 2;

    s->data = realloc(s->data, s->capacity);
}

String* string_create() {
    String *s = malloc(sizeof(String));
    s->length = 0;
    s->capacity = INITIAL_CAP;
    s->data = malloc(s->capacity);
    s->data[0] = '\0';
    return s;
}

void string_append(String *s, const char *text) {
    size_t len = strlen(text);
    ensure_capacity(s, s->length + len + 1);

    memcpy(s->data + s->length, text, len);
    s->length += len;
    s->data[s->length] = '\0';
}

void string_append_char(String *s, char c) {
    ensure_capacity(s, s->length + 2);

    s->data[s->length++] = c;
    s->data[s->length] = '\0';
}

char* string_cstr(String *s) {
    return s->data;
}

void string_free(String *s) {
    free(s->data);
    free(s);
}
