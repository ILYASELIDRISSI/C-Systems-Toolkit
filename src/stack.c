#include "stack.h"
#include <stddef.h>
#include <stdlib.h>

int stack_init(Stack *stack, size_t capacity){

    if(stack == NULL){
        return -1;
    }
    if(d_array_init(&(stack->data),capacity) == -1){
        return -1;
    }

    return 0;
}

int stack_push(Stack *stack, int value){

    if(stack == NULL){
        return -1;
    }
    if(d_array_push(&(stack->data), value) == -1){
        return -1;
    }
    return 0;
}

int stack_pop(Stack *stack, int *value){

    if(stack ==NULL || value == NULL){
        return -1;
    }
    if(d_array_pop(&(stack->data), value)){
        return -1;
    }

    return 0;
}

int stack_peek(const Stack *stack, int *value)
{
    if (stack == NULL || value == NULL){
        return -1;
    }
    
    size_t size = d_array_size(&stack->data);

    if (size == 0){
        return -1;
    }
    return d_array_get(&stack->data, size - 1, value);
}

int stack_is_empty(const Stack *stack)
{
    if (stack == NULL)
        return -1;

    if (d_array_size(&stack->data) == 0)
        return 1;

    return 0;
}

size_t stack_size(const Stack *stack){

    if(stack == NULL){
        return 0;
    }
    if(d_array_size(&(stack->data)) == 0){
        return 0;
    }
    return d_array_size(&(stack->data));
}

void stack_free(Stack *stack){

    if(stack == NULL){
        return;
    }
    d_array_free(&(stack->data));
    return;
}