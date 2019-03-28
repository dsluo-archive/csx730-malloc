#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include "csx730_malloc.h"

struct meta {
    size_t size;
    bool free;
    struct meta * next;
};

void * base = NULL;

void * csx730_malloc(size_t size) {
    if (size <= 0)
        return NULL;

    int num_blocks = (sizeof(struct meta) + size) / getpagesize();
    int extra = (sizeof(struct meta) + size) % getpagesize();
    num_blocks += extra != 0 ? 1 : 0;
    size_t allocate_size = num_blocks * getpagesize();

    if (base == NULL) {
        struct meta * used = sbrk(allocate_size);
        used->free = false;
        used->size = size;

        struct meta * free = (void *) (used + 1) + size + 1;
        free->free = true;
        free->size = allocate_size - size - 2 * sizeof(struct meta);
        free->next = NULL;
        used->next = free;
        
        base = used;
        return (void *) (used + 1);
    } else {
        struct meta * current = base;
        while (current->next && !current->free && current->size < (size + sizeof(struct meta)))
            current = current->next;
        if (current->next == NULL && !current->free) {
            // we're at the last block and it's allocated. move program break
            struct meta * used = sbrk(allocate_size);
            if (used == (void *) -1)
                return NULL;

            used->free = false;
            used->size = size;

            struct meta * free = (void *) (used + 1) + size + 1;
            free->free = true;
            free->size = allocate_size - size - 2 * sizeof(struct meta);
            free->next = NULL;
            used->next = free;

            return (void *) (used + 1);
        } else {
            // we're at a block that can hold what we want allocated.
            struct meta * free = (void *) (current + 1) + size + 1;
            free->free = true;
            free->size = current->size - size - sizeof(struct meta);
            free->next = current->next;

            current->free = false;
            current->size = size;
            current->next = free;
            
            return (void *) (current + 1);
        }
    }
}

void csx730_free(void * ptr) {
    if (ptr == NULL)
        return;
    
    struct meta * current = base;
    while (current && (void *) (current + 1) != ptr)
        current = current->next;
    if (!current) // ptr isn't something we allocated.
        return;

    current->free = true;

    // extend this block if the next block is also free
    if (current->next && current->next->free) {
        current->size += current->next->size + sizeof(struct meta);
        current->next = current->next->next;
    }

    // this is (now) the last block; move program break if necessary
    if (!current->next) {
        size_t move_brk = -1 * (current->size / getpagesize()) * getpagesize();
        current->size += move_brk;
        sbrk(move_brk);
}
}

void csx730_pheapstats(void) {

}

void csx730_pheapmap(void) {

}