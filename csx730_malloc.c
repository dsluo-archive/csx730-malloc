#define _DEFAULT_SOURCE
#define _CS6730_SOURCE

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "csx730_malloc.h"

struct meta {
    size_t size;
    bool free;
    struct meta * next;
};

void * base = NULL;
void * brk0 = NULL;

/**
 * Initializes `brk0` so that we can keep track of the initial program break.
 */
void init_brk0(void) {
    if (!brk0)
        brk0 = sbrk(0);
}

void * csx730_malloc(size_t size) {
    init_brk0();

    if (size <= 0)
        return NULL;

    if (base == NULL) {
        int num_pages = (sizeof(struct meta) + size) / getpagesize() + 1;
        size_t allocate_size = num_pages * getpagesize();

        struct meta * used = sbrk(allocate_size);
        used->free = false;
        used->size = size;

        struct meta * free = (struct meta *) ((char *) (used + 1) + size);
        free->free = true;
        free->size = allocate_size - size - 2 * sizeof(struct meta);
        free->next = NULL;
        used->next = free;
        
        base = used;
        return (void *) (used + 1);
    } else {
        struct meta * current = base;
        while (current->next && (!current->free || current->size < size + sizeof(struct meta)))
            current = current->next;
        if (current->next == NULL) {
            // we're at the last block
            size_t free_size;

            struct meta * used;

            if (current->size < (size + sizeof(struct meta))) {
                // can't fit in current block; extend block to accomodate
                int num_pages = (sizeof(struct meta) + size) / getpagesize() + 1;
                size_t allocate_size = num_pages * getpagesize();

                used = (struct meta *) sbrk(allocate_size);
                if (used == (struct meta *) -1)
                    return NULL;
                
                free_size = allocate_size - 2 * sizeof(struct meta) - size;
                current->next = used;
            } else {
                // can fit in current block
                used = current;
                free_size = current->size - size - sizeof(struct meta);
            }

            used->free = false;
            used->size = size;

            struct meta * free = (struct meta *) ((char *) (used + 1) + size);
            free->free = true;

            free->size = free_size;
            free->next = NULL;
            used->next = free;

            return (void *) (used + 1);
        } else {
            // we're at a block that can hold what we want allocated.
            struct meta * free = (struct meta *) ((char *) (current + 1) + size);
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
    init_brk0();

    if (ptr == NULL)
        return;

    struct meta * current; 
    for (current = base; current && (void *) (current + 1) != ptr; current = current->next);
    if (!current) // ptr isn't something we allocated.
        return;
    current->free = true;

    // consolidate empty blocks 
    for (current = base; current && current->next;) {
        // extend this block if the next block is also free
        if (current->free && current->next->free) {
            current->size += current->next->size + sizeof(struct meta);
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }

    // this is (now) the last block; by design is always a free block
    // move program break if necessary
    // if this is also the only block in the list, deallocate as well.
    int num_pages;
    if (current == base) {
        num_pages = (current->size + sizeof(struct meta)) / getpagesize();
        base = NULL;
    } else {
        num_pages = current->size / getpagesize();
        current->size -= num_pages * getpagesize();
    }
    sbrk(-num_pages * getpagesize());
}

void csx730_pheapstats(void) {
    init_brk0();

    printf("csx730_pheapstats()\n");
    printf("{\n");
    printf("\t.page_size\t= %d (0x%x)\n", getpagesize(), getpagesize());
    printf("\t.brk0\t= %p\n", brk0);
    printf("\t.brk\t= %p\n", sbrk(0));
    size_t total = 0;
    size_t used = 0;
    size_t free = 0;
    struct meta * current = base;
    while (current) {
        total += current->size + sizeof(struct meta);
        used += current->free ? 0 : current->size;
        free += current-> free ? current->size : 0;
        current = current->next;
    }
    printf("\t.total_size\t= %lu (0x%lx)\n", total, total);
    printf("\t.used_size\t= %lu (0x%lx)\n", used, used);
    printf("\t.free_size\t= %lu (0x%lx)\n", free, free);
    printf("\t.head_meta\t= %p\n", base);
    printf("\t.meta_size\t= %lu (0x%lx)\n", sizeof(struct meta), sizeof(struct meta));
    printf("}\n");
}

void csx730_pheapmap(void) {
    init_brk0();

    printf("cs730_pheapmap()\n");
    printf("  ------------------\n");
    printf("P %p original program break\n", brk0);

    struct meta * current = base;
    while (current) {
        printf("  ------------------\n");
        printf(
            "%c %p %s block\n",
            (size_t) current % getpagesize() == 0 ? (char) 'P' : (char) ' ',
            (void *) current,
            current->free ? "free" : "used"
        );
        printf(
            "%c %p start (%lu bytes)\n",
            (size_t) (current + 1) % getpagesize() == 0 ? (char) 'P' : (char) ' ',
            (void *) (current + 1),
            current->size
        );
        printf(
            "%c %p end\n",
            ((size_t) (current + 1) + current->size) % getpagesize() == 0 ? (char) 'P' : (char) ' ',
            (char *) (current + 1) + current->size
        );
        current = current->next;
    }
    printf("  ------------------\n");
    printf(
        "%c %p program break\n",
        (size_t) (sbrk(0)) % getpagesize() == 0 ? (char) 'P' : (char) ' ',
        sbrk(0)
    );
}

void * csx730_calloc(size_t nmemb, size_t size) {
    void * ptr = csx730_malloc(nmemb * size);
    if (ptr == NULL)
        return NULL;
    
    for (size_t i = 0; i < nmemb * size; i++)
        ((char *) ptr)[i] = 0;

    return ptr;
}