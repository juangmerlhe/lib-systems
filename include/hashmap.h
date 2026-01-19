#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define HM_INITIAL_CAPACITY 16
#define HM_MAX_LOAD_FACTOR 0.75

typedef enum {
    SLOT_EMPTY = 0,
    SLOT_OCCUPIED,
    SLOT_DELETED
} SlotState;

typedef struct {
    char* key;
    int value;
    SlotState state;
} HM_Entry;

typedef struct {
    HM_Entry* entries;
    size_t capacity;
    size_t count;
} HashMap;

// lifecycle
HashMap* hm_create(void);
void hm_destroy(HashMap* map);

// core operations
bool hm_put(HashMap* map, const char* key, int value);
int* hm_get(HashMap* map, const char* key);
bool hm_delete(HashMap* map, const char* key);

// utilities
size_t hm_length(HashMap* map);
void hm_debug_print(HashMap* map);

#endif
