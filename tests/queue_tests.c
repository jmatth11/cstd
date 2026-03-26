#include "log.h"
#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static const char *queue_suite_name = "queue";

static bool test_simple_queue_create() {
  color_log(LOG_COLOR_CYAN, "test_simple_queue_create start\n");
  struct simple_queue_t *queue = simple_queue_create();
  if (queue == NULL) {
    color_log(LOG_COLOR_RED, "%s: simple_queue_create returned NULL\n", queue_suite_name);
    return false;
  }

  bool empty = simple_queue_is_empty(queue);
  if (!empty) {
    color_log(LOG_COLOR_RED, "%s: new queue should be empty\n", queue_suite_name);
    simple_queue_destroy(&queue);
    return false;
  }

  size_t len = simple_queue_len(queue);
  if (len != 0) {
    color_log(LOG_COLOR_RED, "%s: new queue length should be 0, got %zu\n", queue_suite_name, len);
    simple_queue_destroy(&queue);
    return false;
  }

  simple_queue_destroy(&queue);
  return true;
}

static bool test_simple_queue_push_pop() {
  color_log(LOG_COLOR_CYAN, "test_simple_queue_push_pop start\n");
  struct simple_queue_t *queue = simple_queue_create();

  bool success = simple_queue_push(queue, (void*)10);
  if (!success) {
    color_log(LOG_COLOR_RED, "%s: push failed\n", queue_suite_name);
    simple_queue_destroy(&queue);
    return false;
  }

  size_t len = simple_queue_len(queue);
  if (len != 1) {
    color_log(LOG_COLOR_RED, "%s: expected length 1, got %zu\n", queue_suite_name, len);
    simple_queue_destroy(&queue);
    return false;
  }

  void *val = NULL;
  success = simple_queue_pop(queue, &val);
  if (!success) {
    color_log(LOG_COLOR_RED, "%s: pop failed\n", queue_suite_name);
    simple_queue_destroy(&queue);
    return false;
  }

  if (val != (void*)10) {
    color_log(LOG_COLOR_RED, "%s: pop value mismatch, expected 10\n", queue_suite_name);
    simple_queue_destroy(&queue);
    return false;
  }

  bool empty = simple_queue_is_empty(queue);
  if (!empty) {
    color_log(LOG_COLOR_RED, "%s: queue should be empty after pop\n", queue_suite_name);
    simple_queue_destroy(&queue);
    return false;
  }

  simple_queue_destroy(&queue);
  return true;
}

static bool test_simple_queue_fifo_order() {
  color_log(LOG_COLOR_CYAN, "test_simple_queue_fifo_order start\n");
  struct simple_queue_t *queue = simple_queue_create();

  simple_queue_push(queue, (void*)1);
  simple_queue_push(queue, (void*)2);
  simple_queue_push(queue, (void*)3);

  size_t len = simple_queue_len(queue);
  if (len != 3) {
    color_log(LOG_COLOR_RED, "%s: expected length 3, got %zu\n", queue_suite_name, len);
    simple_queue_destroy(&queue);
    return false;
  }

  void *val = NULL;
  simple_queue_pop(queue, &val);
  if (val != (void*)1) {
    color_log(LOG_COLOR_RED, "%s: first pop should be 1, got %p\n", queue_suite_name, val);
    simple_queue_destroy(&queue);
    return false;
  }

  simple_queue_pop(queue, &val);
  if (val != (void*)2) {
    color_log(LOG_COLOR_RED, "%s: second pop should be 2, got %p\n", queue_suite_name, val);
    simple_queue_destroy(&queue);
    return false;
  }

  simple_queue_pop(queue, &val);
  if (val != (void*)3) {
    color_log(LOG_COLOR_RED, "%s: third pop should be 3, got %p\n", queue_suite_name, val);
    simple_queue_destroy(&queue);
    return false;
  }

  bool empty = simple_queue_is_empty(queue);
  if (!empty) {
    color_log(LOG_COLOR_RED, "%s: queue should be empty after all pops\n", queue_suite_name);
    simple_queue_destroy(&queue);
    return false;
  }

  simple_queue_destroy(&queue);
  return true;
}

static bool test_simple_queue_destroy_null() {
  color_log(LOG_COLOR_CYAN, "test_simple_queue_destroy_null start\n");
  struct simple_queue_t *queue = NULL;
  simple_queue_destroy(&queue);
  return true;
}

static void queue_tests() {
  int failures = 0;

  if (!test_simple_queue_create()) {
    color_log(LOG_COLOR_RED, "%s: test_simple_queue_create failed\n", queue_suite_name);
    failures++;
  }
  if (!test_simple_queue_push_pop()) {
    color_log(LOG_COLOR_RED, "%s: test_simple_queue_push_pop failed\n", queue_suite_name);
    failures++;
  }
  if (!test_simple_queue_fifo_order()) {
    color_log(LOG_COLOR_RED, "%s: test_simple_queue_fifo_order failed\n", queue_suite_name);
    failures++;
  }
  if (!test_simple_queue_destroy_null()) {
    color_log(LOG_COLOR_RED, "%s: test_simple_queue_destroy_null failed\n", queue_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All queue tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d queue tests failed\n", failures);
  }
}
