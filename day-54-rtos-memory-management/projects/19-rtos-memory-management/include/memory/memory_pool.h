#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H
#include <stdbool.h>
#include <stdint.h>
#define POOL_BLOCK_SIZE 32
#define POOL_BLOCK_COUNT 8
typedef struct {
    uint8_t storage[POOL_BLOCK_COUNT][POOL_BLOCK_SIZE];
    bool used[POOL_BLOCK_COUNT];
    uint32_t used_count;
} memory_pool_t;
void pool_init(memory_pool_t*);
void* pool_alloc(memory_pool_t*);
bool pool_free(memory_pool_t*, void*);
uint32_t pool_used(const memory_pool_t*);
uint32_t pool_free_count(const memory_pool_t*);
#endif
