#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// --- private helper functions ---

// fnv-1a hash algorithm (faster than cryptographic algortihms)
static uint32_t hash_function(const char* key) {
    
	uint32_t hash = 2166136261;
	
	for (int i = 0; key[i] != '\0'; i++){
		hash = hash ^ key[i];
		hash = hash * 16777619;
	}
	return hash;
}

// expands the hash map when load factor > 0.75
static bool hm_resize(HashMap* map) {
    size_t new_capacity = map->capacity * 2;
    
    // allocate new entries
    HM_Entry* new_entries = calloc(new_capacity, sizeof(HM_Entry));
    if (new_entries == NULL) return false;
    // save old entries info
    HM_Entry* old_entries = map->entries;
    size_t old_capacity = map->capacity;

    map->entries = new_entries;
    map->capacity = new_capacity;
    // map->count stays the same

    for (size_t i = 0; i < old_capacity; i++) {
        
	// only move occupied slots, skip deleted (we clean the entries)    
        if (old_entries[i].state == SLOT_OCCUPIED) {
		
	    const char* key = old_entries[i].key;
	    int value = old_entries[i].value;

	    uint32_t hash = hash_function(key);
            uint32_t index = hash % new_capacity; 

            while (true) {
                if (new_entries[index].state == SLOT_EMPTY) {
                    new_entries[index].key = (char*)key; // Transfer ownership
                    new_entries[index].value = value;
                    new_entries[index].state = SLOT_OCCUPIED;
                    break;
                }
                // if collision move to the next 
		index = (index + 1) % new_capacity;
            }	
        }
    }

    free(old_entries);

    return true;
}

// --- public api implementation ---

HashMap* hm_create(void) {
    	
	HashMap *map = malloc(sizeof(HashMap));
	if (map == NULL) return NULL;
	
	map->capacity = HM_INITIAL_CAPACITY;
	map->count = 0;

	map->entries = calloc(map->capacity, sizeof(HM_Entry));

	if (map->entries == NULL){

		free(map);
		return NULL;
	}

	return map;
}

void hm_destroy(HashMap* map) {
    if (map == NULL) return; // Safety check

    // 1. Iterate through the entire capacity (not count!)
    for (size_t i = 0; i < map->capacity; i++) {
        
        // check if the slot has a key (Occupied)
        if (map->entries[i].state == SLOT_OCCUPIED) {
            
            // free the string we allocated
            // Note: we use '.' because entries[i] is the struct itself
            free(map->entries[i].key);
        }
    }

    free(map->entries);
    free(map);
}

bool hm_put(HashMap* map, const char* key, int value) {
    if (map->count >= map->capacity * HM_MAX_LOAD_FACTOR){
	if(!hm_resize(map)) return false;
    }
    uint32_t hash = hash_function(key);
    uint32_t index = hash % map->capacity;
    

    // don't end the loop if i reach the end, indexes lower than index might be available
    while (true) {
	HM_Entry *entry = &map->entries[index];

	// caso 1: empty slot
	if (entry->key == NULL){
		// entry->key now has its own copy of the key variable
		// otherwise, we would point to temporary memory (like a stack variable)
		// that disappears when the function ends, causing a crash
		entry->key = strdup(key);
		if (entry->key == NULL) return false; //malloc failed

		entry->value = value;
		entry->state = SLOT_OCCUPIED;

		map->count++;
		return true;
	}

	// caso 2: update existing key (matching keys)
	
	if (strcmp(entry->key, key) == 0) {
		entry->value = value;
		return true;
	}
	
	// caso 3: slot occupied -> move to next slot
	index = (index + 1) % map->capacity;

    }
}

int* hm_get(HashMap* map, const char* key) {
   
    uint32_t hash = hash_function(key);
    uint32_t index = hash % map->capacity;
    

    // don't end the loop if i reach the end, indexes lower than index might be available
    while (true) {
	HM_Entry *entry = &map->entries[index];

	// key doesnt exist, we dont keep looking	
	if (entry->key == NULL){
		return NULL;	
	}

	
	// match
	if (strcmp(entry->key, key) == 0) {
		return &entry->value;
	}
	

	index = (index + 1) % map->capacity;

    } 
}

bool hm_delete(HashMap* map, const char* key) {
    uint32_t hash = hash_function(key);
    uint32_t index = hash % map->capacity;
    

    while (true) {
	HM_Entry *entry = &map->entries[index];

	if (entry->state == SLOT_EMPTY){
		return false;	
	}
	
	// check match only if it's occupied
	if (entry->state == SLOT_OCCUPIED && strcmp(entry->key, key) == 0) {
		free(entry->key);
		entry->key = NULL;
		entry->value = 0;
		entry->state = SLOT_DELETED;
		map->count--;
		return true;
	}
	

	index = (index + 1) % map->capacity;

    }  
    return false;
}

size_t hm_length(HashMap* map) {
    return map->count;
}

void hm_debug_print(HashMap* map) {
	HM_Entry* entries = map->entries;
	for (size_t i = 0; i < map->capacity; i++) {
		if (entries[i].state == SLOT_EMPTY) {
			printf("[%zu] .\n", i);
		} else if (entries[i].state == SLOT_OCCUPIED) {
			printf("[%zu] %s: %d\n", i, entries[i].key, entries[i].value);
		} else {

			printf("[%zu]  X (Tombstone)\n", i);	
		}
	}
}


