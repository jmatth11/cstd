#include "arena.h"
#include "log.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ARENA_TEST_STR "test str"
#define ARENA_OFFSET_STR "test!"

static bool test_arena_create() {
  color_log(LOG_COLOR_CYAN, "test_arena_create\n");
  struct arena_t *tmp = arena_create(5);
  if (tmp == NULL) {
    color_log(LOG_COLOR_RED, "arena_create returned NULL.\n");
    return false;
  }
  arena_destroy(&tmp);
  return true;
}

static bool test_arena_alloc() {
  color_log(LOG_COLOR_CYAN, "test_arena_alloc\n");
  struct arena_t *tmp = arena_create(20);

  const size_t len = strlen(ARENA_TEST_STR);
  char *tmp_str = arena_alloc(tmp, (sizeof(char)*(len + 1)), _Alignof(char));

  if (strncpy(tmp_str, ARENA_TEST_STR, len) == NULL) {
    color_log(LOG_COLOR_RED, "strncpy failed for arena_alloc.\n");
    arena_destroy(&tmp);
    return false;
  }
  tmp_str[len] = '\0';

  if (strncmp(tmp_str, ARENA_TEST_STR, len) != 0) {
    color_log(LOG_COLOR_RED, "string compare against arena_test_str failed.\n");
    arena_destroy(&tmp);
    return false;
  }

  arena_destroy(&tmp);
  return true;
}

static bool test_arena_alloc_alignment() {
  color_log(LOG_COLOR_CYAN, "test_arena_alloc_alignment\n");
  struct arena_t *tmp = arena_create(20);

  const size_t len = strlen(ARENA_OFFSET_STR);
  char *tmp_str = arena_alloc(tmp, sizeof(char)*(len + 1), _Alignof(char));

  if (strncpy(tmp_str, ARENA_OFFSET_STR, len) == NULL) {
    color_log(LOG_COLOR_RED, "strncpy failed for arena_alloc.\n");
    arena_destroy(&tmp);
    return false;
  }
  tmp_str[len] = '\0';

  int *num = arena_alloc(tmp, sizeof(int), _Alignof(int));
  if (num == NULL) {
    color_log(LOG_COLOR_RED, "allocating number was NULL.\n");
    return false;
  }
  *num = 5;
  if (( ((unsigned long)num) % _Alignof(int)) != 0) {
    color_log(LOG_COLOR_RED, "number was not aligned to %zu bytes.\n", _Alignof(int));
    arena_destroy(&tmp);
    return false;
  }
  arena_destroy(&tmp);
  return true;
}

static void arena_alloc_tests() {
  int failures = 0;

  if (!test_arena_create()) {
    color_log(LOG_COLOR_RED, "arena allocator create test failed.\n");
    failures++;
  }
  if (!test_arena_alloc()) {
    color_log(LOG_COLOR_RED, "arena allocator alloc test failed.\n");
    failures++;
  }
  if (!test_arena_alloc_alignment()) {
    color_log(LOG_COLOR_RED, "arena allocator alloc alignment test failed.\n");
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All arena_alloc tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d arena_alloc tests failed\n", failures);
  }
}
