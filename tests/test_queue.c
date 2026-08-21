#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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
    Queue queue;

    if (queue_init(&queue, 4) != 0)
        return TEST_FAIL;

    if (queue.data == NULL)
        return TEST_FAIL;

    if (queue.capacity != 4)
        return TEST_FAIL;

    if (queue.size != 0)
        return TEST_FAIL;

    if (queue.front != 0 || queue.rear != 0)
        return TEST_FAIL;

    queue_free(&queue);

    return TEST_PASS;
}

static int test_enqueue(void)
{
    Queue queue;

    if (queue_init(&queue, 3) != 0)
        return TEST_FAIL;

    if (queue_enqueue(&queue, 10) != 0)
        return TEST_FAIL;

    if (queue_enqueue(&queue, 20) != 0)
        return TEST_FAIL;

    if (queue_enqueue(&queue, 30) != 0)
        return TEST_FAIL;

    if (queue_size(&queue) != 3)
        return TEST_FAIL;

    if (queue_is_full(&queue) != 1)
        return TEST_FAIL;

    if (queue_enqueue(&queue, 40) == 0)
        return TEST_FAIL;

    queue_free(&queue);

    return TEST_PASS;
}

static int test_dequeue_fifo(void)
{
    Queue queue;
    int value;

    if (queue_init(&queue, 4) != 0)
        return TEST_FAIL;

    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);
    queue_enqueue(&queue, 30);

    if (queue_dequeue(&queue, &value) != 0 || value != 10)
        return TEST_FAIL;

    if (queue_dequeue(&queue, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (queue_dequeue(&queue, &value) != 0 || value != 30)
        return TEST_FAIL;

    if (queue_is_empty(&queue) != 1)
        return TEST_FAIL;

    queue_free(&queue);

    return TEST_PASS;
}

static int test_peek(void)
{
    Queue queue;
    int value;

    if (queue_init(&queue, 4) != 0)
        return TEST_FAIL;

    queue_enqueue(&queue, 100);
    queue_enqueue(&queue, 200);

    if (queue_peek(&queue, &value) != 0)
        return TEST_FAIL;

    if (value != 100)
        return TEST_FAIL;

    if (queue_size(&queue) != 2)
        return TEST_FAIL;

    queue_free(&queue);

    return TEST_PASS;
}

static int test_wrap_around(void)
{
    Queue queue;
    int value;

    if (queue_init(&queue, 3) != 0)
        return TEST_FAIL;

    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);
    queue_enqueue(&queue, 30);

    if (queue_dequeue(&queue, &value) != 0 || value != 10)
        return TEST_FAIL;

    if (queue_dequeue(&queue, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (queue_enqueue(&queue, 40) != 0)
        return TEST_FAIL;

    if (queue_enqueue(&queue, 50) != 0)
        return TEST_FAIL;

    if (queue_size(&queue) != 3)
        return TEST_FAIL;

    if (queue_dequeue(&queue, &value) != 0 || value != 30)
        return TEST_FAIL;

    if (queue_dequeue(&queue, &value) != 0 || value != 40)
        return TEST_FAIL;

    if (queue_dequeue(&queue, &value) != 0 || value != 50)
        return TEST_FAIL;

    if (queue_is_empty(&queue) != 1)
        return TEST_FAIL;

    queue_free(&queue);

    return TEST_PASS;
}

static int test_multiple_cycles(void)
{
    Queue queue;
    int value;

    if (queue_init(&queue, 3) != 0)
        return TEST_FAIL;

    for (int cycle = 0; cycle < 10; cycle++)
    {
        if (queue_enqueue(&queue, cycle * 10 + 1) != 0)
            return TEST_FAIL;

        if (queue_enqueue(&queue, cycle * 10 + 2) != 0)
            return TEST_FAIL;

        if (queue_dequeue(&queue, &value) != 0)
            return TEST_FAIL;

        if (value != cycle * 10 + 1)
            return TEST_FAIL;

        if (queue_dequeue(&queue, &value) != 0)
            return TEST_FAIL;

        if (value != cycle * 10 + 2)
            return TEST_FAIL;
    }

    if (queue_is_empty(&queue) != 1)
        return TEST_FAIL;

    queue_free(&queue);

    return TEST_PASS;
}

static int test_empty_operations(void)
{
    Queue queue;
    int value;

    if (queue_init(&queue, 3) != 0)
        return TEST_FAIL;

    if (queue_dequeue(&queue, &value) == 0)
        return TEST_FAIL;

    if (queue_peek(&queue, &value) == 0)
        return TEST_FAIL;

    queue_free(&queue);

    return TEST_PASS;
}

static int test_null_arguments(void)
{
    Queue queue;
    int value;

    if (queue_init(NULL, 3) == 0)
        return TEST_FAIL;

    if (queue_enqueue(NULL, 10) == 0)
        return TEST_FAIL;

    if (queue_dequeue(NULL, &value) == 0)
        return TEST_FAIL;

    if (queue_peek(NULL, &value) == 0)
        return TEST_FAIL;

    if (queue_is_empty(NULL) != -1)
        return TEST_FAIL;

    if (queue_is_full(NULL) != -1)
        return TEST_FAIL;

    if (queue_size(NULL) != 0)
        return TEST_FAIL;

    queue_free(NULL);

    if (queue_init(&queue, 3) != 0)
        return TEST_FAIL;

    queue_enqueue(&queue, 10);

    if (queue_dequeue(&queue, NULL) == 0)
        return TEST_FAIL;

    if (queue_peek(&queue, NULL) == 0)
        return TEST_FAIL;

    queue_free(&queue);

    return TEST_PASS;
}

static int test_free(void)
{
    Queue queue;

    if (queue_init(&queue, 5) != 0)
        return TEST_FAIL;

    queue_enqueue(&queue, 10);
    queue_enqueue(&queue, 20);

    queue_free(&queue);

    if (queue.data != NULL)
        return TEST_FAIL;

    if (queue.capacity != 0)
        return TEST_FAIL;

    if (queue.size != 0)
        return TEST_FAIL;

    if (queue.front != 0 || queue.rear != 0)
        return TEST_FAIL;

    return TEST_PASS;
}

int main(void)
{
    printf("=================================\n");
    printf(" Queue Test Suite\n");
    printf("=================================\n\n");

    run_test("Initialization", test_init);
    run_test("Enqueue", test_enqueue);
    run_test("FIFO dequeue", test_dequeue_fifo);
    run_test("Peek", test_peek);
    run_test("Wrap around", test_wrap_around);
    run_test("Multiple cycles", test_multiple_cycles);
    run_test("Empty operations", test_empty_operations);
    run_test("NULL arguments", test_null_arguments);
    run_test("Free", test_free);

    printf("\n=================================\n");
    printf("All queue tests passed!\n");
    printf("=================================\n");

    return EXIT_SUCCESS;
}