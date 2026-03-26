static const char *array_template_suite_name = "array_template";

#include "array_template.h"
#include "log.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

generate_array_template(int, int)

static bool test_array_init() {
  color_log(LOG_COLOR_CYAN, "test_array_init start\n");
  int_array a;
  bool result = int_array_init(&a, 10);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: int_array_init returned false\n", array_template_suite_name);
    return false;
  }
  if (a.len != 0) {
    color_log(LOG_COLOR_RED, "%s: int_array_init len expected 0, got %lu\n", array_template_suite_name, a.len);
    int_array_free(&a);
    return false;
  }
  if (a.cap != 10) {
    color_log(LOG_COLOR_RED, "%s: int_array_init cap expected 10, got %lu\n", array_template_suite_name, a.cap);
    int_array_free(&a);
    return false;
  }
  int_array_free(&a);
  return true;
}

static bool test_array_init_zero_size() {
  color_log(LOG_COLOR_CYAN, "test_array_init_zero_size start\n");
  int_array arr;
  bool result = int_array_init(&arr, 0);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: int_array_init zero size returned false\n", array_template_suite_name);
    return false;
  }
  if (arr.cap == 0) {
    color_log(LOG_COLOR_RED, "%s: int_array_init cap should not be 0\n", array_template_suite_name);
    int_array_free(&arr);
    return false;
  }
  int_array_free(&arr);
  return true;
}

static bool test_array_insert() {
  color_log(LOG_COLOR_CYAN, "test_array_insert start\n");
  int_array arr;
  if (!int_array_init(&arr, 2)) {
    color_log(LOG_COLOR_RED, "%s: int_array_init failed\n", array_template_suite_name);
    return false;
  }
  for (int i = 0; i < 10; i++) {
    if (!int_array_insert(&arr, i)) {
      color_log(LOG_COLOR_RED, "%s: int_array_insert failed at index %d\n", array_template_suite_name, i);
      int_array_free(&arr);
      return false;
    }
  }
  if (arr.len != 10) {
    color_log(LOG_COLOR_RED, "%s: int_array_insert len expected 10, got %lu\n", array_template_suite_name, arr.len);
    int_array_free(&arr);
    return false;
  }
  for (int i = 0; i < 10; i++) {
    int val;
    int_array_get(&arr, i, &val);
    if (val != i) {
      color_log(LOG_COLOR_RED, "%s: int_array_get at index %d expected %d, got %d\n", array_template_suite_name, i, i, val);
      int_array_free(&arr);
      return false;
    }
  }
  int_array_free(&arr);
  return true;
}

static bool test_array_get() {
  color_log(LOG_COLOR_CYAN, "test_array_get start\n");
  int_array arr;
  if (!int_array_init(&arr, 5)) {
    color_log(LOG_COLOR_RED, "%s: int_array_init failed\n", array_template_suite_name);
    return false;
  }
  int_array_insert(&arr, 42);
  int_array_insert(&arr, 99);
  int val;
  int_array_get(&arr, 0, &val);
  if (val != 42) {
    color_log(LOG_COLOR_RED, "%s: int_array_get expected 42, got %d\n", array_template_suite_name, val);
    int_array_free(&arr);
    return false;
  }
  int_array_get(&arr, 1, &val);
  if (val != 99) {
    color_log(LOG_COLOR_RED, "%s: int_array_get expected 99, got %d\n", array_template_suite_name, val);
    int_array_free(&arr);
    return false;
  }
  int_array_free(&arr);
  return true;
}

static bool test_array_fast_remove() {
  color_log(LOG_COLOR_CYAN, "test_array_fast_remove start\n");
  int_array arr;
  if (!int_array_init(&arr, 10)) {
    color_log(LOG_COLOR_RED, "%s: int_array_init failed\n", array_template_suite_name);
    return false;
  }
  for (int i = 0; i < 5; i++) {
    int_array_insert(&arr, i);
  }
  if (!int_array_fast_remove(&arr, 2)) {
    color_log(LOG_COLOR_RED, "%s: int_array_fast_remove failed\n", array_template_suite_name);
    int_array_free(&arr);
    return false;
  }
  if (arr.len != 4) {
    color_log(LOG_COLOR_RED, "%s: int_array_fast_remove len expected 4, got %lu\n", array_template_suite_name, arr.len);
    int_array_free(&arr);
    return false;
  }
  int val;
  int_array_get(&arr, 2, &val);
  if (val != 4) {
    color_log(LOG_COLOR_RED, "%s: int_array_fast_remove expected 4 at index 2, got %d\n", array_template_suite_name, val);
    int_array_free(&arr);
    return false;
  }
  int_array_free(&arr);
  return true;
}

