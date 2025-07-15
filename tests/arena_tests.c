#include "arena.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ARENA_TEST_STR "test str"
#define ARENA_OFFSET_STR "test!"

static bool test_arena_create() {
  struct arena_t *tmp = arena_create(5);
  if (tmp == NULL) {
    fprintf(stderr, "arena_create returned NULL.\n");
    return false;
  }
  arena_destroy(&tmp);
  return true;
}

static bool test_arena_alloc() {
  struct arena_t *tmp = arena_create(20);

  char *tmp_str = arena_alloc(tmp, (sizeof(char)*strlen(ARENA_TEST_STR)) + 1, _Alignof(char));

  if (strncpy(tmp_str, ARENA_TEST_STR, strlen(ARENA_TEST_STR)) == NULL) {
    fprintf(stderr, "strncpy failed for arena_alloc.\n");
    arena_destroy(&tmp);
    return false;
  }
  tmp_str[strlen(ARENA_TEST_STR)] = '\0';

  if (strncmp(tmp_str, ARENA_TEST_STR, strlen(ARENA_TEST_STR)) != 0) {
    fprintf(stderr, "string compare against arena_test_str failed.\n");
    arena_destroy(&tmp);
    return false;
  }

  arena_destroy(&tmp);
  return true;
}

static bool test_arena_alloc_alignment() {
  struct arena_t *tmp = arena_create(20);

  char *tmp_str = arena_alloc(tmp, sizeof(char)*6, _Alignof(char));

  if (strncpy(tmp_str, ARENA_OFFSET_STR, strlen(ARENA_OFFSET_STR)) == NULL) {
    fprintf(stderr, "strncpy failed for arena_alloc.\n");
    arena_destroy(&tmp);
    return false;
  }
  tmp_str[strlen(ARENA_OFFSET_STR)] = '\0';

  int *num = arena_alloc(tmp, sizeof(int), _Alignof(int));
  if (num == NULL) {
    fprintf(stderr, "allocating number was NULL.\n");
    return false;
  }
  *num = 5;
  // TODO fix comparison
  if ((num % _Alignof(int)) == 0) {

  }

  arena_destroy(&tmp);
  return true;
}
