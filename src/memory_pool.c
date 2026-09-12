#include <stdlib.h>
#include "memory_pool.h"

int memory_pool_init(MemoryPool *pool, size_t block_size, size_t capacity)
{
    if (pool == NULL ||
        capacity == 0 ||
        block_size < sizeof(MemoryBlock) ||
        block_size % _Alignof(MemoryBlock) != 0)
    {
        return -1;
    }
    // size_t overflow check
    if (block_size > SIZE_MAX / capacity)
        return -1;

    pool->buffer = malloc(block_size * capacity);

    if (pool->buffer == NULL)
        return -1;

    pool->available = capacity;
    pool->block_size = block_size;
    pool->capacity = capacity;

    MemoryBlock *current = (MemoryBlock *)pool->buffer;

    for (size_t i = 0; i < capacity; i++)
    {
        if (i == capacity - 1)
        {
            current->next = NULL;
        }
        else
        {
            current->next =
                (MemoryBlock *)(pool->buffer +
                ((i + 1) * block_size));

            current = current->next;
        }
    }

    pool->free_list = (MemoryBlock *)pool->buffer;

    return 0;
}

void *memory_pool_alloc(MemoryPool *pool){
    if(pool == NULL || pool->free_list == NULL){
        return NULL;
    }
    MemoryBlock *Block = pool->free_list;
    pool->free_list = Block->next;
    pool->available --;
    return Block;

}

int memory_pool_free(MemoryPool *pool, void *ptr)
{
    if (pool == NULL || ptr == NULL)
    {
        return -1;
    }

    unsigned char *block_ptr = (unsigned char *)ptr;
    unsigned char *start = pool->buffer;
    unsigned char *end =
        pool->buffer + (pool->block_size * pool->capacity);

    if (block_ptr < start || block_ptr >= end)
    {
        return -1;
    }

    size_t offset = (size_t)(block_ptr - start);

    if (offset % pool->block_size != 0)
    {
        return -1;
    }

    if (pool->available >= pool->capacity)
    {
        return -1;
    }

    MemoryBlock *block = (MemoryBlock *)ptr;

    block->next = pool->free_list;
    pool->free_list = block;

    pool->available++;

    return 0;
}

size_t memory_pool_available(const MemoryPool *pool){
    if(pool == NULL){
        return 0;
    }

    return pool->available;

}

void memory_pool_destroy(MemoryPool *pool){
    if(pool == NULL){
        return;
    }
    free(pool->buffer);
    pool->available  = 0;
    pool->block_size = 0;
    pool->capacity   = 0;
    pool->free_list  = NULL;
    pool->buffer     = NULL;
    return;
}
