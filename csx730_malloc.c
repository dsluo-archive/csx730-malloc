#define __GNU_SOURCE

#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "csx730_malloc.h"

struct meta {
    size_t size;
    bool free;
    struct meta * next;
};

void * base = NULL;
void * brk0 = NULL;

void init_brk0(void) {
    if (!brk0)
        brk0 = sbrk(0);
}

void * csx730_malloc(size_t size) {
    init_brk0();

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
    init_brk0();

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
    init_brk0();

    printf('csx730_pheapstats()\n');
    printf('{\n');
    printf('\t.page_size\t= %d (%x)\n', getpagesize(), getpagesize());
    printf('\t.brk0\t= %p (%x)\n', brk0, brk0);
    printf('\t.brk\t= %p (%x)\n', sbrk(0), sbrk(0));
    size_t total = 0;
    size_t used = 0;
    size_t free = 0;
    struct meta * current = base;
    while (current) {
        total += current->size;
        used += current->free ? 0 : current->size;
        free += current-> free ? current->size : 0;
    }
    printf('\t.total_size\t= %d (%x)', total, total);
    printf('\t.used_size\t= %d (%x)', used, used);
    printf('\t.free_size\t= %d (%x)', free, free);
    printf('\t.head_meta\t= %p', base);
    printf('\t.meta_size\t= %d (%x)', sizeof(struct meta), sizeof(struct meta));
    printf('}\n');
}

void csx730_pheapmap(void) {
    init_brk0();

    printf('cs730_pheapmap()\n');
    printf('  ------------------\n');
    printf('P %p original program break', brk0);

    struct meta * current = base;
    while (current) {
        printf('  ------------------\n');
        printf(
            '%c %p %s block\n',
            (size_t) current % getpagesize() == 0 ? 'P' : ' ',
            current,
            current->free ? 'free' : 'used'
        );
        printf(
            '%c %p start (%d bytes)\n',
            (size_t) (current + 1) % getpagesize() == 0 ? 'P' : ' ',
            current + 1,
            current->size
        );
        printf(
            '%c %p end\n',
            (size_t) (current + 1) % getpagesize() == 0 ? 'P' : ' ',
            (void *) (current + 1) + current->size
        );
    }
    printf('  ------------------\n');
    printf(
        '%c %p program break\n',
        (size_t) (current + 1) % getpagesize() == 0 ? 'P' : ' ',
        sbrk(0)
    );
}