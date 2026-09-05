#ifndef LINKED_LIST_H
#define LINKED_LIST_H


#include <stddef.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct{
    Node *head;
    size_t size;
}LinkedList;

/* Function calls*/

int linked_list_init(LinkedList *list);

int linked_list_push_front(LinkedList *list, int value);

void linked_list_free(LinkedList *list);

int linked_list_push_back(LinkedList *list, int value);

int linked_list_insert(LinkedList *list, size_t index, int value);

int linked_list_pop_front(LinkedList *list, int *value);

int linked_list_pop_back(LinkedList *list, int *value);

int linked_list_remove(LinkedList *list, size_t index, int *value);

int linked_list_get(const LinkedList *list, size_t index, int *value);

int linked_list_set(LinkedList *list, size_t index, int value);

size_t linked_list_size(const LinkedList *list);

#endif