#ifndef CSTD_ARENA_ALLOCATOR_H
#define CSTD_ARENA_ALLOCATOR_H

#include <stddef.h>
#include "defs.h"

/**
 * Simple arena allocator
 */
struct arena_t;

/**
 * Create an arena allocator.
 * The arena will allocate blocks of memory in page_size chunks.
 * Once the block of memory is completely claimed another block will be allocated.
 *
 * @param size The page size of the arena.
 * @return Newly allocated arena.
 */
struct arena_t* arena_create(size_t page_size);

/**
 * Allocate a new object from the arena allocator.
 * This allocates an object on a free section of the memory block.
 * If there is no free space, a new block is allocated.
 * If the size of the object is larger than the page_size this function
 *  fails and returns NULL.
 *
 * @param ptr The arena.
 * @param size The size of the allocation.
 * @param alignment The alignment of the type. @see _Alignof
 * @return The newly allocated object, NULL if an error occurred.
 */
void* arena_alloc(struct arena_t *ptr, size_t size, size_t alignment) __nonnull((1));

/**
 * Free the arena allocator.
 *
 * @param ptr The arena.
 */
void arena_destroy(struct arena_t** ptr);



#endif
