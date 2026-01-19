#include "arena.h"

int main() {
    uint8_t backing_buffer[1024];
    Arena a;
    arena_init(&a, backing_buffer, 1024);

    // test 1: basic allocation
    int *my_num = (int *)arena_alloc(&a, sizeof(int));
    float *my_float = (float *)arena_alloc(&a, sizeof(float));

    if (my_num) *my_num = 44;
    if (my_float) *my_float = 2.14f;

    printf("test 1 - basic allocation:\n");
    printf("number: %d, float: %f\n", *my_num, *my_float);
    printf("used: %zu bytes\n\n", a.offset);

    arena_reset(&a);

    // test 2: memory alignment
    // allocate 1 byte. without alignment, the next addr would be +1.
    // with 8-byte alignment, the next addr must be +8.
    printf("test 2 - alignment check:\n");
    void *ptr1 = arena_alloc(&a, 1);
    void *ptr2 = arena_alloc(&a, 1);

    uintptr_t addr1 = (uintptr_t)ptr1;
    uintptr_t addr2 = (uintptr_t)ptr2;

    printf("address 1: %p\n", ptr1);
    printf("address 2: %p\n", ptr2);
    printf("distance: %lu bytes (should be 8)\n", (unsigned long)(addr2 - addr1));

    if ((addr2 - addr1) == 8) {
        printf("alignment test passed\n");
    } else {
        printf("alignment test failed\n");
    }

    return 0;
}
