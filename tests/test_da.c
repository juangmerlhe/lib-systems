#include <stdio.h>
#include "da.h" 

int main() {
    IntArray my_list;
    
    // 1. Start small (Capacity 1) to force reallocs immediately
    printf("Initializing array...\n");
    da_init(&my_list, 1);
    
    printf("Initial Capacity: %zu\n", my_list.capacity);

    // 2. Stress Test: Append 100 items
    // This will force capacity to grow: 1 -> 2 -> 4 -> 8 -> 16 -> 32 -> 64 -> 128
    for (int i = 0; i < 100; i++) {
        da_append(&my_list, i * 10);
        printf("Appended %d | Size: %zu | Capacity: %zu\n", 
               i * 10, my_list.size, my_list.capacity);
    }

    // 3. Verify Data Integrity
    printf("\nVerifying data...\n");
    if (my_list.items[50] == 500) {
        printf("Index 50 contains 500. Correct.\n");
    } else {
        printf("DATA CORRUPTION DETECTED.\n");
    }

    // 4. Cleanup
    da_free(&my_list);
    printf("Memory freed. Size: %zu, Capacity: %zu\n", my_list.size, my_list.capacity);

    return 0;
}
