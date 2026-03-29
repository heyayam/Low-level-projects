#include <stdio.h>
#include "../include/arena.h"

int main() {
    Arena *arena = arena_create(1024);

    int *a = (int*) arena_alloc(arena, sizeof(int));
    int *b = (int*) arena_alloc(arena, sizeof(int));

    *a = 10;
    *b = 20;

    printf("%d %d\n", *a, *b);

    arena_reset(arena);

    arena_destroy(arena);
    return 0;
}
