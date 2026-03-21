#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

typedef struct block {
    size_t size;
    struct block *next;
    int free;
} block_t;

#define BLOCK_SIZE sizeof(block_t)

block_t *free_list = NULL;

block_t *find_free_block(size_t size) {
    block_t *curr = free_list;
    while (curr) {
        if (curr->free && curr->size >= size)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

block_t *request_space(size_t size) {
    block_t *block = mmap(NULL, size + BLOCK_SIZE,
                          PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANON, -1, 0);

    if (block == MAP_FAILED)
        return NULL;

    block->size = size;
    block->next = NULL;
    block->free = 0;

    return block;
}

void *my_malloc(size_t size) {
    if (size <= 0) return NULL;

    block_t *block;

    if (!free_list) {
        block = request_space(size);
        if (!block) return NULL;
        free_list = block;
    } else {
        block = find_free_block(size);
        if (!block) {
            block_t *last = free_list;
            while (last->next) last = last->next;

            block = request_space(size);
            if (!block) return NULL;

            last->next = block;
        } else {
            block->free = 0;
        }
    }

    return (block + 1);
}

void my_free(void *ptr) {
    if (!ptr) return;

    block_t *block = (block_t*)ptr - 1;
    block->free = 1;
}

void *my_realloc(void *ptr, size_t size) {
    if (!ptr) return my_malloc(size);

    block_t *block = (block_t*)ptr - 1;

    if (block->size >= size)
        return ptr;

    void *new_ptr = my_malloc(size);
    if (!new_ptr) return NULL;

    memcpy(new_ptr, ptr, block->size);
    my_free(ptr);

    return new_ptr;
}
