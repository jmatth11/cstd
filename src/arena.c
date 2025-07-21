#include "headers/arena.h"

#include <stdlib.h>
#include <string.h>

struct arena_t {
  size_t size;
  size_t offset;
  void *ptr;
  struct arena_t *next;
};

struct arena_t* arena_create(size_t page_size) {
  struct arena_t *result = malloc(sizeof(struct arena_t));
  if (result == NULL) {
    return NULL;
  }
  result->size = page_size;
  result->offset = 0;
  result->ptr = malloc(page_size);
  result->next = NULL;
  if (result->ptr == NULL) {
    free(result);
    return NULL;
  }
  return result;
}

static void* arena_get_next_alloc(struct arena_t *ptr, size_t size, size_t alignment) {
  if (ptr->next == NULL) {
    ptr->next = arena_create(ptr->size);
    return arena_alloc(ptr->next, size, alignment);
  }
  return arena_alloc(ptr->next, size, alignment);
}

void* arena_alloc(struct arena_t *ptr, size_t size, size_t alignment) {
  // size is bigger than arena page size
  if (size > ptr->size) {
    return NULL;
  }
  if (ptr->offset == ptr->size) {
    return arena_get_next_alloc(ptr, size, alignment);
  }
  // get alignment padding to conform to CPU memory layout
  size_t padding = (alignment - (ptr->offset % alignment)) % alignment;
  size_t aligned_offset = ptr->offset + padding;
  size_t new_offset = aligned_offset + size;
  if (new_offset > size) {
    return arena_get_next_alloc(ptr, size, alignment);
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
  if ((*ptr)->next != NULL) {
    arena_destroy( &((*ptr)->next) );
  }
  free((*ptr)->ptr);
  free(*ptr);
  *ptr = NULL;
}
