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
 *
 * @param size The size of the arena.
 * @return Newly allocated arena.
 */
struct arena_t* arena_create(size_t size);

/**
 * Allocate a new object from the arena allocator.
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
