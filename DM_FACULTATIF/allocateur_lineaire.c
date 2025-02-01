#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 32;
uint64_t heap[HEAP_SIZE];

const uint64_t block_size = 8;

int init_heap() {
    heap[0] = 0;
}

uint64_t* malloc_ui(uint64_t size) {
    if(heap[0] + size > HEAP_SIZE) return nullptr;
    return &heap[heap[0] + size];
}





