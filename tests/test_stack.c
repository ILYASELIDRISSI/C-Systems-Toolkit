#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

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
    Stack stack;

    if (stack_init(&stack, 4) != 0)
        return TEST_FAIL;

    if (stack_size(&stack) != 0)
        return TEST_FAIL;

    if (stack_is_empty(&stack) != 1)
        return TEST_FAIL;

    stack_free(&stack);

    return TEST_PASS;
}

static int test_push(void)
{
    Stack stack;

    if (stack_init(&stack, 2) != 0)
        return TEST_FAIL;

    if (stack_push(&stack, 10) != 0)
        return TEST_FAIL;

    if (stack_push(&stack, 20) != 0)
        return TEST_FAIL;

    if (stack_push(&stack, 30) != 0)
        return TEST_FAIL;

    if (stack_size(&stack) != 3)
        return TEST_FAIL;

    if (stack_is_empty(&stack) != 0)
        return TEST_FAIL;

    stack_free(&stack);

    return TEST_PASS;
}

static int test_peek(void)
{
    Stack stack;
    int value;

    if (stack_init(&stack, 4) != 0)
        return TEST_FAIL;

    stack_push(&stack, 10);
    stack_push(&stack, 20);
    stack_push(&stack, 30);

    if (stack_peek(&stack, &value) != 0)
        return TEST_FAIL;

    if (value != 30)
        return TEST_FAIL;

    /* Peek must not remove the value. */
    if (stack_size(&stack) != 3)
        return TEST_FAIL;

    stack_free(&stack);

    return TEST_PASS;
}

static int test_pop_lifo(void)
{
    Stack stack;
    int value;

    if (stack_init(&stack, 4) != 0)
        return TEST_FAIL;

    stack_push(&stack, 10);
    stack_push(&stack, 20);
    stack_push(&stack, 30);

    if (stack_pop(&stack, &value) != 0 || value != 30)
        return TEST_FAIL;

    if (stack_pop(&stack, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (stack_pop(&stack, &value) != 0 || value != 10)
        return TEST_FAIL;

    if (stack_size(&stack) != 0)
        return TEST_FAIL;

    if (stack_is_empty(&stack) != 1)
        return TEST_FAIL;

    stack_free(&stack);

    return TEST_PASS;
}

static int test_empty_operations(void)
{
    Stack stack;
    int value;

    if (stack_init(&stack, 4) != 0)
        return TEST_FAIL;

    if (stack_pop(&stack, &value) == 0)
        return TEST_FAIL;

    if (stack_peek(&stack, &value) == 0)
        return TEST_FAIL;

    stack_free(&stack);

    return TEST_PASS;
}

static int test_resize(void)
{
    Stack stack;
    int value;

    if (stack_init(&stack, 2) != 0)
        return TEST_FAIL;

    for (int i = 0; i < 10; i++)
    {
        if (stack_push(&stack, i) != 0)
            return TEST_FAIL;
    }

    if (stack_size(&stack) != 10)
        return TEST_FAIL;

    /*
     * Verify that resizing preserved the values
     * and that LIFO behavior still works.
     */
    for (int i = 9; i >= 0; i--)
    {
        if (stack_pop(&stack, &value) != 0)
            return TEST_FAIL;

        if (value != i)
            return TEST_FAIL;
    }

    stack_free(&stack);

    return TEST_PASS;
}

static int test_null_arguments(void)
{
    Stack stack;
    int value;

    if (stack_init(NULL, 4) == 0)
        return TEST_FAIL;

    if (stack_push(NULL, 10) == 0)
        return TEST_FAIL;

    if (stack_pop(NULL, &value) == 0)
        return TEST_FAIL;

    if (stack_peek(NULL, &value) == 0)
        return TEST_FAIL;

    if (stack_size(NULL) != 0)
        return TEST_FAIL;

    if (stack_is_empty(NULL) != -1)
        return TEST_FAIL;

    stack_free(NULL);

    if (stack_init(&stack, 4) != 0)
        return TEST_FAIL;

    stack_push(&stack, 10);

    if (stack_pop(&stack, NULL) == 0)
        return TEST_FAIL;

    if (stack_peek(&stack, NULL) == 0)
        return TEST_FAIL;

    stack_free(&stack);

    return TEST_PASS;
}

static int test_free(void)
{
    Stack stack;

    if (stack_init(&stack, 4) != 0)
        return TEST_FAIL;

    stack_push(&stack, 10);
    stack_push(&stack, 20);

    stack_free(&stack);

    if (stack.data.data != NULL)
        return TEST_FAIL;

    if (stack.data.size != 0)
        return TEST_FAIL;

    if (stack.data.capacity != 0)
        return TEST_FAIL;

    return TEST_PASS;
}

int main(void)
{
    printf("=================================\n");
    printf(" Stack Test Suite\n");
    printf("=================================\n\n");

    run_test("Initialization", test_init);
    run_test("Push", test_push);
    run_test("Peek", test_peek);
    run_test("LIFO pop", test_pop_lifo);
    run_test("Empty operations", test_empty_operations);
    run_test("Automatic resize", test_resize);
    run_test("NULL arguments", test_null_arguments);
    run_test("Free", test_free);

    printf("\n=================================\n");
    printf("All stack tests passed!\n");
    printf("=================================\n");

    return EXIT_SUCCESS;
}