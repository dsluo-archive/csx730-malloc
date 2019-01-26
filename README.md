# csx730-alloc

Implement an allocator and deallocator similar to `malloc` and `free`.

Requires:
* Knowledge of `brk(2)`, `sbrk(2)`, and `mmap(2)`.
* A good list implementation.
* A good design.

```c
struct block_info {
  void * ptr;              /* pointer to beginning of chunk */
  size_t length;           /* number of bytes allocated - sizeof(struct block_info) */
  enum { 
    SBRK, 
    MMAP 
  } syscall_used;          /* how the memory was requested */
  struct list_node blocks; /* list of blocks */
};
```

Implementations:
* `brk_alloc`
* `mmap_alloc`
* `mixed_alloc`

Advanced Requirements
* Small chunks should not cross page boundaries.
* Large chunks should be ...
