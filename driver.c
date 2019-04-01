#include <stdio.h>
#include "csx730_malloc.h"


int main() {
    printf("init\n");
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("allocate p1 (32 bytes)\n"); 
    void * p1 = csx730_malloc(32);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("allocate p2 (4048 bytes)\n"); 
    void * p2 = csx730_malloc(4048);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("allocate p3 (16384 bytes)\n"); 
    void * p3 = csx730_malloc(16384);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("free p1 (32 bytes)\n");
    csx730_free(p1);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("free p3 (16384 bytes)\n");
    csx730_free(p3);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("allocating p4 (100 bytes)\n");
    void * p4 = csx730_malloc(100);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("allocating p5 (100 bytes)\n");
    void * p5 = csx730_malloc(100);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("allocating p6 (1025 bytes)\n");
    void * p6 = csx730_malloc(1025);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("freeing rest (p2, p4, p5, p6)\n");
    csx730_free(p2);
    csx730_free(p4);
    csx730_free(p5);
    csx730_free(p6);
    csx730_pheapmap();
    csx730_pheapstats();
    printf("\n");

    printf("allocate p7 (4072 bytes)\n");
    void * p7 = csx730_malloc(4072);
    csx730_pheapmap();
    csx730_pheapstats();
}