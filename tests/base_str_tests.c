static const char *base_str_suite_name = "base_str";

#include "base_str.h"
#include "log.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool test_new_base_str_basic() {
  color_log(LOG_COLOR_CYAN, "test_new_base_str_basic\n");
  base_str str;
  base_str_error err = new_base_str(&str, 10);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: new_base_str returned error\n", base_str_suite_name);
    return false;
  }
  if (str.length(&str) != 0) {
    color_log(LOG_COLOR_RED, "%s: new_base_str length should be 0\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_new_base_str_zero_capacity() {
  color_log(LOG_COLOR_CYAN, "test_new_base_str_zero_capacity\n");
  base_str str;
  base_str_error err = new_base_str(&str, 0);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: new_base_str zero cap returned error\n", base_str_suite_name);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_new_base_str_with_string_basic() {
  color_log(LOG_COLOR_CYAN, "test_new_base_str_with_string_basic\n");
  base_str str;
  const char *input = "hello";
  base_str_error err = new_base_str_with_string(&str, input, 5);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: new_base_str_with_string returned error\n", base_str_suite_name);
    return false;
  }
  if (str.length(&str) != 5) {
    color_log(LOG_COLOR_RED, "%s: new_base_str_with_string length mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  char *result;
  str.get_str(&str, &result);
  if (strcmp(result, "hello") != 0) {
    color_log(LOG_COLOR_RED, "%s: new_base_str_with_string content mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_new_base_str_with_string_empty() {
  color_log(LOG_COLOR_CYAN, "test_new_base_str_with_string_empty\n");
  base_str str;
  base_str_error err = new_base_str_with_string(&str, "", 0);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: new_base_str_with_string empty returned error\n", base_str_suite_name);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_append_basic() {
  color_log(LOG_COLOR_CYAN, "test_append_basic\n");
  base_str str;
  base_str_error err = new_base_str(&str, 10);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: append setup failed\n", base_str_suite_name);
    return false;
  }
  err = str.append(&str, "hello", 5);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: append returned error\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  if (str.length(&str) != 5) {
    color_log(LOG_COLOR_RED, "%s: append length mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  char *result;
  str.get_str(&str, &result);
  if (strcmp(result, "hello") != 0) {
    color_log(LOG_COLOR_RED, "%s: append content mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_append_multiple() {
  color_log(LOG_COLOR_CYAN, "test_append_multiple\n");
  base_str str;
  new_base_str(&str, 10);
  str.append(&str, "hello", 5);
  str.append(&str, " world", 6);
  if (str.length(&str) != 11) {
    color_log(LOG_COLOR_RED, "%s: append multiple length mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  char *result;
  str.get_str(&str, &result);
  if (strcmp(result, "hello world") != 0) {
    color_log(LOG_COLOR_RED, "%s: append multiple content mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_set_basic() {
  color_log(LOG_COLOR_CYAN, "test_set_basic\n");
  base_str str;
  new_base_str_with_string(&str, "initial", 7);
  base_str_error err = str.set(&str, "updated", 7);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: set returned error\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  if (str.length(&str) != 7) {
    color_log(LOG_COLOR_RED, "%s: set length mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  char *result;
  str.get_str(&str, &result);
  if (strcmp(result, "updated") != 0) {
    color_log(LOG_COLOR_RED, "%s: set content mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_at_valid_index() {
  color_log(LOG_COLOR_CYAN, "test_at_valid_index\n");
  base_str str;
  new_base_str_with_string(&str, "hello", 5);
  char out;
  base_str_error err = str.at(&str, 0, &out);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: at valid index returned error\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  if (out != 'h') {
    color_log(LOG_COLOR_RED, "%s: at valid index content mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  err = str.at(&str, 4, &out);
  if (err != C_STR_NO_ERROR || out != 'o') {
    color_log(LOG_COLOR_RED, "%s: at last index failed\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_at_out_of_bounds() {
  color_log(LOG_COLOR_CYAN, "test_at_out_of_bounds\n");
  base_str str;
  new_base_str_with_string(&str, "hello", 5);
  char out;
  base_str_error err = str.at(&str, 10, &out);
  if (err != C_STR_OUT_OF_BOUNDS) {
    color_log(LOG_COLOR_RED, "%s: at out of bounds should return error\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_copy_basic() {
  color_log(LOG_COLOR_CYAN, "test_copy_basic\n");
  base_str str;
  new_base_str_with_string(&str, "hello", 5);
  char *result;
  base_str_error err = str.copy(&str, &result);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: copy returned error\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  if (strcmp(result, "hello") != 0) {
    color_log(LOG_COLOR_RED, "%s: copy content mismatch\n", base_str_suite_name);
    free(result);
    free_base_str(&str);
    return false;
  }
  free(result);
  free_base_str(&str);
  return true;
}

static bool test_get_str_and_get_const_str() {
  color_log(LOG_COLOR_CYAN, "test_get_str_and_get_const_str\n");
  base_str str;
  new_base_str_with_string(&str, "test", 4);
  char *result;
  base_str_error err = str.get_str(&str, &result);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: get_str returned error\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  const char *const_result;
  err = str.get_const_str(&str, &const_result);
  if (err != C_STR_NO_ERROR) {
    color_log(LOG_COLOR_RED, "%s: get_const_str returned error\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  if (strcmp(const_result, "test") != 0) {
    color_log(LOG_COLOR_RED, "%s: get_const_str content mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static bool test_free_base_str_null() {
  color_log(LOG_COLOR_CYAN, "test_free_base_str_null\n");
  free_base_str(NULL);
  return true;
}

static bool test_length() {
  color_log(LOG_COLOR_CYAN, "test_length\n");
  base_str str;
  new_base_str_with_string(&str, "hello world", 11);
  if (str.length(&str) != 11) {
    color_log(LOG_COLOR_RED, "%s: length mismatch\n", base_str_suite_name);
    free_base_str(&str);
    return false;
  }
  free_base_str(&str);
  return true;
}

static void base_str_tests() {
  int failures = 0;

  if (!test_new_base_str_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_new_base_str_basic failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_new_base_str_zero_capacity()) {
    color_log(LOG_COLOR_RED, "%s: test_new_base_str_zero_capacity failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_new_base_str_with_string_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_new_base_str_with_string_basic failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_new_base_str_with_string_empty()) {
    color_log(LOG_COLOR_RED, "%s: test_new_base_str_with_string_empty failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_append_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_append_basic failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_append_multiple()) {
    color_log(LOG_COLOR_RED, "%s: test_append_multiple failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_set_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_set_basic failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_at_valid_index()) {
    color_log(LOG_COLOR_RED, "%s: test_at_valid_index failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_at_out_of_bounds()) {
    color_log(LOG_COLOR_RED, "%s: test_at_out_of_bounds failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_copy_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_copy_basic failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_get_str_and_get_const_str()) {
    color_log(LOG_COLOR_RED, "%s: test_get_str_and_get_const_str failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_free_base_str_null()) {
    color_log(LOG_COLOR_RED, "%s: test_free_base_str_null failed\n", base_str_suite_name);
    failures++;
  }
  if (!test_length()) {
    color_log(LOG_COLOR_RED, "%s: test_length failed\n", base_str_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All base_str tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d base_str tests failed\n", failures);
  }
}
