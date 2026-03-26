#include "linked_list.h"
#include "log.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static const char *linked_list_suite_name = "linked_list";

static bool test_linked_list_create() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_create start\n");
  struct linked_list_t *ll = linked_list_create((void*)42);
  if (ll == NULL) {
    color_log(LOG_COLOR_RED, "%s: linked_list_create returned NULL\n", linked_list_suite_name);
    return false;
  }
  if (ll->value != (void*)42) {
    color_log(LOG_COLOR_RED, "%s: value mismatch\n", linked_list_suite_name);
    linked_list_free(ll);
    return false;
  }
  linked_list_free(ll);
  return true;
}

static bool test_linked_list_init() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_init start\n");
  struct linked_list_t *ll = malloc(sizeof(struct linked_list_t));
  bool result = linked_list_init(ll);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: linked_list_init returned false\n", linked_list_suite_name);
    free(ll);
    return false;
  }
  if (ll->next != NULL || ll->prev != NULL || ll->value != NULL) {
    color_log(LOG_COLOR_RED, "%s: init did not set fields correctly\n", linked_list_suite_name);
    free(ll);
    return false;
  }
  ll->value = (void*)100;
  linked_list_free(ll);
  return true;
}

static bool test_linked_list_append() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_append start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);

  linked_list_append(ll, (void*)2);
  linked_list_append(ll, (void*)3);

  size_t len = linked_list_get_len(ll);
  if (len != 3) {
    color_log(LOG_COLOR_RED, "%s: expected length 3, got %zu\n", linked_list_suite_name, len);
    linked_list_free_all(ll);
    return false;
  }

  struct linked_list_t *node = linked_list_get_pos(ll, 0);
  if (node->value != (void*)1) {
    color_log(LOG_COLOR_RED, "%s: pos 0 value mismatch\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  node = linked_list_get_pos(ll, 1);
  if (node->value != (void*)2) {
    color_log(LOG_COLOR_RED, "%s: pos 1 value mismatch\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  node = linked_list_get_pos(ll, 2);
  if (node->value != (void*)3) {
    color_log(LOG_COLOR_RED, "%s: pos 2 value mismatch\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_insert() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_insert start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);

  linked_list_insert(ll, 1, (void*)3);
  linked_list_insert(ll, 1, (void*)2);

  size_t len = linked_list_get_len(ll);
  if (len != 3) {
    color_log(LOG_COLOR_RED, "%s: expected length 3, got %zu\n", linked_list_suite_name, len);
    linked_list_free_all(ll);
    return false;
  }

  struct linked_list_t *node = linked_list_get_pos(ll, 0);
  if (node->value != (void*)1) {
    color_log(LOG_COLOR_RED, "%s: pos 0 value mismatch\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  node = linked_list_get_pos(ll, 1);
  if (node->value != (void*)2) {
    color_log(LOG_COLOR_RED, "%s: pos 1 value mismatch\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  node = linked_list_get_pos(ll, 2);
  if (node->value != (void*)3) {
    color_log(LOG_COLOR_RED, "%s: pos 2 value mismatch\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_get_pos() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_get_pos start\n");
  struct linked_list_t *ll = linked_list_create((void*)10);
  linked_list_append(ll, (void*)20);
  linked_list_append(ll, (void*)30);

  struct linked_list_t *node = linked_list_get_pos(ll, 0);
  if (node == NULL || node->value != (void*)10) {
    color_log(LOG_COLOR_RED, "%s: get_pos(0) failed\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  node = linked_list_get_pos(ll, 1);
  if (node == NULL || node->value != (void*)20) {
    color_log(LOG_COLOR_RED, "%s: get_pos(1) failed\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  node = linked_list_get_pos(ll, 2);
  if (node == NULL || node->value != (void*)30) {
    color_log(LOG_COLOR_RED, "%s: get_pos(2) failed\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  node = linked_list_get_pos(ll, 99);
  if (node != NULL) {
    color_log(LOG_COLOR_RED, "%s: get_pos(99) should return NULL\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_get_end() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_get_end start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);
  linked_list_append(ll, (void*)2);
  linked_list_append(ll, (void*)3);

  struct linked_list_t *end = linked_list_get_end(ll);
  if (end == NULL || end->value != (void*)3) {
    color_log(LOG_COLOR_RED, "%s: get_end failed\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_get_len() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_get_len start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);

  size_t len = linked_list_get_len(ll);
  if (len != 1) {
    color_log(LOG_COLOR_RED, "%s: initial length should be 1, got %zu\n", linked_list_suite_name, len);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_append(ll, (void*)2);
  linked_list_append(ll, (void*)3);
  linked_list_append(ll, (void*)4);

  len = linked_list_get_len(ll);
  if (len != 4) {
    color_log(LOG_COLOR_RED, "%s: expected length 4, got %zu\n", linked_list_suite_name, len);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_delete() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_delete start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);
  linked_list_append(ll, (void*)2);
  linked_list_append(ll, (void*)3);

  ll = linked_list_delete(ll, 1);

  size_t len = linked_list_get_len(ll);
  if (len != 2) {
    color_log(LOG_COLOR_RED, "%s: expected length 2 after delete, got %zu\n", linked_list_suite_name, len);
    linked_list_free_all(ll);
    return false;
  }

  struct linked_list_t *node = linked_list_get_pos(ll, 0);
  if (node->value != (void*)1) {
    color_log(LOG_COLOR_RED, "%s: pos 0 value should be 1\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  node = linked_list_get_pos(ll, 1);
  if (node->value != (void*)3) {
    color_log(LOG_COLOR_RED, "%s: pos 1 value should be 3\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_delete_first() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_delete_first start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);
  linked_list_append(ll, (void*)2);
  linked_list_append(ll, (void*)3);

  ll = linked_list_delete(ll, 0);

  size_t len = linked_list_get_len(ll);
  if (len != 2) {
    color_log(LOG_COLOR_RED, "%s: expected length 2, got %zu\n", linked_list_suite_name, len);
    linked_list_free_all(ll);
    return false;
  }

  struct linked_list_t *node = linked_list_get_pos(ll, 0);
  if (node->value != (void*)2) {
    color_log(LOG_COLOR_RED, "%s: first value should be 2\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_delete_node() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_delete_node start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);
  linked_list_append(ll, (void*)2);
  linked_list_append(ll, (void*)3);

  struct linked_list_t *node_to_delete = linked_list_get_pos(ll, 1);
  linked_list_delete_node(node_to_delete);

  size_t len = linked_list_get_len(ll);
  if (len != 2) {
    color_log(LOG_COLOR_RED, "%s: expected length 2, got %zu\n", linked_list_suite_name, len);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_delete_invalid_pos() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_delete_invalid_pos start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);

  struct linked_list_t *result = linked_list_delete(ll, 99);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: delete at invalid pos should return ll\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static bool test_linked_list_free_null() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_free_null start\n");
  linked_list_free(NULL);
  linked_list_free_all(NULL);
  return true;
}

static bool test_linked_list_head() {
  color_log(LOG_COLOR_CYAN, "test_linked_list_head start\n");
  struct linked_list_t *ll = linked_list_create((void*)1);
  linked_list_append(ll, (void*)2);
  linked_list_append(ll, (void*)3);

  struct linked_list_t *middle = linked_list_get_pos(ll, 1);
  struct linked_list_t *head = linked_list_head(middle);
  if (head == NULL || head->value != (void*)1) {
    color_log(LOG_COLOR_RED, "%s: linked_list_head failed\n", linked_list_suite_name);
    linked_list_free_all(ll);
    return false;
  }

  linked_list_free_all(ll);
  return true;
}

static void linked_list_tests() {
  int failures = 0;

  if (!test_linked_list_create()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_create failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_init()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_init failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_append()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_append failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_insert()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_insert failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_get_pos()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_get_pos failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_get_end()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_get_end failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_get_len()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_get_len failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_delete()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_delete failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_delete_first()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_delete_first failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_delete_node()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_delete_node failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_delete_invalid_pos()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_delete_invalid_pos failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_free_null()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_free_null failed\n", linked_list_suite_name);
    failures++;
  }
  if (!test_linked_list_head()) {
    color_log(LOG_COLOR_RED, "%s: test_linked_list_head failed\n", linked_list_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All linked_list tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d linked_list tests failed\n", failures);
  }
}
