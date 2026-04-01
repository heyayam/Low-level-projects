#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/json.h"

static void skip_whitespace(const char **p) {
    while (isspace(**p)) (*p)++;
}

static char* parse_string(const char **p) {
    (*p)++;
    const char *start = *p;

    while (**p && **p != '"') (*p)++;

    int len = *p - start;
    char *str = malloc(len + 1);
    strncpy(str, start, len);
    str[len] = '\0';

    (*p)++;
    return str;
}

static int parse_number(const char **p) {
    int num = 0;
    while (isdigit(**p)) {
        num = num * 10 + (**p - '0');
        (*p)++;
    }
    return num;
}

json_t* json_parse(const char *text) {
    const char *p = text;
    skip_whitespace(&p);

    if (*p != '{') return NULL;
    p++;

    json_t *head = NULL;
    json_t *current = NULL;

    while (*p && *p != '}') {
        skip_whitespace(&p);

        char *key = parse_string(&p);
        skip_whitespace(&p);

        if (*p != ':') break;
        p++;

        skip_whitespace(&p);

        json_t *node = malloc(sizeof(json_t));
        node->key = key;
        node->next = NULL;

        if (*p == '"') {
            node->type = JSON_STRING;
            node->string_value = parse_string(&p);
        } else {
            node->type = JSON_NUMBER;
            node->number_value = parse_number(&p);
        }

        if (!head) head = node;
        else current->next = node;

        current = node;

        skip_whitespace(&p);
        if (*p == ',') p++;
    }

    return head;
}

void json_print(json_t *json) {
    while (json) {
        printf("%s: ", json->key);
        if (json->type == JSON_STRING)
            printf("%s\n", json->string_value);
        else
            printf("%d\n", json->number_value);

        json = json->next;
    }
}

void json_free(json_t *json) {
    while (json) {
        json_t *next = json->next;
        free(json->key);
        if (json->type == JSON_STRING)
            free(json->string_value);
        free(json);
        json = next;
    }
}
