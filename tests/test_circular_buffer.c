#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

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
    CircularBuffer buffer;

    if (circular_buffer_init(&buffer, 3) != 0)
        return TEST_FAIL;

    if (buffer.data == NULL)
        return TEST_FAIL;

    if (buffer.capacity != 3)
        return TEST_FAIL;

    if (buffer.size != 0)
        return TEST_FAIL;

    if (buffer.head != 0 || buffer.tail != 0)
        return TEST_FAIL;

    circular_buffer_free(&buffer);

    return TEST_PASS;
}

static int test_write_read(void)
{
    CircularBuffer buffer;
    int value;

    if (circular_buffer_init(&buffer, 3) != 0)
        return TEST_FAIL;

    circular_buffer_write(&buffer, 10);
    circular_buffer_write(&buffer, 20);
    circular_buffer_write(&buffer, 30);

    if (circular_buffer_size(&buffer) != 3)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) != 0 || value != 10)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) != 0 || value != 30)
        return TEST_FAIL;

    circular_buffer_free(&buffer);

    return TEST_PASS;
}

static int test_overwrite_oldest(void)
{
    CircularBuffer buffer;
    int value;

    if (circular_buffer_init(&buffer, 3) != 0)
        return TEST_FAIL;

    circular_buffer_write(&buffer, 10);
    circular_buffer_write(&buffer, 20);
    circular_buffer_write(&buffer, 30);

    if (circular_buffer_is_full(&buffer) != 1)
        return TEST_FAIL;

    circular_buffer_write(&buffer, 40);

    if (circular_buffer_size(&buffer) != 3)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) != 0 || value != 30)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) != 0 || value != 40)
        return TEST_FAIL;

    circular_buffer_free(&buffer);

    return TEST_PASS;
}

static int test_wrap_around(void)
{
    CircularBuffer buffer;
    int value;

    if (circular_buffer_init(&buffer, 3) != 0)
        return TEST_FAIL;

    circular_buffer_write(&buffer, 10);
    circular_buffer_write(&buffer, 20);

    if (circular_buffer_read(&buffer, &value) != 0 || value != 10)
        return TEST_FAIL;

    circular_buffer_write(&buffer, 30);
    circular_buffer_write(&buffer, 40);

    if (circular_buffer_read(&buffer, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) != 0 || value != 30)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) != 0 || value != 40)
        return TEST_FAIL;

    circular_buffer_free(&buffer);

    return TEST_PASS;
}

static int test_peek(void)
{
    CircularBuffer buffer;
    int value;

    if (circular_buffer_init(&buffer, 3) != 0)
        return TEST_FAIL;

    circular_buffer_write(&buffer, 100);
    circular_buffer_write(&buffer, 200);

    if (circular_buffer_peek(&buffer, &value) != 0)
        return TEST_FAIL;

    if (value != 100)
        return TEST_FAIL;

    if (circular_buffer_size(&buffer) != 2)
        return TEST_FAIL;

    circular_buffer_free(&buffer);

    return TEST_PASS;
}

static int test_empty_operations(void)
{
    CircularBuffer buffer;
    int value;

    if (circular_buffer_init(&buffer, 3) != 0)
        return TEST_FAIL;

    if (circular_buffer_read(&buffer, &value) == 0)
        return TEST_FAIL;

    if (circular_buffer_peek(&buffer, &value) == 0)
        return TEST_FAIL;

    if (circular_buffer_is_empty(&buffer) != 1)
        return TEST_FAIL;

    circular_buffer_free(&buffer);

    return TEST_PASS;
}

static int test_null_arguments(void)
{
    CircularBuffer buffer;
    int value;

    if (circular_buffer_init(NULL, 3) == 0)
        return TEST_FAIL;

    if (circular_buffer_write(NULL, 10) == 0)
        return TEST_FAIL;

    if (circular_buffer_read(NULL, &value) == 0)
        return TEST_FAIL;

    if (circular_buffer_peek(NULL, &value) == 0)
        return TEST_FAIL;

    if (circular_buffer_is_empty(NULL) != -1)
        return TEST_FAIL;

    if (circular_buffer_is_full(NULL) != -1)
        return TEST_FAIL;

    if (circular_buffer_size(NULL) != 0)
        return TEST_FAIL;

    circular_buffer_free(NULL);

    if (circular_buffer_init(&buffer, 3) != 0)
        return TEST_FAIL;

    circular_buffer_write(&buffer, 10);

    if (circular_buffer_read(&buffer, NULL) == 0)
        return TEST_FAIL;

    if (circular_buffer_peek(&buffer, NULL) == 0)
        return TEST_FAIL;

    circular_buffer_free(&buffer);

    return TEST_PASS;
}

static int test_free(void)
{
    CircularBuffer buffer;

    if (circular_buffer_init(&buffer, 3) != 0)
        return TEST_FAIL;

    circular_buffer_write(&buffer, 10);

    circular_buffer_free(&buffer);

    if (buffer.data != NULL)
        return TEST_FAIL;

    if (buffer.capacity != 0 ||
        buffer.size != 0 ||
        buffer.head != 0 ||
        buffer.tail != 0)
        return TEST_FAIL;

    return TEST_PASS;
}

int main(void)
{
    printf("=================================\n");
    printf(" Circular Buffer Test Suite\n");
    printf("=================================\n\n");

    run_test("Initialization", test_init);
    run_test("Write/read", test_write_read);
    run_test("Overwrite oldest", test_overwrite_oldest);
    run_test("Wrap around", test_wrap_around);
    run_test("Peek", test_peek);
    run_test("Empty operations", test_empty_operations);
    run_test("NULL arguments", test_null_arguments);
    run_test("Free", test_free);

    printf("\n=================================\n");
    printf("All circular-buffer tests passed!\n");
    printf("=================================\n");

    return EXIT_SUCCESS;
}