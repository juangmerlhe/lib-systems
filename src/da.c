#include <stdio.h>
#include <stdlib.h>
#include "da.h"

// 1. initialize the array
void da_init(IntArray *a, size_t initial_capacity) {
	// we need an initial_capacity > 0 
	if (initial_capacity < 1 ) initial_capacity = 1;

	// allocate memory
       	a->items = malloc(initial_capacity * sizeof(int)); 

    	// check if malloc returned null (out of memory). if so, exit 
	if (a->items == NULL) exit(1);

	a->size = 0;
	a->capacity = initial_capacity;
}

// 2. add an item to the end
void da_append(IntArray *a, int value) {
    // step 1: check if the list is full (size equals capacity)
    if (a->size == a->capacity) {
        // calculate new capacity, i read standard practice is to double it
	// preventing to use realloc (slow)
	size_t new_capacity = a->capacity * 2;
        
        // resize the memory block using realloc
        int *temp = realloc(a->items, new_capacity * sizeof(int));
        
        // safety
	if (temp == NULL) exit(1);
	a->items = temp;
	a->capacity = new_capacity; // Update capacity only after success
    }
    a->items[a->size] = value;
    a->size++;

}

// 3. clean up memory
void da_free(IntArray *a) {
    // return the memory to the os using free() on the items pointer
    free(a->items);
    // safety: set the items pointer to null so you don't use it by accident later
    a->items = NULL;
    // set size and capacity to 0
    a->size = 0;
    a->capacity = 0;
}
