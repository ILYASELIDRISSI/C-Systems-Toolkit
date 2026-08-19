#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

#define TEST_PASS 0
#define TEST_FAIL 1


static int test_init(void)
{
    DynamicArray array;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    if (array.data == NULL)
        return TEST_FAIL;

    if (array.size != 0)
        return TEST_FAIL;

    if (array.capacity != 4)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_push(void)
{
    DynamicArray array;

    if (d_array_init(&array, 2) != 0)
        return TEST_FAIL;

    if (d_array_push(&array, 10) != 0)
        return TEST_FAIL;

    if (d_array_push(&array, 20) != 0)
        return TEST_FAIL;

    if (array.size != 2)
        return TEST_FAIL;

    if (array.data[0] != 10)
        return TEST_FAIL;

    if (array.data[1] != 20)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_resize(void)
{
    DynamicArray array;

    if (d_array_init(&array, 2) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);

    /* Array is now full */

    if (d_array_push(&array, 30) != 0)
        return TEST_FAIL;

    if (array.size != 3)
        return TEST_FAIL;

    if (array.capacity != 4)
        return TEST_FAIL;

    if (array.data[0] != 10 ||
        array.data[1] != 20 ||
        array.data[2] != 30)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_pop(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);
    d_array_push(&array, 30);

    if (d_array_pop(&array, &value) != 0)
        return TEST_FAIL;

    if (value != 30)
        return TEST_FAIL;

    if (array.size != 2)
        return TEST_FAIL;

    if (d_array_pop(&array, &value) != 0)
        return TEST_FAIL;

    if (value != 20)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_get(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 100);
    d_array_push(&array, 200);
    d_array_push(&array, 300);

    if (d_array_get(&array, 1, &value) != 0)
        return TEST_FAIL;

    if (value != 200)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_set(void)
{
    DynamicArray array;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);

    if (d_array_set(&array, 1, 99) != 0)
        return TEST_FAIL;

    if (array.data[1] != 99)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_size_and_capacity(void)
{
    DynamicArray array;

    if (d_array_init(&array, 8) != 0)
        return TEST_FAIL;

    if (d_array_size(&array) != 0)
        return TEST_FAIL;

    if (d_array_capacity(&array) != 8)
        return TEST_FAIL;

    d_array_push(&array, 1);
    d_array_push(&array, 2);

    if (d_array_size(&array) != 2)
        return TEST_FAIL;

    if (d_array_capacity(&array) != 8)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_empty_pop(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    if (d_array_pop(&array, &value) == 0)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_invalid_index(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);

    /* Index 1 is outside the current size */

    if (d_array_get(&array, 1, &value) == 0)
        return TEST_FAIL;

    if (d_array_set(&array, 1, 20) == 0)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


static int test_null_arguments(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(NULL, 4) == 0)
        return TEST_FAIL;

    if (d_array_push(NULL, 10) == 0)
        return TEST_FAIL;

    if (d_array_pop(NULL, &value) == 0)
        return TEST_FAIL;

    if (d_array_get(NULL, 0, &value) == 0)
        return TEST_FAIL;

    if (d_array_set(NULL, 0, 10) == 0)
        return TEST_FAIL;

    if (d_array_size(NULL) != 0)
        return TEST_FAIL;

    if (d_array_capacity(NULL) != 0)
        return TEST_FAIL;

    d_array_free(NULL);

    /* NULL output pointer */

    if (d_array_get(&array, 0, NULL) == 0)
        return TEST_FAIL;

    return TEST_PASS;
}

static int test_insert_beginning(void)
{
    DynamicArray array;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 20);
    d_array_push(&array, 30);

    if (d_array_insert(&array, 0, 10) != 0)
        return TEST_FAIL;

    if (array.size != 3)
        return TEST_FAIL;

    if (array.data[0] != 10 ||
        array.data[1] != 20 ||
        array.data[2] != 30)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}

static int test_insert_middle(void)
{
    DynamicArray array;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);
    d_array_push(&array, 40);

    if (d_array_insert(&array, 2, 30) != 0)
        return TEST_FAIL;

    if (array.size != 4)
        return TEST_FAIL;

    if (array.data[0] != 10 ||
        array.data[1] != 20 ||
        array.data[2] != 30 ||
        array.data[3] != 40)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}

static int test_insert_end(void)
{
    DynamicArray array;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);

    if (d_array_insert(&array, array.size, 30) != 0)
        return TEST_FAIL;

    if (array.data[2] != 30)
        return TEST_FAIL;

    if (array.size != 3)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}

static int test_insert_resize(void)
{
    DynamicArray array;

    if (d_array_init(&array, 2) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 30);

    if (d_array_insert(&array, 1, 20) != 0)
        return TEST_FAIL;

    if (array.size != 3)
        return TEST_FAIL;

    if (array.capacity != 4)
        return TEST_FAIL;

    if (array.data[0] != 10 ||
        array.data[1] != 20 ||
        array.data[2] != 30)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}

static int test_remove_beginning(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);
    d_array_push(&array, 30);

    if (d_array_remove(&array, 0, &value) != 0)
        return TEST_FAIL;

    if (value != 10)
        return TEST_FAIL;

    if (array.size != 2)
        return TEST_FAIL;

    if (array.data[0] != 20 ||
        array.data[1] != 30)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}

