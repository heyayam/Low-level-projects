#include <stdlib.h>
#include <string.h>
#include "../include/kvstore.h"

typedef struct entry {
    char *key;
    char *value;
    struct entry *next;
} entry_t;

struct kvstore {
    entry_t *head;
};

kvstore_t* kvstore_create() {
    kvstore_t *store = malloc(sizeof(kvstore_t));
    store->head = NULL;
    return store;
}

void kvstore_put(kvstore_t *store, const char *key, const char *value) {
    entry_t *curr = store->head;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            free(curr->value);
            curr->value = strdup(value);
            return;
        }
        curr = curr->next;
    }

    entry_t *e = malloc(sizeof(entry_t));
    e->key = strdup(key);
    e->value = strdup(value);
    e->next = store->head;
    store->head = e;
}

const char* kvstore_get(kvstore_t *store, const char *key) {
    entry_t *curr = store->head;

    while (curr) {
        if (strcmp(curr->key, key) == 0)
            return curr->value;
        curr = curr->next;
    }
    return NULL;
}

void kvstore_delete(kvstore_t *store, const char *key) {
    entry_t *curr = store->head;
    entry_t *prev = NULL;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (prev) prev->next = curr->next;
            else store->head = curr->next;

            free(curr->key);
            free(curr->value);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void kvstore_free(kvstore_t *store) {
    entry_t *curr = store->head;
    while (curr) {
        entry_t *next = curr->next;
        free(curr->key);
        free(curr->value);
        free(curr);
        curr = next;
    }
    free(store);
}
