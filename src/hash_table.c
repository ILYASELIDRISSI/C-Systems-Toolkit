#include <string.h>
#include <stdlib.h>
#include "hash_table.h"


static size_t hash_string(const char *key)
{
    size_t hash = 5381;

    while (*key != '\0')
    {
        hash = ((hash << 5) + hash) + (unsigned char)*key;
        key++;
    }

    return hash;
}

int hash_table_init(HashTable *table, size_t capacity){
    if(table == NULL || capacity == 0){
        return -1;
    }

    table->buckets = malloc(capacity * sizeof(*table->buckets));
    if (table->buckets == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < capacity; i++)
    {
        table->buckets[i] = NULL;
    }
    table->capacity = capacity;
    table->size = 0;
    return 0;
}

int hash_table_set(HashTable *table, const char *key, int value)
{
    if (table == NULL ||
        key == NULL ||
        table->capacity == 0)
    {
        return -1;
    }

    size_t hash = hash_string(key);
    size_t index = hash % table->capacity;

    HashNode *current = table->buckets[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = value;
            return 0;
        }

        current = current->next;
    }

    HashNode *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
    {
        return -1;
    }

    size_t key_length = strlen(key);
    new_node->key = malloc(key_length + 1);

    if (new_node->key == NULL)
    {
        free(new_node);
        return -1;
    }

    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->size++;

    return 0;
}

int hash_table_get(const HashTable *table, const char *key, int *value)
{
    if (table == NULL ||
        key == NULL ||
        value == NULL ||
        table->capacity == 0)
    {
        return -1;
    }

    size_t hash = hash_string(key);
    size_t index = hash % table->capacity;
    const HashNode *current = table->buckets[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            *value = current->value;
            return 0;
        }

        current = current->next;
    }
    return -1;
}

int hash_table_contains(const HashTable *table, const char *key){

    if(table == NULL || key == NULL || table->capacity == 0){
        return -1;
    }

    size_t hash = hash_string(key);
    size_t index = hash % table->capacity;
    
    const HashNode *current = table->buckets[index];
    while(current !=NULL){
        if(strcmp(current->key,key) == 0){
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int hash_table_remove(HashTable *table, const char *key, int *value)
{
    if (table == NULL ||
        key == NULL ||
        value == NULL ||
        table->capacity == 0)
    {
        return -1;
    }

    size_t hash = hash_string(key);
    size_t index = hash % table->capacity;

    HashNode *current = table->buckets[index];
    HashNode *previous = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            *value = current->value;

            if (previous == NULL)
            {
                /* Removing first node in bucket */
                table->buckets[index] = current->next;
            }
            else
            {
                /* Removing middle or last node */
                previous->next = current->next;
            }

            free(current->key);
            free(current);

            table->size--;

            return 0;
        }

        previous = current;
        current = current->next;
    }

    return -1;
}

size_t hash_table_size(const HashTable *table){
    if(table == NULL){
        return 0;
    }
    return table->size;
}

void hash_table_free(HashTable *table)
{
    if (table == NULL)
        return;

    for (size_t i = 0; i < table->capacity; i++)
    {
        HashNode *current = table->buckets[i];

        while (current != NULL)
        {
            HashNode *next = current->next;

            free(current->key);
            free(current);

            current = next;
        }
    }

    free(table->buckets);

    table->buckets = NULL;
    table->capacity = 0;
    table->size = 0;
}