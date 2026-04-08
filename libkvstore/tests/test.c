#include <stdio.h>
#include "../include/kvstore.h"

int main() {
    kvstore_t *store = kvstore_create();

    kvstore_put(store, "name", "Alice");
    kvstore_put(store, "age", "25");

    printf("name: %s\n", kvstore_get(store, "name"));

    kvstore_delete(store, "age");
    printf("age: %s\n", kvstore_get(store, "age"));

    kvstore_free(store);
    return 0;
}
