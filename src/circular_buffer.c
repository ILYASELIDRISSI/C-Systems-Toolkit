#include <stdlib.h>
#include "circular_buffer.h"

int circular_buffer_init(CircularBuffer *buffer, size_t capacity)
{
    if (buffer == NULL || capacity == 0)
    {
        return -1;
    }

    buffer->data = malloc(capacity * sizeof(*buffer->data));

    if (buffer->data == NULL)
    {
        return -1;
    }

    buffer->capacity = capacity;
    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;

    return 0;
}

int circular_buffer_write(CircularBuffer *buffer, int value)
{
    if (buffer == NULL)
    {
        return -1;
    }

    buffer->data[buffer->tail] = value;
    buffer->tail = (buffer->tail + 1) % buffer->capacity;

    if (buffer->size == buffer->capacity)
    {
        buffer->head = (buffer->head + 1) % buffer->capacity;
    }
    else
    {
        buffer->size++;
    }

    return 0;
}

int circular_buffer_read(CircularBuffer *buffer, int *value)
{
    if (buffer == NULL || value == NULL || buffer->size == 0)
    {
        return -1;
    }

    *value = buffer->data[buffer->head];
    buffer->head = (buffer->head + 1) % buffer->capacity;
    buffer->size--;

    return 0;
}

int circular_buffer_peek(const CircularBuffer *buffer, int *value)
{
    if (buffer == NULL || value == NULL || buffer->size == 0)
    {
        return -1;
    }

    *value = buffer->data[buffer->head];

    return 0;
}

int circular_buffer_is_empty(const CircularBuffer *buffer)
{
    if (buffer == NULL)
    {
        return -1;
    }

    return buffer->size == 0;
}

int circular_buffer_is_full(const CircularBuffer *buffer)
{
    if (buffer == NULL)
    {
        return -1;
    }

    return buffer->size == buffer->capacity;
}

size_t circular_buffer_size(const CircularBuffer *buffer)
{
    if (buffer == NULL)
    {
        return 0;
    }

    return buffer->size;
}

void circular_buffer_free(CircularBuffer *buffer)
{
    if (buffer == NULL)
    {
        return;
    }

    free(buffer->data);

    buffer->data = NULL;
    buffer->capacity = 0;
    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;
}