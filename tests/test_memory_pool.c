#include <assert.h>
#include <stdio.h>

#include "memory_pool.h"

int main(void)
{
    MemoryPool pool;

    /* Test initialization */
    assert(memory_pool_init(&pool, 32, 4) == 0);

    assert(pool.buffer != NULL);
    assert(pool.free_list != NULL);
    assert(pool.block_size == 32);
    assert(pool.capacity == 4);
    assert(pool.available == 4);

    assert(memory_pool_available(&pool) == 4);

    /* Test allocations */
    void *p1 = memory_pool_alloc(&pool);
    void *p2 = memory_pool_alloc(&pool);
    void *p3 = memory_pool_alloc(&pool);
    void *p4 = memory_pool_alloc(&pool);

    assert(p1 != NULL);
    assert(p2 != NULL);
    assert(p3 != NULL);
    assert(p4 != NULL);

    assert(p1 != p2);
    assert(p1 != p3);
    assert(p1 != p4);
    assert(p2 != p3);
    assert(p2 != p4);
    assert(p3 != p4);

    assert(memory_pool_available(&pool) == 0);

    /* Pool is exhausted */
    assert(memory_pool_alloc(&pool) == NULL);

    /* Free one block */
    assert(memory_pool_free(&pool, p2) == 0);
    assert(memory_pool_available(&pool) == 1);

    /*
     * Freed blocks are pushed to the head of the free list,
     * so the next allocation should return p2 again.
     */
    void *p5 = memory_pool_alloc(&pool);

    assert(p5 != NULL);
    assert(p5 == p2);
    assert(memory_pool_available(&pool) == 0);

    /* Free several blocks */
    assert(memory_pool_free(&pool, p1) == 0);
    assert(memory_pool_free(&pool, p3) == 0);
    assert(memory_pool_free(&pool, p4) == 0);
    assert(memory_pool_free(&pool, p5) == 0);

    assert(memory_pool_available(&pool) == 4);

    /* Pool is already completely free */
    assert(memory_pool_free(&pool, p1) == -1);

    /* NULL pointer cannot be freed */
    assert(memory_pool_free(&pool, NULL) == -1);

    /* Pointer outside the pool */
    int outside_value = 123;
    assert(memory_pool_free(&pool, &outside_value) == -1);

    /*
     * Test pointer inside the pool but not at the beginning
     * of a valid block.
     */
    void *block = memory_pool_alloc(&pool);

    assert(block != NULL);
    assert(memory_pool_available(&pool) == 3);

    unsigned char *invalid_block =
        (unsigned char *)block + 1;

    assert(memory_pool_free(&pool, invalid_block) == -1);

    /* Valid free still works */
    assert(memory_pool_free(&pool, block) == 0);
    assert(memory_pool_available(&pool) == 4);

    /* NULL pool checks */
    assert(memory_pool_alloc(NULL) == NULL);
    assert(memory_pool_free(NULL, p1) == -1);
    assert(memory_pool_available(NULL) == 0);

    /* Destroy */
    memory_pool_destroy(&pool);

    assert(pool.buffer == NULL);
    assert(pool.free_list == NULL);
    assert(pool.block_size == 0);
    assert(pool.capacity == 0);
    assert(pool.available == 0);

    /* Destroying again should be safe */
    memory_pool_destroy(&pool);

    printf("All memory pool tests passed.\n");

    return 0;
}