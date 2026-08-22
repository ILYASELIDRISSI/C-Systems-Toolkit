#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

#define TEST_PASS 0
#define TEST_FAIL 1

static void run_test(const char *name, int (*test_function)(void))
{
    if (test_function() == TEST_PASS)
    {
        printf("[PASS] %s\n", name);
    }
    else
    {
        printf("[FAIL] %s\n", name);
        exit(EXIT_FAILURE);
    }
}

static int test_init(void)
{
    HashTable table;

    if (hash_table_init(&table, 8) != 0)
        return TEST_FAIL;

    if (table.buckets == NULL)
        return TEST_FAIL;

    if (table.capacity != 8)
        return TEST_FAIL;

    if (table.size != 0)
        return TEST_FAIL;

    for (size_t i = 0; i < table.capacity; i++)
    {
        if (table.buckets[i] != NULL)
            return TEST_FAIL;
    }

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_set_get(void)
{
    HashTable table;
    int value;

    if (hash_table_init(&table, 8) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, "speed", 120) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, "gear", 4) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, "temperature", 90) != 0)
        return TEST_FAIL;

    if (hash_table_size(&table) != 3)
        return TEST_FAIL;

    if (hash_table_get(&table, "speed", &value) != 0 || value != 120)
        return TEST_FAIL;

    if (hash_table_get(&table, "gear", &value) != 0 || value != 4)
        return TEST_FAIL;

    if (hash_table_get(&table, "temperature", &value) != 0 || value != 90)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_update_existing_key(void)
{
    HashTable table;
    int value;

    if (hash_table_init(&table, 8) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, "speed", 100) != 0)
        return TEST_FAIL;

    if (hash_table_size(&table) != 1)
        return TEST_FAIL;

    if (hash_table_set(&table, "speed", 150) != 0)
        return TEST_FAIL;

    if (hash_table_size(&table) != 1)
        return TEST_FAIL;

    if (hash_table_get(&table, "speed", &value) != 0)
        return TEST_FAIL;

    if (value != 150)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_contains(void)
{
    HashTable table;

    if (hash_table_init(&table, 8) != 0)
        return TEST_FAIL;

    hash_table_set(&table, "speed", 120);

    if (hash_table_contains(&table, "speed") != 1)
        return TEST_FAIL;

    if (hash_table_contains(&table, "missing") != 0)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_missing_key(void)
{
    HashTable table;
    int value;

    if (hash_table_init(&table, 8) != 0)
        return TEST_FAIL;

    hash_table_set(&table, "speed", 120);

    if (hash_table_get(&table, "missing", &value) == 0)
        return TEST_FAIL;

    if (hash_table_remove(&table, "missing", &value) == 0)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_remove(void)
{
    HashTable table;
    int value;

    if (hash_table_init(&table, 8) != 0)
        return TEST_FAIL;

    hash_table_set(&table, "speed", 120);
    hash_table_set(&table, "gear", 4);
    hash_table_set(&table, "temperature", 90);

    if (hash_table_remove(&table, "gear", &value) != 0)
        return TEST_FAIL;

    if (value != 4)
        return TEST_FAIL;

    if (hash_table_size(&table) != 2)
        return TEST_FAIL;

    if (hash_table_contains(&table, "gear") != 0)
        return TEST_FAIL;

    if (hash_table_get(&table, "speed", &value) != 0 || value != 120)
        return TEST_FAIL;

    if (hash_table_get(&table, "temperature", &value) != 0 || value != 90)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_collision_chain(void)
{
    HashTable table;
    int value;

    /*
     * Capacity 1 forces every key into the same bucket.
     * This is an easy way to test collision handling.
     */
    if (hash_table_init(&table, 1) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, "one", 1) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, "two", 2) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, "three", 3) != 0)
        return TEST_FAIL;

    if (hash_table_size(&table) != 3)
        return TEST_FAIL;

    if (hash_table_get(&table, "one", &value) != 0 || value != 1)
        return TEST_FAIL;

    if (hash_table_get(&table, "two", &value) != 0 || value != 2)
        return TEST_FAIL;

    if (hash_table_get(&table, "three", &value) != 0 || value != 3)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_collision_remove_head(void)
{
    HashTable table;
    int value;

    if (hash_table_init(&table, 1) != 0)
        return TEST_FAIL;

    hash_table_set(&table, "one", 1);
    hash_table_set(&table, "two", 2);
    hash_table_set(&table, "three", 3);

    /*
     * New nodes are inserted at the front:
     *
     * three -> two -> one
     */
    if (hash_table_remove(&table, "three", &value) != 0)
        return TEST_FAIL;

    if (value != 3)
        return TEST_FAIL;

    if (hash_table_get(&table, "two", &value) != 0 || value != 2)
        return TEST_FAIL;

    if (hash_table_get(&table, "one", &value) != 0 || value != 1)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_collision_remove_middle(void)
{
    HashTable table;
    int value;

    if (hash_table_init(&table, 1) != 0)
        return TEST_FAIL;

    hash_table_set(&table, "one", 1);
    hash_table_set(&table, "two", 2);
    hash_table_set(&table, "three", 3);

    /*
     * three -> two -> one
     *
     * Remove "two".
     */
    if (hash_table_remove(&table, "two", &value) != 0)
        return TEST_FAIL;

    if (value != 2)
        return TEST_FAIL;

    if (hash_table_get(&table, "three", &value) != 0 || value != 3)
        return TEST_FAIL;

    if (hash_table_get(&table, "one", &value) != 0 || value != 1)
        return TEST_FAIL;

    if (hash_table_contains(&table, "two") != 0)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_collision_remove_tail(void)
{
    HashTable table;
    int value;

    if (hash_table_init(&table, 1) != 0)
        return TEST_FAIL;

    hash_table_set(&table, "one", 1);
    hash_table_set(&table, "two", 2);
    hash_table_set(&table, "three", 3);

    /*
     * three -> two -> one
     *
     * Remove "one".
     */
    if (hash_table_remove(&table, "one", &value) != 0)
        return TEST_FAIL;

    if (value != 1)
        return TEST_FAIL;

    if (hash_table_get(&table, "three", &value) != 0 || value != 3)
        return TEST_FAIL;

    if (hash_table_get(&table, "two", &value) != 0 || value != 2)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_key_copy(void)
{
    HashTable table;
    int value;
    char key[] = "speed";

    if (hash_table_init(&table, 8) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, key, 120) != 0)
        return TEST_FAIL;

    /*
     * Modify the caller's original string.
     * The table should still own its own copy of "speed".
     */
    key[0] = 'X';

    if (hash_table_get(&table, "speed", &value) != 0)
        return TEST_FAIL;

    if (value != 120)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_null_arguments(void)
{
    HashTable table;
    int value;

    if (hash_table_init(NULL, 8) == 0)
        return TEST_FAIL;

    if (hash_table_set(NULL, "key", 1) == 0)
        return TEST_FAIL;

    if (hash_table_get(NULL, "key", &value) == 0)
        return TEST_FAIL;

    if (hash_table_contains(NULL, "key") != -1)
        return TEST_FAIL;

    if (hash_table_remove(NULL, "key", &value) == 0)
        return TEST_FAIL;

    if (hash_table_size(NULL) != 0)
        return TEST_FAIL;

    hash_table_free(NULL);

    if (hash_table_init(&table, 8) != 0)
        return TEST_FAIL;

    if (hash_table_set(&table, NULL, 1) == 0)
        return TEST_FAIL;

    if (hash_table_get(&table, NULL, &value) == 0)
        return TEST_FAIL;

    if (hash_table_get(&table, "key", NULL) == 0)
        return TEST_FAIL;

    if (hash_table_contains(&table, NULL) != -1)
        return TEST_FAIL;

    if (hash_table_remove(&table, NULL, &value) == 0)
        return TEST_FAIL;

    if (hash_table_remove(&table, "key", NULL) == 0)
        return TEST_FAIL;

    hash_table_free(&table);

    return TEST_PASS;
}

static int test_free(void)
{
    HashTable table;

    if (hash_table_init(&table, 4) != 0)
        return TEST_FAIL;

    hash_table_set(&table, "one", 1);
    hash_table_set(&table, "two", 2);
    hash_table_set(&table, "three", 3);

    hash_table_free(&table);

    if (table.buckets != NULL)
        return TEST_FAIL;

    if (table.capacity != 0)
        return TEST_FAIL;

    if (table.size != 0)
        return TEST_FAIL;

    return TEST_PASS;
}

int main(void)
{
    printf("=================================\n");
    printf(" Hash Table Test Suite\n");
    printf("=================================\n\n");

    run_test("Initialization", test_init);
    run_test("Set/get", test_set_get);
    run_test("Update existing key", test_update_existing_key);
    run_test("Contains", test_contains);
    run_test("Missing key", test_missing_key);
    run_test("Remove", test_remove);

    run_test("Collision chain", test_collision_chain);
    run_test("Collision remove head", test_collision_remove_head);
    run_test("Collision remove middle", test_collision_remove_middle);
    run_test("Collision remove tail", test_collision_remove_tail);

    run_test("Key copy", test_key_copy);
    run_test("NULL arguments", test_null_arguments);
    run_test("Free", test_free);

    printf("\n=================================\n");
    printf("All hash-table tests passed!\n");
    printf("=================================\n");

    return EXIT_SUCCESS;
}