static int test_remove_middle(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);
    d_array_push(&array, 30);
    d_array_push(&array, 40);

    if (d_array_remove(&array, 1, &value) != 0)
        return TEST_FAIL;

    if (value != 20)
        return TEST_FAIL;

    if (array.size != 3)
        return TEST_FAIL;

    if (array.data[0] != 10 ||
        array.data[1] != 30 ||
        array.data[2] != 40)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}

static int test_remove_last(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);
    d_array_push(&array, 30);

    if (d_array_remove(&array, 2, &value) != 0)
        return TEST_FAIL;

    if (value != 30)
        return TEST_FAIL;

    if (array.size != 2)
        return TEST_FAIL;

    if (array.data[0] != 10 ||
        array.data[1] != 20)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}

static int test_remove_only_element(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 42);

    if (d_array_remove(&array, 0, &value) != 0)
        return TEST_FAIL;

    if (value != 42)
        return TEST_FAIL;

    if (array.size != 0)
        return TEST_FAIL;

    if (array.capacity != 4)
        return TEST_FAIL;

    if (array.data == NULL)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}

static int test_insert_remove_invalid_index(void)
{
    DynamicArray array;
    int value;

    if (d_array_init(&array, 4) != 0)
        return TEST_FAIL;

    d_array_push(&array, 10);
    d_array_push(&array, 20);

    /* Insert: index > size is invalid */
    if (d_array_insert(&array, 3, 30) == 0)
        return TEST_FAIL;

    /* Remove: index == size is invalid */
    if (d_array_remove(&array, 2, &value) == 0)
        return TEST_FAIL;

    /* Remove: clearly out of bounds */
    if (d_array_remove(&array, 100, &value) == 0)
        return TEST_FAIL;

    d_array_free(&array);

    return TEST_PASS;
}


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


int main(void)
{
    printf("=================================\n");
    printf(" Dynamic Array Test Suite\n");
    printf("=================================\n\n");

    run_test("Initialization", test_init);
    run_test("Push", test_push);
    run_test("Automatic resize", test_resize);
    run_test("Pop", test_pop);
    run_test("Get", test_get);
    run_test("Set", test_set);
    run_test("Size and capacity", test_size_and_capacity);
    run_test("Pop from empty array", test_empty_pop);
    run_test("Invalid index", test_invalid_index);
    run_test("NULL arguments", test_null_arguments);
    run_test("Insert beginning", test_insert_beginning);
    run_test("Insert middle", test_insert_middle);
    run_test("Insert end", test_insert_end);
    run_test("Insert with resize", test_insert_resize);

    run_test("Remove beginning", test_remove_beginning);
    run_test("Remove middle", test_remove_middle);
    run_test("Remove last", test_remove_last);
    run_test("Remove only element", test_remove_only_element);
    run_test("Invalid insert/remove index", test_insert_remove_invalid_index);

    printf("\n=================================\n");
    printf("All tests passed!\n");
    printf("=================================\n");

    return EXIT_SUCCESS;
}