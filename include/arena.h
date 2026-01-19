#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t *buffer;
    size_t buffer_length;
    size_t offset;
} Arena;

void arena_init(Arena *a, void *backing_buffer, size_t length);
void *arena_alloc(Arena *a, size_t size);
void arena_reset(Arena *a);

#endif
