#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/config.h"

typedef struct entry {
    char *key;
    char *value;
    struct entry *next;
} entry_t;

struct config {
    entry_t *head;
};

static char* trim(char *str) {
    while (*str == ' ' || *str == '\t') str++;
    return str;
}

config_t* config_load(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    config_t *cfg = malloc(sizeof(config_t));
    cfg->head = NULL;

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#') continue;

        char *eq = strchr(line, '=');
        if (!eq) continue;

        *eq = '\0';
        char *key = trim(line);
        char *value = trim(eq + 1);

        value[strcspn(value, "\n")] = '\0';

        entry_t *e = malloc(sizeof(entry_t));
        e->key = strdup(key);
        e->value = strdup(value);
        e->next = cfg->head;
        cfg->head = e;
    }

    fclose(file);
    return cfg;
}

const char* config_get(config_t *cfg, const char *key) {
    entry_t *curr = cfg->head;
    while (curr) {
        if (strcmp(curr->key, key) == 0)
            return curr->value;
        curr = curr->next;
    }
    return NULL;
}

void config_free(config_t *cfg) {
    entry_t *curr = cfg->head;
    while (curr) {
        entry_t *next = curr->next;
        free(curr->key);
        free(curr->value);
        free(curr);
        curr = next;
    }
    free(cfg);
}
