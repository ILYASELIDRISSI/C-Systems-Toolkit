#include <stddef.h>
#include <stdlib.h>
#include "linked_list.h"

int linked_list_init(LinkedList *list){

    if( list == NULL){
        return -1;
    }
    list->head = NULL;
    list->size = 0;
    return 0;
}

int linked_list_push_front(LinkedList *list, int value){

    if(list == NULL){
        return -1;
    }
    
    Node *new_node = malloc(sizeof(*new_node));
    
    if(new_node == NULL){
        return -1;
    }

    new_node->value = value;
    new_node->next = list->head;
    
    list->head = new_node;
    list->size++;
    return 0;
}

int linked_list_push_back(LinkedList *list, int value)
{
    if (list == NULL)
    {
        return -1;
    }

    Node *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
    {
        return -1;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
        list->size++;

        return 0;
    }

    Node *current_node = list->head;

    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }

    current_node->next = new_node;
    list->size++;

    return 0;
}

int linked_list_get(const LinkedList *list, size_t index, int *value)
{
    if (list == NULL || value == NULL || index >= list->size)
    {
        return -1;
    }

    Node *current_node = list->head;

    for (size_t i = 0; i < index; i++)
    {
        current_node = current_node->next;
    }

    *value = current_node->value;

    return 0;
}


int linked_list_set(LinkedList *list, size_t index, int value)
{
    if (list == NULL || index >= list->size)
    {
        return -1;
    }

    Node *current_node = list->head;

    for (size_t i = 0; i < index; i++)
    {
        current_node = current_node->next;
    }

    current_node->value = value;

    return 0;
}

int linked_list_insert(LinkedList *list, size_t index, int value)
{
    if (list == NULL || index > list->size)
    {
        return -1;
    }

    Node *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
    {
        return -1;
    }

    new_node->value = value;

    if (index == 0)
    {
        new_node->next = list->head;
        list->head = new_node;
        list->size++;

        return 0;
    }

    Node *previous_node = list->head;

    for (size_t i = 0; i < index - 1; i++)
    {
        previous_node = previous_node->next;
    }

    new_node->next = previous_node->next;
    previous_node->next = new_node;

    list->size++;

    return 0;
}

int linked_list_pop_front(LinkedList *list, int *value){
    if(list == NULL || value == NULL){
        return -1;
    }
    
    if(list->size == 0){
        return -1;
    }

    Node *deleted_node = list->head;
    Node *new_head = deleted_node->next;
    *value = deleted_node->value;
    
    list->head = new_head;

    free(deleted_node);
    list->size--;

    return 0;
}

int linked_list_pop_back(LinkedList *list, int *value)
{
    if (list == NULL || value == NULL || list->head == NULL)
    {
        return -1;
    }

    if (list->size == 1)
    {
        *value = list->head->value;

        free(list->head);

        list->head = NULL;
        list->size = 0;

        return 0;
    }

    Node *last_node = list->head;
    Node *previous_node = NULL;

    while (last_node->next != NULL)
    {
        previous_node = last_node;
        last_node = last_node->next;
    }

    *value = last_node->value;
    previous_node->next = NULL;
    free(last_node);
    list->size--;

    return 0;
}

int linked_list_remove(LinkedList *list, size_t index, int *value)
{
    if (list == NULL || value == NULL || index >= list->size)
    {
        return -1;
    }

    if (index == 0)
    {
        Node *node_to_delete = list->head;
        *value = node_to_delete->value;
        list->head = node_to_delete->next;
        free(node_to_delete);
        list->size--;

        return 0;
    }

    Node *previous_node = list->head;

    for (size_t i = 0; i < index - 1; i++)
    {
        previous_node = previous_node->next;
    }

    Node *node_to_delete = previous_node->next;
    *value = node_to_delete->value;
    previous_node->next = node_to_delete->next;
    free(node_to_delete);
    list->size--;

    return 0;
}

void linked_list_free(LinkedList *list)
{
    if (list == NULL)
    {
        return;
    }

    Node *current = list->head;

    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0;
}

size_t linked_list_size(const LinkedList *list){

    if(list == NULL){
        return 0;
    }
    return list->size;

}

