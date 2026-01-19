#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


#define DEFAULT_ALIGNMENT 8


typedef struct {
	uint8_t *buffer;     // the big chunk of memory
	size_t buffer_length;
	size_t offset;       // current position
} Arena;

// 1- Initializing the big chunk of memory
void arena_init(Arena *a, void *backing_buffer, size_t length){
	a->buffer = (uint8_t *)backing_buffer; // Assigning the memory "created" in the main function
	a->buffer_length = length;
	a->offset = 0;
}


// 2- The main function, returning a pointer to "size" bytes

// Lack of memory allignment (a variable could start at an address that isn't a multiple of 4)
// This could make programs slow or even get them killed


	//void *arena_alloc(Arena *a, size_t size){
	
	//	if (a->offset + size > a->buffer_length){
	//		printf("Out of memory\n");
	//		return NULL;
	//	}

	//	void *ptr = a->buffer + a->offset;
	//	a->offset += size;
	//	return ptr;
	//}

// Corrected Version

void *arena_alloc(Arena *a, size_t size) {
    uintptr_t current_ptr = (uintptr_t)a->buffer + a->offset;
    
    // Calculate the padding needed to reach a multiple of 8
    // This is the "Alignment" logic
    uintptr_t aligned_ptr = (current_ptr + (DEFAULT_ALIGNMENT - 1)) & ~(DEFAULT_ALIGNMENT - 1);
    
    // Calculate the new offset based on the ALIGNED pointer
    size_t new_offset = (aligned_ptr - (uintptr_t)a->buffer) + size;

    // Safety Check
    if (new_offset > a->buffer_length) {
        printf("Out of memory\n");
        return NULL;
    }

    // Update offset and return the aligned address
    a->offset = new_offset;
    return (void *)aligned_ptr;
}


// 3- Freeing everything in O(1)
void arena_reset(Arena *a){
	a->offset = 0;
}


