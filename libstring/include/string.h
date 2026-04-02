#ifndef STRING_H
#define STRING_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} String;

String* string_create();
void string_append(String *s, const char *text);
void string_append_char(String *s, char c);
char* string_cstr(String *s);
void string_free(String *s);

#endif
