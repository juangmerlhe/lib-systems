#include <stdio.h>
#include <string.h>
#include "hashmap.h" 

// Helper to print Pass/Fail
void assert_test(bool condition, const char* test_name) {
    if (condition) {
        printf("[PASS] %s\n", test_name);
    } else {
        printf("[FAIL] %s\n", test_name);
    }
}

int main() {
    printf("=== SYSTEMS CHECK INITIATED ===\n\n");
    HashMap* map = hm_create();

    // --- TEST 1: Basic PUT and GET ---
    hm_put(map, "Goku", 9000);
    hm_put(map, "Vegeta", 8000);
    
    int* val = hm_get(map, "Goku");
    assert_test(val != NULL && *val == 9000, "Retrieve Goku (9000)");

    val = hm_get(map, "Vegeta");
    assert_test(val != NULL && *val == 8000, "Retrieve Vegeta (8000)");

    val = hm_get(map, "Piccolo");
    assert_test(val == NULL, "Retrieve Non-Existent Key (NULL)");


    // --- TEST 2: Update Existing Value ---
    hm_put(map, "Goku", 9500); // Update
    val = hm_get(map, "Goku");
    assert_test(val != NULL && *val == 9500, "Update Goku Value");


    // --- TEST 3: Deletion & Tombstones ---
    hm_delete(map, "Vegeta");
    val = hm_get(map, "Vegeta");
    assert_test(val == NULL, "Delete Vegeta");

    // Re-insert to verify tombstone doesn't block insertion
    hm_put(map, "Vegeta", 8500);
    val = hm_get(map, "Vegeta");
    assert_test(val != NULL && *val == 8500, "Re-insert after Delete");


    // --- TEST 4: Stress Test & Resize ---
    // We will insert 50 items. 
    // Initial capacity is 16. It MUST resize multiple times (16 -> 32 -> 64).
    printf("\n[STRESS TEST] Inserting 50 items to force Resize...\n");
    
    char buffer[20];
    for (int i = 0; i < 50; i++) {
        sprintf(buffer, "User%d", i); // Generates "User0", "User1"...
        hm_put(map, buffer, i);
    }

    // Verify length
    // We had 2 items (Goku, Vegeta) + 50 new items = 52 total
    size_t len = hm_length(map);
    printf("Map Length: %zu (Expected 52)\n", len);
    assert_test(len == 52, "Count Tracking");

    // Verify a random item survived the resize
    val = hm_get(map, "User42");
    assert_test(val != NULL && *val == 42, "Data Integrity Post-Resize");

    // --- CLEANUP ---
    hm_destroy(map);
    printf("\n=== MEMORY CLEANED. SYSTEM SHUTDOWN. ===\n");
    
    return 0;
}
