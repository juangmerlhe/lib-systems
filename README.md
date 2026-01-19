# lib-systems

A collection of high-performance, hand-written core utilities for systems programming in C. 
Designed to be the standard library for my future projects (HTTP Server, Satellite Scheduler, etc.).

## 🧩 Modules

### 1. Memory Arena (`arena.h`)
A linear memory allocator for high-performance, cache-friendly memory management. 
- **O(1) Allocation:** Pointer bumping only.
- **Zero-overhead Deallocation:** Frees the entire block at once.

### 2. Hash Map (`hashmap.h`)
An open-addressing hash map implementation.
- **Linear Probing:** Cache-efficient collision resolution.
- **Dynamic Resizing:** Auto-expands at 75% load factor.
- **Tombstones:** Correctly handles deletion in probe chains.

### 3. Dynamic Array (`da.h`)
A resizeable array implementation for C.

## 🛠️ Build & Test

This project uses a unified Makefile for testing.

```bash
# Run all tests
make all

# Run specific module test
make test_map
make test_arena
