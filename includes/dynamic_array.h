#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

typedef struct{

    int* data;
    size_t size;
    size_t capacity;
}DynamicArray;

int d_array_init(DynamicArray *array, size_t initial_capacity);

int d_array_push(DynamicArray *array, int value);

int d_array_pop(DynamicArray *array, int *value);

int d_array_get(const DynamicArray *array, size_t index, int *value);

int d_array_set(DynamicArray *array, size_t index, int value);

size_t d_array_size(const DynamicArray *array);

size_t d_array_capacity(const DynamicArray *array);

void d_array_free(DynamicArray *array);



#endif