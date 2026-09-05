#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct{

    int *data;
    size_t capacity;
    size_t size;

    size_t rear;
    size_t front;
}Queue;

int queue_init(Queue *queue, size_t capacity);

int queue_enqueue(Queue *queue, int value);

int queue_dequeue(Queue *queue, int *value);

int queue_peek(const Queue *queue, int *value);

int queue_is_empty(const Queue *queue);

int queue_is_full(const Queue *queue);

size_t queue_size(const Queue *queue);

void queue_free(Queue *queue);

#endif