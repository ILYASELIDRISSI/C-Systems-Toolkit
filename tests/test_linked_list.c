#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

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
    LinkedList list;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    if (list.head != NULL)
        return TEST_FAIL;

    if (list.size != 0)
        return TEST_FAIL;

    return TEST_PASS;
}

static int test_push_front(void)
{
    LinkedList list;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    if (linked_list_push_front(&list, 30) != 0)
        return TEST_FAIL;

    if (linked_list_push_front(&list, 20) != 0)
        return TEST_FAIL;

    if (linked_list_push_front(&list, 10) != 0)
        return TEST_FAIL;

    if (list.size != 3)
        return TEST_FAIL;

    if (list.head == NULL)
        return TEST_FAIL;

    if (list.head->value != 10)
        return TEST_FAIL;

    if (list.head->next == NULL ||
        list.head->next->value != 20)
        return TEST_FAIL;

    if (list.head->next->next == NULL ||
        list.head->next->next->value != 30)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_push_back(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    if (linked_list_push_back(&list, 10) != 0)
        return TEST_FAIL;

    if (linked_list_push_back(&list, 20) != 0)
        return TEST_FAIL;

    if (linked_list_push_back(&list, 30) != 0)
        return TEST_FAIL;

    if (list.size != 3)
        return TEST_FAIL;

    if (linked_list_get(&list, 0, &value) != 0 || value != 10)
        return TEST_FAIL;

    if (linked_list_get(&list, 1, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (linked_list_get(&list, 2, &value) != 0 || value != 30)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_get(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 100);
    linked_list_push_back(&list, 200);
    linked_list_push_back(&list, 300);

    if (linked_list_get(&list, 1, &value) != 0)
        return TEST_FAIL;

    if (value != 200)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_set(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);
    linked_list_push_back(&list, 30);

    if (linked_list_set(&list, 1, 99) != 0)
        return TEST_FAIL;

    if (linked_list_get(&list, 1, &value) != 0)
        return TEST_FAIL;

    if (value != 99)
        return TEST_FAIL;

    if (list.size != 3)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_insert_beginning(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 20);
    linked_list_push_back(&list, 30);

    if (linked_list_insert(&list, 0, 10) != 0)
        return TEST_FAIL;

    if (list.size != 3)
        return TEST_FAIL;

    if (linked_list_get(&list, 0, &value) != 0 || value != 10)
        return TEST_FAIL;

    if (linked_list_get(&list, 1, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (linked_list_get(&list, 2, &value) != 0 || value != 30)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_insert_middle(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 30);

    if (linked_list_insert(&list, 1, 20) != 0)
        return TEST_FAIL;

    if (list.size != 3)
        return TEST_FAIL;

    if (linked_list_get(&list, 0, &value) != 0 || value != 10)
        return TEST_FAIL;

    if (linked_list_get(&list, 1, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (linked_list_get(&list, 2, &value) != 0 || value != 30)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_insert_end(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);

    if (linked_list_insert(&list, list.size, 30) != 0)
        return TEST_FAIL;

    if (list.size != 3)
        return TEST_FAIL;

    if (linked_list_get(&list, 2, &value) != 0 || value != 30)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_pop_front(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);
    linked_list_push_back(&list, 30);

    if (linked_list_pop_front(&list, &value) != 0)
        return TEST_FAIL;

    if (value != 10)
        return TEST_FAIL;

    if (list.size != 2)
        return TEST_FAIL;

    if (linked_list_get(&list, 0, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (linked_list_pop_front(&list, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (linked_list_pop_front(&list, &value) != 0 || value != 30)
        return TEST_FAIL;

    if (list.size != 0)
        return TEST_FAIL;

    if (list.head != NULL)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_pop_back(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);
    linked_list_push_back(&list, 30);

    if (linked_list_pop_back(&list, &value) != 0 || value != 30)
        return TEST_FAIL;

    if (list.size != 2)
        return TEST_FAIL;

    if (linked_list_pop_back(&list, &value) != 0 || value != 20)
        return TEST_FAIL;

    if (linked_list_pop_back(&list, &value) != 0 || value != 10)
        return TEST_FAIL;

    if (list.size != 0)
        return TEST_FAIL;

    if (list.head != NULL)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_remove_beginning(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);
    linked_list_push_back(&list, 30);

    if (linked_list_remove(&list, 0, &value) != 0)
        return TEST_FAIL;

    if (value != 10)
        return TEST_FAIL;

    if (list.size != 2)
        return TEST_FAIL;

    if (linked_list_get(&list, 0, &value) != 0 || value != 20)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_remove_middle(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);
    linked_list_push_back(&list, 30);
    linked_list_push_back(&list, 40);

    if (linked_list_remove(&list, 1, &value) != 0)
        return TEST_FAIL;

    if (value != 20)
        return TEST_FAIL;

    if (list.size != 3)
        return TEST_FAIL;

    if (linked_list_get(&list, 1, &value) != 0 || value != 30)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_remove_last(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);
    linked_list_push_back(&list, 30);

    if (linked_list_remove(&list, 2, &value) != 0)
        return TEST_FAIL;

    if (value != 30)
        return TEST_FAIL;

    if (list.size != 2)
        return TEST_FAIL;

    if (linked_list_get(&list, 1, &value) != 0 || value != 20)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_remove_only_element(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 42);

    if (linked_list_remove(&list, 0, &value) != 0)
        return TEST_FAIL;

    if (value != 42)
        return TEST_FAIL;

    if (list.size != 0)
        return TEST_FAIL;

    if (list.head != NULL)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_size(void)
{
    LinkedList list;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    if (linked_list_size(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);

    if (linked_list_size(&list) != 2)
        return TEST_FAIL;

    linked_list_pop_front(&list, &(int){0});

    if (linked_list_size(&list) != 1)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_free(void)
{
    LinkedList list;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);
    linked_list_push_back(&list, 30);

    linked_list_free(&list);

    if (list.head != NULL)
        return TEST_FAIL;

    if (list.size != 0)
        return TEST_FAIL;

    return TEST_PASS;
}

static int test_invalid_indexes(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);
    linked_list_push_back(&list, 20);

    if (linked_list_get(&list, 2, &value) == 0)
        return TEST_FAIL;

    if (linked_list_set(&list, 2, 99) == 0)
        return TEST_FAIL;

    if (linked_list_remove(&list, 2, &value) == 0)
        return TEST_FAIL;

    if (linked_list_insert(&list, 3, 30) == 0)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_empty_operations(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    if (linked_list_pop_front(&list, &value) == 0)
        return TEST_FAIL;

    if (linked_list_pop_back(&list, &value) == 0)
        return TEST_FAIL;

    if (linked_list_get(&list, 0, &value) == 0)
        return TEST_FAIL;

    if (linked_list_set(&list, 0, 10) == 0)
        return TEST_FAIL;

    if (linked_list_remove(&list, 0, &value) == 0)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

static int test_null_arguments(void)
{
    LinkedList list;
    int value;

    if (linked_list_init(NULL) == 0)
        return TEST_FAIL;

    if (linked_list_push_front(NULL, 10) == 0)
        return TEST_FAIL;

    if (linked_list_push_back(NULL, 10) == 0)
        return TEST_FAIL;

    if (linked_list_get(NULL, 0, &value) == 0)
        return TEST_FAIL;

    if (linked_list_set(NULL, 0, 10) == 0)
        return TEST_FAIL;

    if (linked_list_insert(NULL, 0, 10) == 0)
        return TEST_FAIL;

    if (linked_list_pop_front(NULL, &value) == 0)
        return TEST_FAIL;

    if (linked_list_pop_back(NULL, &value) == 0)
        return TEST_FAIL;

    if (linked_list_remove(NULL, 0, &value) == 0)
        return TEST_FAIL;

    if (linked_list_size(NULL) != 0)
        return TEST_FAIL;

    linked_list_free(NULL);

    if (linked_list_init(&list) != 0)
        return TEST_FAIL;

    linked_list_push_back(&list, 10);

    if (linked_list_get(&list, 0, NULL) == 0)
        return TEST_FAIL;

    if (linked_list_pop_front(&list, NULL) == 0)
        return TEST_FAIL;

    if (linked_list_pop_back(&list, NULL) == 0)
        return TEST_FAIL;

    if (linked_list_remove(&list, 0, NULL) == 0)
        return TEST_FAIL;

    linked_list_free(&list);

    return TEST_PASS;
}

int main(void)
{
    printf("=================================\n");
    printf(" Linked List Test Suite\n");
    printf("=================================\n\n");

    run_test("Initialization", test_init);
    run_test("Push front", test_push_front);
    run_test("Push back", test_push_back);
    run_test("Get", test_get);
    run_test("Set", test_set);

    run_test("Insert beginning", test_insert_beginning);
    run_test("Insert middle", test_insert_middle);
    run_test("Insert end", test_insert_end);

    run_test("Pop front", test_pop_front);
    run_test("Pop back", test_pop_back);

    run_test("Remove beginning", test_remove_beginning);
    run_test("Remove middle", test_remove_middle);
    run_test("Remove last", test_remove_last);
    run_test("Remove only element", test_remove_only_element);

    run_test("Size", test_size);
    run_test("Free", test_free);

    run_test("Invalid indexes", test_invalid_indexes);
    run_test("Empty operations", test_empty_operations);
    run_test("NULL arguments", test_null_arguments);

    printf("\n=================================\n");
    printf("All linked-list tests passed!\n");
    printf("=================================\n");

    return EXIT_SUCCESS;
}