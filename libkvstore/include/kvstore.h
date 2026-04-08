#ifndef KVSTORE_H
#define KVSTORE_H

typedef struct kvstore kvstore_t;

kvstore_t* kvstore_create();
void kvstore_put(kvstore_t *store, const char *key, const char *value);
const char* kvstore_get(kvstore_t *store, const char *key);
void kvstore_delete(kvstore_t *store, const char *key);
void kvstore_free(kvstore_t *store);

#endif
