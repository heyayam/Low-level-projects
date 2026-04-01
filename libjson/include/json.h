#ifndef JSON_H
#define JSON_H

typedef enum {
    JSON_STRING,
    JSON_NUMBER
} json_type;

typedef struct json {
    char *key;
    json_type type;
    char *string_value;
    int number_value;
    struct json *next;
} json_t;

json_t* json_parse(const char *text);
void json_print(json_t *json);
void json_free(json_t *json);

#endif
