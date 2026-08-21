#include <stdlib.h>
#include <stddef.h>
#include "queue.h"

int queue_init(Queue *queue, size_t capacity){

    if(queue == NULL || capacity == 0){
        return -1;
    }
    queue->data = malloc(sizeof(*(queue->data)) * capacity);
    if(queue->data == NULL){
        return -1;
    }
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;

    return 0;
}

int queue_enqueue(Queue *queue, int value)
{
    if (queue == NULL)
    {
        return -1;
    }

    if (queue->size == queue->capacity)
    {
        return -1;
    }

    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;

    return 0;
}

int queue_dequeue(Queue *queue, int *value){
    if(queue == NULL || value == NULL || queue->size == 0){
        return -1;
    }

    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return 0; 

}

int queue_peek(const Queue *queue, int *value){

    if(queue == NULL || value == NULL || queue->size == 0){
        return -1;
    }
    *value = queue->data[queue->front];
    return 0;
}

int queue_is_empty(const Queue *queue){
    if(queue == NULL){
        return -1;
    }
    if(queue->size == 0){
        return 1;
    }
    return 0;
}

int queue_is_full(const Queue *queue){

    if(queue == NULL){
        return -1;
    }
    if(queue->size == queue->capacity){
        return 1;
    }
    return 0;
}

size_t queue_size(const Queue *queue){
    if(queue == NULL){
        return 0; 
    }
    return queue->size;
}

void queue_free(Queue *queue)
{
    if (queue == NULL)
    {
        return;
    }

    free(queue->data);

    queue->data = NULL;
    queue->capacity = 0;
    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;
}