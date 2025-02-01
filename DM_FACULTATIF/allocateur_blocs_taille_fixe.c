#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 32;
uint64_t heap[HEAP_SIZE];

const uint64_t block_size = 8;

uint64_t heap_index(uint64_t* p);

int init_heap() {
    heap[0] = 1;
}

bool is_free(uint64_t i) {
    return i == 0;
}

void set_free(uint64_t i) {
    heap[i] = 0;
}

void set_used(uint64_t i) {
    heap[i] = 1;
}

uint64_t* malloc_ui(uint64_t size) {
    if(size > block_size || heap[0] == 32 /* 32 // 8*/) return nullptr;

    uint64_t end = heap[0];
    for(int i = 0; i < end; i++) {

        if(heap[i * block_size] == 0) {
            set_used(i * block_size)
            return &heap[i * block_size + 1];
        }
    }
    return &heap[(end+1) * block_size + 1];
}

void free_ui(uint64_t* p) {
    uint64_t i = heap_index(p);
    if(heap[0] == i) heap[0] = heap[0] - block_size;
    else set_free(heap[i]);
}






