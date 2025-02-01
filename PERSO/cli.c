#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

const int SIZE_MEMORY = 32;

chunk* MEMORY = malloc(sizeof(chunk) * SIZE_MEMORY);

struct Chunk { int size; int* data };

typedef Chunk chunk;

int length(chunk memory) {
    return memory.size;
}

chunk create_memory(int size) {
    return {size ; malloc(size * sizeof(int))};
}

chunk read_memory(chunk memory, int index) {
    assert(index < length(memory));
    return memory.data[index];
}

void write_memory(chunk memory, int index, int el) {
    assert(index < length(memory));
    memory.data[index] = el;
}

void destroy(chunk memory) {
    free(memory.data);
}


struct File { char* name, int* content }

//



char** parse_argument(char* string) {
    int size_of_vector = ceil(strlen(string)/2); // au max la moitiée de ' ';
    char** parsed_arguments = malloc(size_of_vector * sizeof(char*));
    int ind = 0;

    int length = strlen(string);
    char* new_string = malloc(sizeof(char*) * length);
    int index = 0;

    for(int i = 0; i<length; i++) {
        if(string[i] == ' ') {
            parsed_arguments[ind] = new_string;
            ind++;
            index = 0;
        }
        else {
            new_string[index] = string[i];
            index++;
        }
    }

    free(new_string);
    return parsed_arguments;
}