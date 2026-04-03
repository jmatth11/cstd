#include <stdio.h>
#include "headers/arena.h"

int main(void) {
    struct arena_t *arena = arena_create(4096);
    if (arena == NULL) {
        fprintf(stderr, "Failed to create arena\n");
        return 1;
    }

    int *x = arena_alloc(arena, sizeof(int), _Alignof(int));
    *x = 42;
    printf("Allocated int: %d\n", *x);

    double *d = arena_alloc(arena, sizeof(double), _Alignof(double));
    *d = 3.14159;
    printf("Allocated double: %f\n", *d);

    struct arena_t **ptr = arena_alloc(arena, sizeof(void*), _Alignof(void*));
    printf("Allocated pointer: %p\n", (void*)ptr);

    char *buf = arena_alloc(arena, 256, 1);
    snprintf(buf, 256, "Hello, Arena!");
    printf("Allocated string: %s\n", buf);

    arena_destroy(&arena);
    printf("Arena destroyed successfully\n");

    return 0;
}
