CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Library Sources (All your implementation files)
# We compile ALL library code for every test to ensure no missing dependencies
LIB_SRC = src/hashmap.c src/arena.c src/da.c

# --- Targets ---

# Default: Run all tests if you just type 'make'
all: test_map test_arena test_da

# 1. Hash Map Test
test_map:
	$(CC) $(CFLAGS) $(LIB_SRC) tests/test_hashmap.c -o test_map
	@echo "\n=== RUNNING HASHMAP TEST ==="
	./test_map

# 2. Memory Arena Test
test_arena:
	$(CC) $(CFLAGS) $(LIB_SRC) tests/test_memory_arena.c -o test_arena
	@echo "\n=== RUNNING ARENA TEST ==="
	./test_arena

# 3. Dynamic Array Test
test_da:
	$(CC) $(CFLAGS) $(LIB_SRC) tests/test_da.c -o test_da
	@echo "\n=== RUNNING DYNAMIC ARRAY TEST ==="
	./test_da

# Clean up binaries
clean:
	rm -f test_map test_arena test_da
