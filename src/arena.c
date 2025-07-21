#include "headers/arena.h"

#include <stdlib.h>
#include <string.h>

struct arena_t {
  size_t size;
  size_t offset;
  void *ptr;
};

struct arena_t* arena_create(size_t size) {
  struct arena_t *result = malloc(sizeof(struct arena_t));
  if (result == NULL) {
    return NULL;
  }
  result->size = size;
  result->offset = 0;
  result->ptr = malloc(size);
  if (result->ptr == NULL) {
    free(result);
    return NULL;
  }
  return result;
}

void* arena_alloc(struct arena_t *ptr, size_t size, size_t alignment) {
  // get alignment padding to conform to CPU memory layout
  size_t padding = (alignment - (ptr->offset % alignment)) % alignment;
  size_t aligned_offset = ptr->offset + padding;
  size_t new_offset = aligned_offset + size;
  if (size > ptr->size) {
    // TODO figure out how to increase size without invalidating previous pointer
    return NULL;
  }
  void *result = (void*)(ptr->ptr + aligned_offset);
  ptr->offset = new_offset;
  (void)memset(result, 0, size);
  return result;
}

void arena_destroy(struct arena_t** ptr) {
  if (ptr == NULL) {
    return;
  }
  if (*ptr == NULL) {
    return;
  }
  (*ptr)->size = 0;
  (*ptr)->offset = 0;
  free((*ptr)->ptr);
  free(*ptr);
  *ptr = NULL;
}
