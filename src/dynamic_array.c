#include "dynamic_array.h"
#include <stdlib.h>
#include <stdio.h>

int d_array_init(DynamicArray *array, size_t initial_capacity){

    if (array == NULL){
        printf("ERROR");
        return -1;
    }
    if (initial_capacity == 0){
        printf("ERROR");
        return -1;
    }
    array->data = malloc(sizeof(*array->data)*initial_capacity);
    if(array->data == NULL){
        printf("allocation error!");
        return -1;
    }
    array->size = 0;
    array->capacity = initial_capacity;
    return 0;
    
}

int d_array_push(DynamicArray *array, int value){

    if (array == NULL){
        return -1;
    }
    if (array->capacity == array->size){
        size_t new_capacity = array->capacity * 2 ;
        int *temp = realloc(array->data,new_capacity*(sizeof(*array->data)));
        if(temp == NULL){
            return -1;
        }
        array->data = temp;
        array->capacity = new_capacity; 
    }
    array->data[array->size] = value;
    array->size++;
    return 0; 
}

int d_array_pop(DynamicArray *array, int *value){
    if(array == NULL || value == NULL){
        return -1;
    }
    if(array->size == 0){
        return -1;
    }
    *value = array->data [array->size - 1];
    array->size--;
    return 0;
}

int d_array_get(const DynamicArray *array, size_t index, int *value){
    
    if( array == NULL || value == NULL){
        return -1;
    }
    if( index >= array->size){
        return -1;
    }
    *value = array->data[index]; 
    return 0;
}

int d_array_set(DynamicArray *array, size_t index, int value){

    if(array == NULL){
        return -1;
    }
    if(index >= array->size){
        return -1; 
    }
    array->data[index] = value;
    return 0; 
}

size_t d_array_size(const DynamicArray *array){

    if(array == NULL){
        return 0;
    }
    size_t tmp = array->size;
    return tmp;
}

size_t d_array_capacity(const DynamicArray *array){
    if( array == NULL){
        return 0;
    }
    size_t tmp = array->capacity;
    return tmp;
}

void d_array_free(DynamicArray *array){

    if(array == NULL){
        return;
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;

}

int d_array_insert(DynamicArray *array, size_t index, int value)
{
    if (array == NULL)
    {
        return -1;
    }

    if (index > array->size)
    {
        return -1;
    }

    if (array->size == array->capacity)
    {
        size_t new_capacity = array->capacity * 2;

        int *temp = realloc(
            array->data,
            new_capacity * sizeof(*array->data)
        );

        if (temp == NULL)
        {
            return -1;
        }

        array->data = temp;
        array->capacity = new_capacity;
    }

    for (size_t i = array->size; i > index; i--)
    {
        array->data[i] = array->data[i - 1];
    }

    array->data[index] = value;
    array->size++;

    return 0;
}

int d_array_remove(DynamicArray *array, size_t index, int *value)
{
    if (array == NULL || value == NULL)
    {
        return -1;
    }

    if (index >= array->size)
    {
        return -1;
    }

    *value = array->data[index];

    for (size_t i = index; i < array->size - 1; i++)
    {
        array->data[i] = array->data[i + 1];
    }

    array->size--;

    return 0;
}

