#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include "dynamic_array.h"


typedef struct{
    DynamicArray data;
}Stack;

int stack_init(Stack *stack, size_t capacity);

int stack_push(Stack *stack, int value);

int stack_pop(Stack *stack, int *value);

int stack_peek(const Stack *stack, int *value);

int stack_is_empty(const Stack *stack);

size_t stack_size(const Stack *stack);

void stack_free(Stack *stack);

#endif