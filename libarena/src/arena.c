#include <stdlib.h>
#include "../include/arena.h"

Arena* arena_create(size_t size) {
    Arena *arena = malloc(sizeof(Arena));
    arena->memory = malloc(size);
    arena->size = size;
    arena->offset = 0;
    return arena;
}

void* arena_alloc(Arena *arena, size_t size) {
    if (arena->offset + size > arena->size)
        return NULL;

    void *ptr = arena->memory + arena->offset;
    arena->offset += size;
    return ptr;
}

void arena_reset(Arena *arena) {
    arena->offset = 0;
}

void arena_destroy(Arena *arena) {
    free(arena->memory);
    free(arena);
}
