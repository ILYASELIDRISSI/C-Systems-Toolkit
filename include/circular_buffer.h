#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stddef.h>

typedef struct{
    int *data;
    size_t capacity;
    size_t size;
    size_t head;
    size_t tail;

}CircularBuffer;

int circular_buffer_init(CircularBuffer *buffer, size_t capacity);

int circular_buffer_write(CircularBuffer *buffer, int value);

int circular_buffer_read(CircularBuffer *buffer, int *value);

int circular_buffer_peek(const CircularBuffer *buffer, int *value);

int circular_buffer_is_empty(const CircularBuffer *buffer);

int circular_buffer_is_full(const CircularBuffer *buffer);

size_t circular_buffer_size(const CircularBuffer *buffer);

void circular_buffer_free(CircularBuffer *buffer);


#endif