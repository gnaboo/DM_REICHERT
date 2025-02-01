#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <bool.h>

bool compile_program(char* name, int size) {
    /*
    int main(char* argv) {

    
    
    
        return 0;
    } 
    */
   return true;
}

double running_time(char* name, int size) {
    double start_time = clock();

    int ret = system(String.concat(String.concat(String.concat("./", name), " "), size));
    if(ret == 0) { return 0. };

    double end_time = clock();

    return (double) (end_time - start_time) / CLOCKS_PER_SEC;
}

int test_accurate_complexity(int* times) {
    
}

bool test_time(char* name) {
    for(int i = 0; i<pow(2, _INTEGRAL_MAX_BITS); i*=2) {
        printf("Testing for i: time: [%f]", i running_time(i));
    }
}



int main() {




    return 0;
}