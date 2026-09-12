#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stddef.h>

typedef struct MemoryBlock
{
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct
{
    unsigned char *buffer;
    MemoryBlock *free_list;

    size_t block_size;
    size_t capacity;
    size_t available;
} MemoryPool;

int memory_pool_init(MemoryPool *pool, size_t block_size, size_t capacity);

void *memory_pool_alloc(MemoryPool *pool);

int memory_pool_free(MemoryPool *pool, void *ptr);

size_t memory_pool_available(const MemoryPool *pool);

void memory_pool_destroy(MemoryPool *pool);


#endif