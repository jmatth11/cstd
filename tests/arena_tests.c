#include "arena.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ARENA_TEST_STR "test str"
#define ARENA_OFFSET_STR "test!"

static bool test_arena_create() {
  printf("test_arena_create start\n");
  struct arena_t *tmp = arena_create(5);
  if (tmp == NULL) {
    fprintf(stderr, "arena_create returned NULL.\n");
    return false;
  }
  arena_destroy(&tmp);
  return true;
}

static bool test_arena_alloc() {
  printf("test_arena_alloc start\n");
  struct arena_t *tmp = arena_create(20);

  const size_t len = strlen(ARENA_TEST_STR);
  char *tmp_str = arena_alloc(tmp, (sizeof(char)*(len + 1)), _Alignof(char));

  if (strncpy(tmp_str, ARENA_TEST_STR, len) == NULL) {
    fprintf(stderr, "strncpy failed for arena_alloc.\n");
    arena_destroy(&tmp);
    return false;
  }
  tmp_str[len] = '\0';

  if (strncmp(tmp_str, ARENA_TEST_STR, len) != 0) {
    fprintf(stderr, "string compare against arena_test_str failed.\n");
    arena_destroy(&tmp);
    return false;
  }

  arena_destroy(&tmp);
  return true;
}

static bool test_arena_alloc_alignment() {
  printf("test_arena_alloc_alignment start\n");
  struct arena_t *tmp = arena_create(20);

  const size_t len = strlen(ARENA_OFFSET_STR);
  char *tmp_str = arena_alloc(tmp, sizeof(char)*(len + 1), _Alignof(char));

  if (strncpy(tmp_str, ARENA_OFFSET_STR, len) == NULL) {
    fprintf(stderr, "strncpy failed for arena_alloc.\n");
    arena_destroy(&tmp);
    return false;
  }
  tmp_str[len] = '\0';

  int *num = arena_alloc(tmp, sizeof(int), _Alignof(int));
  if (num == NULL) {
    fprintf(stderr, "allocating number was NULL.\n");
    return false;
  }
  *num = 5;
  if (( ((unsigned long)num) % _Alignof(int)) != 0) {
    fprintf(stderr, "number was not aligned to %zu bytes.\n", _Alignof(int));
    arena_destroy(&tmp);
    return false;
  }
  arena_destroy(&tmp);
  return true;
}

static void arena_alloc_tests() {
  if (!test_arena_create()) {
    fprintf(stderr, "arena allocator create test failed.\n");
  }
  if (!test_arena_alloc()) {
    fprintf(stderr, "arena allocator alloc test failed.\n");
  }
  if (!test_arena_alloc_alignment()) {
    fprintf(stderr, "arena allocator alloc alignment test failed.\n");
  }
}
