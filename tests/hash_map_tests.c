static const char *hash_map_suite_name = "hash_map";

#include "hash_map.h"
#include "log.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool test_hash_map_create() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_create start\n");
  struct hash_map_t *hm = hash_map_create(10);
  if (hm == NULL) {
    color_log(LOG_COLOR_RED, "%s: hash_map_create returned NULL\n", hash_map_suite_name);
    return false;
  }
  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_create_zero_size() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_create_zero_size start\n");
  struct hash_map_t *hm = hash_map_create(0);
  if (hm == NULL) {
    color_log(LOG_COLOR_RED, "%s: hash_map_create(0) returned NULL\n", hash_map_suite_name);
    return false;
  }
  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_set_and_get() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_set_and_get start\n");
  struct hash_map_t *hm = hash_map_create(10);
  if (hm == NULL) {
    color_log(LOG_COLOR_RED, "%s: hash_map_create failed\n", hash_map_suite_name);
    return false;
  }

  int value = 42;
  bool result = hash_map_set(hm, "key1", (void*)(intptr_t)value);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: hash_map_set failed\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  void *out = NULL;
  result = hash_map_get(hm, "key1", &out);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: hash_map_get failed\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  if ((intptr_t)out != value) {
    color_log(LOG_COLOR_RED, "%s: value mismatch - expected %d, got %ld\n",
              hash_map_suite_name, value, (intptr_t)out);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_get_nonexistent() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_get_nonexistent start\n");
  struct hash_map_t *hm = hash_map_create(10);

  void *out = NULL;
  bool result = hash_map_get(hm, "nonexistent", &out);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: hash_map_get returned error\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  if (out != NULL) {
    color_log(LOG_COLOR_RED, "%s: nonexistent key should return NULL value\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_set_multiple() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_set_multiple start\n");
  struct hash_map_t *hm = hash_map_create(10);

  hash_map_set(hm, "key1", (void*)1);
  hash_map_set(hm, "key2", (void*)2);
  hash_map_set(hm, "key3", (void*)3);

  void *out = NULL;
  hash_map_get(hm, "key1", &out);
  if ((intptr_t)out != 1) {
    color_log(LOG_COLOR_RED, "%s: key1 value mismatch\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_get(hm, "key2", &out);
  if ((intptr_t)out != 2) {
    color_log(LOG_COLOR_RED, "%s: key2 value mismatch\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_get(hm, "key3", &out);
  if ((intptr_t)out != 3) {
    color_log(LOG_COLOR_RED, "%s: key3 value mismatch\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_update_existing_key() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_update_existing_key start\n");
  struct hash_map_t *hm = hash_map_create(10);

  hash_map_set(hm, "key", (void*)100);
  hash_map_set(hm, "key", (void*)200);

  void *out = NULL;
  hash_map_get(hm, "key", &out);
  if ((intptr_t)out != 200) {
    color_log(LOG_COLOR_RED, "%s: updated value should be 200, got %ld\n",
              hash_map_suite_name, (intptr_t)out);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_remove() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_remove start\n");
  struct hash_map_t *hm = hash_map_create(10);

  hash_map_set(hm, "key1", (void*)1);
  hash_map_set(hm, "key2", (void*)2);

  bool result = hash_map_remove(hm, "key1");
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: hash_map_remove failed\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  void *out = NULL;
  hash_map_get(hm, "key1", &out);
  if (out != NULL) {
    color_log(LOG_COLOR_RED, "%s: removed key should return NULL\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_get(hm, "key2", &out);
  if ((intptr_t)out != 2) {
    color_log(LOG_COLOR_RED, "%s: key2 should still exist\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_remove_nonexistent() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_remove_nonexistent start\n");
  struct hash_map_t *hm = hash_map_create(10);

  bool result = hash_map_remove(hm, "nonexistent");
  if (result) {
    color_log(LOG_COLOR_RED, "%s: removing nonexistent key should return false\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_remove_and_get() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_remove_and_get start\n");
  struct hash_map_t *hm = hash_map_create(10);

  hash_map_set(hm, "key1", (void*)42);

  void *out = NULL;
  bool result = hash_map_remove_and_get(hm, "key1", &out);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: hash_map_remove_and_get failed\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  if ((intptr_t)out != 42) {
    color_log(LOG_COLOR_RED, "%s: removed value should be 42, got %ld\n",
              hash_map_suite_name, (intptr_t)out);
    hash_map_destroy(&hm, false);
    return false;
  }
  
  out = NULL;
  hash_map_get(hm, "key1", &out);
  if (out != NULL) {
    color_log(LOG_COLOR_RED, "%s: key should be removed\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }
  
  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_iterator() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_iterator start\n");
  struct hash_map_t *hm = hash_map_create(10);

  hash_map_set(hm, "key1", (void*)1);
  hash_map_set(hm, "key2", (void*)2);
  hash_map_set(hm, "key3", (void*)3);

  struct hash_map_iterator_t *it = hash_map_iterator(hm);
  if (it == NULL) {
    color_log(LOG_COLOR_RED, "%s: hash_map_iterator returned NULL\n", hash_map_suite_name);
    hash_map_destroy(&hm, false);
    return false;
  }

  int count = 0;
  struct hash_map_entry_t *entry = NULL;
  while ((entry = hash_map_iterator_next(it)) != NULL) {
    count++;
  }
  free(it);

  if (count != 3) {
    color_log(LOG_COLOR_RED, "%s: expected 3 entries, got %d\n", hash_map_suite_name, count);
    hash_map_destroy(&hm, false);
    return false;
  }

  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_iterator_empty() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_iterator_empty start\n");
  struct hash_map_t *hm = hash_map_create(10);

  struct hash_map_iterator_t *it = hash_map_iterator(hm);
  struct hash_map_entry_t *entry = hash_map_iterator_next(it);

  if (entry != NULL) {
    color_log(LOG_COLOR_RED, "%s: empty map should return NULL on first iteration\n", hash_map_suite_name);
    free(it);
    hash_map_destroy(&hm, false);
    return false;
  }

  free(it);
  hash_map_destroy(&hm, false);
  return true;
}

static bool test_hash_map_destroy_null() {
  color_log(LOG_COLOR_CYAN, "test_hash_map_destroy_null start\n");
  struct hash_map_t *hm = NULL;
  hash_map_destroy(&hm, false);
  return true;
}

static void hash_map_tests() {
  int failures = 0;

  if (!test_hash_map_create()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_create failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_create_zero_size()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_create_zero_size failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_set_and_get()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_set_and_get failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_get_nonexistent()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_get_nonexistent failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_set_multiple()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_set_multiple failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_update_existing_key()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_update_existing_key failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_remove()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_remove failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_remove_nonexistent()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_remove_nonexistent failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_remove_and_get()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_remove_and_get failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_iterator()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_iterator failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_iterator_empty()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_iterator_empty failed\n", hash_map_suite_name);
    failures++;
  }
  if (!test_hash_map_destroy_null()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_map_destroy_null failed\n", hash_map_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All hash_map tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d hash_map tests failed\n", failures);
  }
}
