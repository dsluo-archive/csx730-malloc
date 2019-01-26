# csx730-alloc

Implement an allocator and deallocator similar to `malloc` and `free`.

Requires:
* Knowledge of `brk(2)`, `sbrk(2)`, and `mmap(2)`.
* A good list implementation.
* A good design.

```c
struct chunk_meta {
  void * ptr;              /* pointer to beginning of chunk */
  size_t length;           /* number of bytes allocated */ 
  size_t used;             /* number of bytes used */
  struct list_node blocks; /* list of blocks */
};
```
