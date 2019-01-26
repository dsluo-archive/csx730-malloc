#ifndef CSX730_ALLOC_H
#define CSX730_ALLOC_H

/**
 * @file
 * This header defines the interface for the @c csx730_ family of allocators and deallocators. The
 * various functions should be familiar to anyone who has used @c malloc(3) and @c free(3). Students
 * can write and link different implementations.
 *
 * <p>
 * The @c _CS670_SOURCE feature test macro defines csx730_calloc() and csx730_realloc().
 */

/**
 * Represents a node in a doubly linked list.
 */
struct csx730_list_node {
  struct csx730_list_node * prev;
  struct csx730_list_node * next;
}; // csx730_list_node

/**
 * 
 */
struct csx730_block_info {
  void * ptr;                      /**< pointer to beginning of block */
  size_t size;                     /**< size of block, in bytes */
  enum {
	OCCUPIED,                  /**< block is being used */
	EMPTY                      /**< block is not being used */
  } status;                        /**< status of block */
  struct csx730_list_node blocks;  /**< list of all blocks */
  struct csx730_list_node free;    /**< list of free blocks */
  void * extra_info;               /**< pointer to implementation-dependent struct with extra info */
}; // csx730_block_info

/**
 * Allocates @p size bytes and returns a pointer to the allocated memory. The memory is not cleared.
 * If @p size is @c 0, then @c csx730_malloc returns either @c NULL, or a unique pointer value that 
 * can later be successfully passed to the @c csx730_free function.
 * @param size the number of bytes to allocate
 * @return on success, a pointer to the allocated memory; otherwise @c NULL
 */
void * csx730_malloc(size_t size);

/**
 * Frees the memory space pointed to by @p ptr, which must have been returned by a previous call to
 * the @c csx730_malloc, @c csx730_calloc, or @c csx730_realloc function. If @p ptr is @c NULL, then
 * no operation is performed. If @c free(ptr) has already been called, then the behavior is
 * undefined.
 * @param ptr pointer to allocated memory
 */
void csx730_free(void * ptr);

#ifdef _CS6730_SOURCE

/**
 * Allocates memory for an array of @p nmemb elements of @p size bytes each and returns a pointer to
 * the allocated memory. The memory is set to zero. If @p nmemb or @p size is @c 0, then 
 * @c csx730_calloc returns either @c NULL, or a unique pointer value that can later be successfully 
 * passed to the @c csx730_free function.
 * @remark Feature Test Macro Requirements: @c _CS6730_SOURCE
 * @param nmemb the number of elements
 * @param size the number of bytes to allocate for each element
 * @return on success, a pointer to the allocated memory; otherwise @c NULL
 */
void * csx730_calloc(size_t nmemb, size_t size);

/**
 * Changes the size of the memory block pointed to by @p ptr to @p size bytes and returns a pointer 
 * to the allocated memory, which is suitably aligned for any kind of variable and may be 
 * different from @p ptr, or @c NULL if the request fails.  The contents will be unchanged to the 
 * minimum of the old and new sizes; newly allocated memory will be uninitialized. If @p ptr is 
 * @c NULL, then the call is equivalent to @c csx730_malloc(size), for all values of @p size; if 
 * @p size is equal to zero, and @p ptr is not @c NULL, then the call is  equivalent to
 * @c csx730_free(ptr). If the call fails, then the original block is left untouched; it is not 
 * freed or moved.
 * @remark Feature Test Macro Requirements: @c _CS6730_SOURCE
 * @param ptr pointer to allocated memory block
 * @param size the new size, in bytes
 * @return on success, a pointer to the allocated memory; otherwise @c NULL
 */
void * csx730_realloc(void * ptr, size_t size);

#endif // _CS6730_SOURCE

#endif // CSX730_ALLOC_H

