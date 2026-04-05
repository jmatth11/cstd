#include "headers/arena.h"
#include <stdio.h>

struct Animal {
  char *name;
  int count;
};

int main(void) {
  // instantiate your arena allocator
  struct arena_t *arena = arena_create(4096);
  if (arena == NULL) {
    fprintf(stderr, "Failed to create arena\n");
    return 1;
  }

  // allocate an integer
  int *x = arena_alloc(arena, sizeof(int), _Alignof(int));
  *x = 42;
  printf("Allocated int: %d\n", *x);

  // allocate double
  double *d = arena_alloc(arena, sizeof(double), _Alignof(double));
  *d = 3.14159;
  printf("Allocated double: %f\n", *d);

  // allocate structure
  struct Animal **ptr =
      arena_alloc(arena, sizeof(struct Animal *), _Alignof(struct Animal *));
  printf("Allocated pointer: %p\n", (void *)ptr);

  // allocate char array
  char *buf = arena_alloc(arena, 256, _Alignof(char));
  snprintf(buf, 256, "Hello, Arena!");
  printf("Allocated string: %s\n", buf);

  // destroy and free arena
  arena_destroy(&arena);
  printf("Arena destroyed successfully\n");

  return 0;
}
