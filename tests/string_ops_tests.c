static const char *string_ops_suite_name = "string_ops";

#include "string_ops.h"
#include "log.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool test_str_dup_basic() {
  color_log(LOG_COLOR_CYAN, "test_str_dup_basic\n");
  const char *input = "hello world";
  char *result = str_dup(input, 5);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: str_dup returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strncmp(result, "hello", 5) != 0) {
    color_log(LOG_COLOR_RED, "%s: str_dup result mismatch\n", string_ops_suite_name);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_str_dup_full() {
  color_log(LOG_COLOR_CYAN, "test_str_dup_full\n");
  const char *input = "test";
  char *result = str_dup(input, 4);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: str_dup full returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "test") != 0) {
    color_log(LOG_COLOR_RED, "%s: str_dup full result mismatch\n", string_ops_suite_name);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_str_dup_zero_length() {
  color_log(LOG_COLOR_CYAN, "test_str_dup_zero_length\n");
  const char *input = "hello";
  char *result = str_dup(input, 0);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: str_dup zero length returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (result[0] != '\0') {
    color_log(LOG_COLOR_RED, "%s: str_dup zero length should be empty string\n", string_ops_suite_name);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_str_fmt_int() {
  color_log(LOG_COLOR_CYAN, "test_str_fmt_int\n");
  char *result = str_fmt("value: %d", 42);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: str_fmt returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "value: 42") != 0) {
    color_log(LOG_COLOR_RED, "%s: str_fmt int mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_str_fmt_string() {
  color_log(LOG_COLOR_CYAN, "test_str_fmt_string\n");
  char *result = str_fmt("hello %s", "world");
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: str_fmt string returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "hello world") != 0) {
    color_log(LOG_COLOR_RED, "%s: str_fmt string mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_concat_basic() {
  color_log(LOG_COLOR_CYAN, "test_concat_basic\n");
  size_t len = 0;
  char *result = concat("hello", " world", &len);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: concat returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "hello world") != 0) {
    color_log(LOG_COLOR_RED, "%s: concat result mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  if (len != 11) {
    color_log(LOG_COLOR_RED, "%s: concat length mismatch: got %lu\n", string_ops_suite_name, len);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_concat_empty_strings() {
  color_log(LOG_COLOR_CYAN, "test_concat_empty_strings\n");
  size_t len = 0;
  char *result = concat("", "", &len);
  if (result == NULL) {
    color_log(LOG_COLOR_YELLOW, "%s: concat empty returned NULL (empty concat not supported)\n", string_ops_suite_name);
    return true;
  }
  if (len != 0) {
    color_log(LOG_COLOR_RED, "%s: concat empty length should be 0\n", string_ops_suite_name);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_concat_null_inputs() {
  color_log(LOG_COLOR_CYAN, "test_concat_null_inputs\n");
  size_t len = 0;
  char *result = concat(NULL, "test", &len);
  if (result != NULL) {
    color_log(LOG_COLOR_RED, "%s: concat with NULL a should return NULL\n", string_ops_suite_name);
    free(result);
    return false;
  }
  result = concat("test", NULL, &len);
  if (result != NULL) {
    color_log(LOG_COLOR_RED, "%s: concat with NULL b should return NULL\n", string_ops_suite_name);
    free(result);
    return false;
  }
  return true;
}

static bool test_to_str_length_int() {
  color_log(LOG_COLOR_CYAN, "test_to_str_length_int\n");
  size_t len = to_str_length_int(123);
  if (len != 3) {
    color_log(LOG_COLOR_RED, "%s: to_str_length_int(123) expected 3, got %lu\n", string_ops_suite_name, len);
    return false;
  }
  len = to_str_length_int(-456);
  if (len != 4) {
    color_log(LOG_COLOR_RED, "%s: to_str_length_int(-456) expected 4, got %lu\n", string_ops_suite_name, len);
    return false;
  }
  return true;
}

static bool test_to_str_length_double() {
  color_log(LOG_COLOR_CYAN, "test_to_str_length_double\n");
  size_t len = to_str_length_double(1.5);
  if (len == 0) {
    color_log(LOG_COLOR_RED, "%s: to_str_length_double(1.5) returned 0\n", string_ops_suite_name);
    return false;
  }
  return true;
}

static bool test_to_str_length_long() {
  color_log(LOG_COLOR_CYAN, "test_to_str_length_long\n");
  size_t len = to_str_length_long(1234567890123);
  if (len != 13) {
    color_log(LOG_COLOR_RED, "%s: to_str_length_long expected 13, got %lu\n", string_ops_suite_name, len);
    return false;
  }
  return true;
}

static bool test_to_str_int() {
  color_log(LOG_COLOR_CYAN, "test_to_str_int\n");
  char *result = to_str_int(42);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_str_int returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "42") != 0) {
    color_log(LOG_COLOR_RED, "%s: to_str_int mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);

  result = to_str_int(-99);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_str_int negative returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "-99") != 0) {
    color_log(LOG_COLOR_RED, "%s: to_str_int negative mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_to_str_double() {
  color_log(LOG_COLOR_CYAN, "test_to_str_double\n");
  char *result = to_str_double(3.14);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_str_double returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "3.140000") != 0) {
    color_log(LOG_COLOR_RED, "%s: to_str_double mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_to_str_long() {
  color_log(LOG_COLOR_CYAN, "test_to_str_long\n");
  char *result = to_str_long(9876543210);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_str_long returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "9876543210") != 0) {
    color_log(LOG_COLOR_RED, "%s: to_str_long mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_to_str_macro_int() {
  color_log(LOG_COLOR_CYAN, "test_to_str_macro_int\n");
  char *result = to_str(42);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_str(int) returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "42") != 0) {
    color_log(LOG_COLOR_RED, "%s: to_str(int) mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_to_str_macro_double() {
  color_log(LOG_COLOR_CYAN, "test_to_str_macro_double\n");
  char *result = to_str(2.5);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_str(double) returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "2.500000") != 0) {
    color_log(LOG_COLOR_RED, "%s: to_str(double) mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_to_str_macro_long() {
  color_log(LOG_COLOR_CYAN, "test_to_str_macro_long\n");
  char *result = to_str(123456789L);
  if (result == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_str(long) returned NULL\n", string_ops_suite_name);
    return false;
  }
  if (strcmp(result, "123456789") != 0) {
    color_log(LOG_COLOR_RED, "%s: to_str(long) mismatch: got %s\n", string_ops_suite_name, result);
    free(result);
    return false;
  }
  free(result);
  return true;
}

static bool test_to_str_length_macro_int() {
  color_log(LOG_COLOR_CYAN, "test_to_str_length_macro_int\n");
  size_t len = to_str_length(42);
  if (len != 2) {
    color_log(LOG_COLOR_RED, "%s: to_str_length(42) expected 2, got %lu\n", string_ops_suite_name, len);
    return false;
  }
  return true;
}

static bool test_to_str_length_macro_double() {
  color_log(LOG_COLOR_CYAN, "test_to_str_length_macro_double\n");
  size_t len = to_str_length(1.5);
  if (len == 0) {
    color_log(LOG_COLOR_RED, "%s: to_str_length(double) returned 0\n", string_ops_suite_name);
    return false;
  }
  return true;
}

static void string_ops_tests() {
  int failures = 0;

  if (!test_str_dup_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_str_dup_basic failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_str_dup_full()) {
    color_log(LOG_COLOR_RED, "%s: test_str_dup_full failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_str_dup_zero_length()) {
    color_log(LOG_COLOR_RED, "%s: test_str_dup_zero_length failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_str_fmt_int()) {
    color_log(LOG_COLOR_RED, "%s: test_str_fmt_int failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_str_fmt_string()) {
    color_log(LOG_COLOR_RED, "%s: test_str_fmt_string failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_concat_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_concat_basic failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_concat_empty_strings()) {
    color_log(LOG_COLOR_RED, "%s: test_concat_empty_strings failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_concat_null_inputs()) {
    color_log(LOG_COLOR_RED, "%s: test_concat_null_inputs failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_length_int()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_length_int failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_length_double()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_length_double failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_length_long()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_length_long failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_int()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_int failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_double()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_double failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_long()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_long failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_macro_int()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_macro_int failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_macro_double()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_macro_double failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_macro_long()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_macro_long failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_length_macro_int()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_length_macro_int failed\n", string_ops_suite_name);
    failures++;
  }
  if (!test_to_str_length_macro_double()) {
    color_log(LOG_COLOR_RED, "%s: test_to_str_length_macro_double failed\n", string_ops_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All string_ops tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d string_ops tests failed\n", failures);
  }
}
