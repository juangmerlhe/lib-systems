#include <stddef.h>

typedef struct {
    int *items;
    size_t size;
    size_t capacity;
} IntArray;

// The "Interface" you need to build:
void da_init(IntArray *a, size_t initial_capacity);
void da_append(IntArray *a, int value);
void da_free(IntArray *a);