static bool test_array_fast_remove_last() {
  color_log(LOG_COLOR_CYAN, "test_array_fast_remove_last start\n");
  int_array arr;
  if (!int_array_init(&arr, 10)) {
    color_log(LOG_COLOR_RED, "%s: int_array_init failed\n", array_template_suite_name);
    return false;
  }
  for (int i = 0; i < 3; i++) {
    int_array_insert(&arr, i);
  }
  if (!int_array_fast_remove(&arr, 2)) {
    color_log(LOG_COLOR_RED, "%s: int_array_fast_remove last failed\n", array_template_suite_name);
    int_array_free(&arr);
    return false;
  }
  if (arr.len != 2) {
    color_log(LOG_COLOR_RED, "%s: int_array_fast_remove last len expected 2, got %lu\n", array_template_suite_name, arr.len);
    int_array_free(&arr);
    return false;
  }
  int_array_free(&arr);
  return true;
}

static bool test_array_free() {
  color_log(LOG_COLOR_CYAN, "test_array_free start\n");
  int_array arr;
  if (!int_array_init(&arr, 10)) {
    color_log(LOG_COLOR_RED, "%s: int_array_init failed\n", array_template_suite_name);
    return false;
  }
  int_array_insert(&arr, 1);
  int_array_insert(&arr, 2);
  int_array_free(&arr);
  if (arr.len != 0 || arr.cap != 0) {
    color_log(LOG_COLOR_RED, "%s: int_array_free len/cap not reset\n", array_template_suite_name);
    return false;
  }
  return true;
}

static bool test_array_capacity_increase() {
  color_log(LOG_COLOR_CYAN, "test_array_capacity_increase start\n");
  int_array arr;
  if (!int_array_init(&arr, 1)) {
    color_log(LOG_COLOR_RED, "%s: int_array_init failed\n", array_template_suite_name);
    return false;
  }
  size_t initial_cap = arr.cap;
  for (int i = 0; i < 10; i++) {
    int_array_insert(&arr, i);
  }
  if (arr.cap <= initial_cap) {
    color_log(LOG_COLOR_RED, "%s: int_array capacity did not increase\n", array_template_suite_name);
    int_array_free(&arr);
    return false;
  }
  int_array_free(&arr);
  return true;
}

static void array_template_tests() {
  color_log(LOG_COLOR_CYAN, "Running array_template tests\n");
  int failures = 0;

  if (!test_array_init()) {
    color_log(LOG_COLOR_RED, "%s: test_array_init failed\n", array_template_suite_name);
    failures++;
  }
  if (!test_array_init_zero_size()) {
    color_log(LOG_COLOR_RED, "%s: test_array_init_zero_size failed\n", array_template_suite_name);
    failures++;
  }
  if (!test_array_insert()) {
    color_log(LOG_COLOR_RED, "%s: test_array_insert failed\n", array_template_suite_name);
    failures++;
  }
  if (!test_array_get()) {
    color_log(LOG_COLOR_RED, "%s: test_array_get failed\n", array_template_suite_name);
    failures++;
  }
  if (!test_array_fast_remove()) {
    color_log(LOG_COLOR_RED, "%s: test_array_fast_remove failed\n", array_template_suite_name);
    failures++;
  }
  if (!test_array_fast_remove_last()) {
    color_log(LOG_COLOR_RED, "%s: test_array_fast_remove_last failed\n", array_template_suite_name);
    failures++;
  }
  if (!test_array_free()) {
    color_log(LOG_COLOR_RED, "%s: test_array_free failed\n", array_template_suite_name);
    failures++;
  }
  if (!test_array_capacity_increase()) {
    color_log(LOG_COLOR_RED, "%s: test_array_capacity_increase failed\n", array_template_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All array_template tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d array_template tests failed\n", failures);
  }
}
