#include "unicode_str.h"
#include "log.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "helpers.c"

static const char *unicode_str_unicode_str_suite_name = "unicode_str";

static bool unicode_str_create_test() {
  struct unicode_str_t *local = unicode_str_create();
  bool result = local != NULL;
  unicode_str_destroy(&local);
  return result;
}

static bool unicode_str_set_and_get_test() {
  color_log(LOG_COLOR_CYAN, "unicode_str_set_and_get_test\n");
  byte_array test_str = byte_array_from_str("test value");
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    color_log(LOG_COLOR_RED, "%s: result_size != test_str.len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, test_str.len);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    color_log(LOG_COLOR_RED, "%s: unicode string get failed\n", unicode_str_unicode_str_suite_name);
    return false;
  }
  if (out == NULL) {
    color_log(LOG_COLOR_RED, "%s: unicode string get returned NULL\n", unicode_str_unicode_str_suite_name);
    return false;
  }
  if (!compare_byte_arrays(test_str, *out)) {
    color_log(LOG_COLOR_RED, "%s: strings in set_and_get were not the same -- expected:\"%s\" != got:\"%s\"\n",
            unicode_str_unicode_str_suite_name, test_str.byte_data, out->byte_data);
    return false;
  }
  unicode_str_destroy(&local);
  byte_array_free(&test_str);
  return true;
}

static bool unicode_str_append_tests() {
  color_log(LOG_COLOR_CYAN, "unicode_str_append_tests\n");
  byte_array expected = byte_array_from_str("test value -- addition");
  byte_array postfix = byte_array_from_str(" -- addition");
  byte_array test_str = byte_array_from_str("test value");
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    color_log(LOG_COLOR_RED, "%s: result_size != test_str_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, test_str.len);
    return false;
  }
  const size_t postfix_result_len =
      unicode_str_append(local, postfix.byte_data, postfix.len);
  if (postfix_result_len != postfix.len) {
    color_log(LOG_COLOR_RED,
            "%s: unicode str append failed to write the correct number of "
            "bytes -- expected %lu, got %lu\n",
            unicode_str_unicode_str_suite_name, postfix.len, postfix_result_len);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    color_log(LOG_COLOR_RED, "%s: unicode string get failed\n", unicode_str_unicode_str_suite_name);
    return false;
  }
  if (out == NULL) {
    color_log(LOG_COLOR_RED, "%s: unicode string get returned NULL\n", unicode_str_unicode_str_suite_name);
    return false;
  }
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: strings in append were not the same -- expected:%s != got:%s\n",
            unicode_str_unicode_str_suite_name, expected.byte_data, out->byte_data);
    return false;
  }
  unicode_str_destroy(&local);
  byte_array_free(&expected);
  byte_array_free(&postfix);
  byte_array_free(&test_str);
  return true;
}

static bool unicode_str_insert_at_tests() {
  color_log(LOG_COLOR_CYAN, "unicode_str_insert_at_tests\n");
  byte_array expected = byte_array_from_str("test value -- addition");
  byte_array infix = byte_array_from_str(" --");
  byte_array test_str = byte_array_from_str("test value addition");
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    color_log(LOG_COLOR_RED, "%s: result_size != test_str_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, test_str.len);
    return false;
  }
  const size_t infix_result_len =
      unicode_str_insert_at(local, infix.byte_data, infix.len, 10);
  if (infix_result_len != infix.len) {
    color_log(LOG_COLOR_RED,
            "%s: unicode str insert_at failed to write the correct number of "
            "bytes -- expected %lu, got %lu\n",
            unicode_str_unicode_str_suite_name, infix.len, infix_result_len);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    color_log(LOG_COLOR_RED, "%s: unicode string get failed\n", unicode_str_unicode_str_suite_name);
    return false;
  }
  if (out == NULL) {
    color_log(LOG_COLOR_RED, "%s: unicode string get returned NULL\n", unicode_str_unicode_str_suite_name);
    return false;
  }
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: strings in insert_at were not the same -- expected:%s != got:%s\n",
            unicode_str_unicode_str_suite_name, expected.byte_data, out->byte_data);
    return false;
  }
  unicode_str_destroy(&local);
  byte_array_free(&expected);
  byte_array_free(&infix);
  byte_array_free(&test_str);
  return true;
}

static bool unicode_str_remove_range_tests() {
  color_log(LOG_COLOR_CYAN, "unicode_str_remove_range_tests\n");
  byte_array expected = byte_array_from_str("123789");
  byte_array test_str = byte_array_from_str("123456789");
  const size_t expected_remove_len = 3;
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    color_log(LOG_COLOR_RED, "%s: result_size != test_str_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, test_str.len);
    return false;
  }
  const size_t remove_result_len =
      unicode_str_remove_range(local, 3, expected_remove_len);
  if (remove_result_len != expected_remove_len) {
    color_log(LOG_COLOR_RED,
            "%s: unicode str remove_range failed to write the correct number of "
            "bytes -- expected %lu, got %lu\n",
            unicode_str_unicode_str_suite_name, expected_remove_len, remove_result_len);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    color_log(LOG_COLOR_RED, "%s: unicode string get failed\n", unicode_str_unicode_str_suite_name);
    return false;
  }
  if (out == NULL) {
    color_log(LOG_COLOR_RED, "%s: unicode string get returned NULL\n", unicode_str_unicode_str_suite_name);
    return false;
  }
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: strings in remove_range were not the same -- expected:%s != got:%s\n",
            unicode_str_unicode_str_suite_name, expected.byte_data, out->byte_data);
    return false;
  }
  unicode_str_destroy(&local);
  byte_array_free(&expected);
  byte_array_free(&test_str);
  return true;
}

static bool unicode_str_len_tests() {
  color_log(LOG_COLOR_CYAN, "unicode_str_len_tests\n");
  byte_array expected = byte_array_from_str("123456");
  const size_t expected_len = 6;
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, expected.byte_data, expected.len);
  if (result_size != expected_len) {
    color_log(LOG_COLOR_RED, "%s: expected result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, expected.len);
    return false;
  }
  const size_t len_result = unicode_str_len(local);
  if (len_result != expected_len) {
    color_log(LOG_COLOR_RED, "%s: len_result result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, len_result, expected_len);
    return false;
  }
  byte_array expected_unicode = byte_array_from_str("Д");
  const size_t expected_codepoint_len = 1;
  const size_t expected_byte_len = 2;
  const size_t unicode_result_size = unicode_str_set(local, expected_unicode.byte_data, expected_unicode.len);
  if (unicode_result_size != expected_byte_len) {
    color_log(LOG_COLOR_RED, "%s: expected_byte_len result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, expected_byte_len);
    return false;
  }
  const size_t codepoint_len_result = unicode_str_len(local);
  if (codepoint_len_result != expected_codepoint_len) {
    color_log(LOG_COLOR_RED, "%s: codepoint_len_result result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, codepoint_len_result, expected_codepoint_len);
    return false;
  }
  unicode_str_destroy(&local);
  byte_array_free(&expected);
  byte_array_free(&expected_unicode);
  return true;
}

static bool unicode_str_byte_len_tests() {
  color_log(LOG_COLOR_CYAN, "unicode_str_byte_len_tests\n");
  byte_array expected = byte_array_from_str("123456");
  const size_t expected_len = 6;
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, expected.byte_data, expected.len);
  if (result_size != expected_len) {
    color_log(LOG_COLOR_RED, "%s: expected result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, expected_len);
    return false;
  }
  const size_t len_result = unicode_str_byte_len(local);
  if (len_result != expected_len) {
    color_log(LOG_COLOR_RED, "%s: len_result result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, len_result, expected_len);
    return false;
  }
  byte_array expected_unicode = byte_array_from_str("Д");
  const size_t expected_unicode_len = 2;
  const size_t unicode_result_size = unicode_str_set(local, expected_unicode.byte_data, expected_unicode.len);
  if (unicode_result_size != expected_unicode_len) {
    color_log(LOG_COLOR_RED, "%s: expected_unicode result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, expected_unicode_len);
    return false;
  }
  const size_t unicode_len_result = unicode_str_byte_len(local);
  if (unicode_len_result != expected_unicode_len) {
    color_log(LOG_COLOR_RED, "%s: unicode_len_result result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, unicode_len_result, expected_unicode_len);
    return false;
  }
  unicode_str_destroy(&local);
  byte_array_free(&expected);
  byte_array_free(&expected_unicode);
  return true;
}

static bool unicode_str_codepoint_at_tests() {
  color_log(LOG_COLOR_CYAN, "unicode_str_codepoint_at_tests\n");
  byte_array expected = byte_array_from_str("Я был когда-то странной");
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, expected.byte_data, expected.len);
  if (result_size != expected.len) {
    color_log(LOG_COLOR_RED, "%s: expected result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, expected.len);
    return false;
  }
  code_point_t out = 0;
  if (!unicode_str_codepoint_at(local, 9, &out)) {
    color_log(LOG_COLOR_RED, "%s: getting codepoint failed.\n",
            unicode_str_unicode_str_suite_name);
    return false;
  }
  byte_array single_unicode_codepoint = byte_array_from_str("д");
  struct code_point rune = utf8_next(single_unicode_codepoint.byte_data, single_unicode_codepoint.len, 0);
  if (rune.val != out) {
    color_log(LOG_COLOR_RED, "%s: Code points did not match expected:%d got:%d.\n",
            unicode_str_unicode_str_suite_name, rune.val, out);
    return false;
  }
  unicode_str_destroy(&local);
  byte_array_free(&expected);
  byte_array_free(&single_unicode_codepoint);
  return true;
}

static bool unicode_str_get_range_tests() {
  color_log(LOG_COLOR_CYAN, "unicode_str_get_range_tests\n");
  byte_array test_str = byte_array_from_str("Я был когда-то странной");
  const size_t start_index = 6;
  byte_array expected = byte_array_from_str("когда-то");
  const size_t expected_codepoint_len = 8;
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    color_log(LOG_COLOR_RED, "%s: expected result_size != expected_len -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, test_str.len);
    return false;
  }
  uint8_t *out = NULL;
  if (!unicode_str_get_range(local, start_index, expected_codepoint_len, &out)) {
    color_log(LOG_COLOR_RED, "%s: getting range failed.\n",
            unicode_str_unicode_str_suite_name);
    return false;
  }
  if (!compare_byte_array_and_uint8(expected, out)) {
    color_log(LOG_COLOR_RED, "%s: strings in get_range were not the same -- expected:\"%s\" != got:\"%s\"\n",
            unicode_str_unicode_str_suite_name, expected.byte_data, out);
    return false;
  }
  free(out);
  unicode_str_destroy(&local);
  byte_array_free(&test_str);
  byte_array_free(&expected);
  return true;
}

static bool codepoint_idx_from_byte_idx_tests() {
  color_log(LOG_COLOR_CYAN, "codepoint_idx_from_byte_idx_tests\n");
  byte_array expected = byte_array_from_str("Я был когда-то странной");
  const size_t test_byte_idx = 8;
  const size_t expected_codepoint_idx = 5;
  const size_t result_idx = codepoint_idx_from_byte_idx(expected.byte_data, expected.len, test_byte_idx);
  if (result_idx != expected_codepoint_idx) {
    color_log(LOG_COLOR_RED, "%s: Code point index was not correct -- expected:%lu got:%lu.\n",
            unicode_str_unicode_str_suite_name, expected_codepoint_idx, result_idx);
    return false;
  }
  byte_array_free(&expected);
  return true;
}

static bool test_code_point_cmp_equal() {
  color_log(LOG_COLOR_CYAN, "test_code_point_cmp_equal\n");
  code_point_t s1[] = {'h', 'e', 'l', 'l', 'o', 0};
  code_point_t s2[] = {'h', 'e', 'l', 'l', 'o', 0};
  int result = code_point_cmp(s1, s2, 5);
  if (result != 0) {
    color_log(LOG_COLOR_RED, "%s: equal strings should return 0, got %d\n",
              unicode_str_unicode_str_suite_name, result);
    return false;
  }
  return true;
}

static bool test_code_point_cmp_less() {
  color_log(LOG_COLOR_CYAN, "test_code_point_cmp_less\n");
  code_point_t s1[] = {'a', 'p', 'p', 'l', 'e', 0};
  code_point_t s2[] = {'b', 'a', 'n', 'a', 'n', 'a', 0};
  int result = code_point_cmp(s1, s2, 5);
  if (result >= 0) {
    color_log(LOG_COLOR_RED, "%s: \"apple\" < \"banana\" should return negative, got %d\n",
              unicode_str_unicode_str_suite_name, result);
    return false;
  }
  return true;
}

static bool test_code_point_cmp_greater() {
  color_log(LOG_COLOR_CYAN, "test_code_point_cmp_greater\n");
  code_point_t s1[] = {'z', 'e', 'b', 'r', 'a', 0};
  code_point_t s2[] = {'a', 'p', 'p', 'l', 'e', 0};
  int result = code_point_cmp(s1, s2, 5);
  if (result <= 0) {
    color_log(LOG_COLOR_RED, "%s: \"zebra\" > \"apple\" should return positive, got %d\n",
              unicode_str_unicode_str_suite_name, result);
    return false;
  }
  return true;
}

static bool test_code_point_cmp_n_zero() {
  color_log(LOG_COLOR_CYAN, "test_code_point_cmp_n_zero\n");
  code_point_t s1[] = {'h', 'e', 'l', 'l', 'o', 0};
  code_point_t s2[] = {'a', 'n', 'y', 't', 'h', 'i', 'n', 'g', 0};
  int result = code_point_cmp(s1, s2, 0);
  if (result != 0) {
    color_log(LOG_COLOR_RED, "%s: n=0 should return 0, got %d\n",
              unicode_str_unicode_str_suite_name, result);
    return false;
  }
  return true;
}

static bool test_code_point_cmp_partial() {
  color_log(LOG_COLOR_CYAN, "test_code_point_cmp_partial\n");
  code_point_t s1[] = {'h', 'e', 'l', 'l', 'o', 0};
  code_point_t s2[] = {'h', 'e', 'l', 'l', 'x', 0};
  int result = code_point_cmp(s1, s2, 4);
  if (result != 0) {
    color_log(LOG_COLOR_RED, "%s: first 4 chars equal should return 0, got %d\n",
              unicode_str_unicode_str_suite_name, result);
    return false;
  }
  return true;
}

static bool test_code_point_cmp_null_pointers() {
  color_log(LOG_COLOR_CYAN, "test_code_point_cmp_null_pointers\n");
  code_point_t s1[] = {'t', 'e', 's', 't', 0};
  int result = code_point_cmp(NULL, s1, 5);
  if (result != 0) {
    color_log(LOG_COLOR_RED, "%s: NULL s1 should return 0, got %d\n",
              unicode_str_unicode_str_suite_name, result);
    return false;
  }
  result = code_point_cmp(s1, NULL, 5);
  if (result != 0) {
    color_log(LOG_COLOR_RED, "%s: NULL s2 should return 0, got %d\n",
              unicode_str_unicode_str_suite_name, result);
    return false;
  }
  return true;
}

static bool test_code_point_cmp_different_lengths() {
  color_log(LOG_COLOR_CYAN, "test_code_point_cmp_different_lengths\n");
  code_point_t s1[] = {'h', 'e', 'l', 'l', 0};
  code_point_t s2[] = {'h', 'e', 'l', 'l', 'o', 0};
  int result = code_point_cmp(s1, s2, 10);
  if (result >= 0) {
    color_log(LOG_COLOR_RED, "%s: \"hell\" < \"hello\" should return negative, got %d\n",
              unicode_str_unicode_str_suite_name, result);
    return false;
  }
  return true;
}

static bool test_codepoint_idx_from_byte_idx_char() {
  color_log(LOG_COLOR_CYAN, "test_codepoint_idx_from_byte_idx_char\n");
  const char *expected = "Я был когда-то странной";
  const size_t test_byte_idx = 8;
  const size_t expected_codepoint_idx = 5;
  const size_t result_idx = codepoint_idx_from_byte_idx_char(expected, strlen(expected), test_byte_idx);
  if (result_idx != expected_codepoint_idx) {
    color_log(LOG_COLOR_RED, "%s: codepoint index was not correct -- expected:%lu got:%lu.\n",
            unicode_str_unicode_str_suite_name, expected_codepoint_idx, result_idx);
    return false;
  }
  return true;
}

static bool test_unicode_str_set_char() {
  color_log(LOG_COLOR_CYAN, "test_unicode_str_set_char\n");
  const char *test_str = "test value";
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set_char(local, test_str, strlen(test_str));
  if (result_size != strlen(test_str)) {
    color_log(LOG_COLOR_RED, "%s: result_size mismatch -- %lu != %lu\n",
            unicode_str_unicode_str_suite_name, result_size, strlen(test_str));
    unicode_str_destroy(&local);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    color_log(LOG_COLOR_RED, "%s: unicode_str_get failed\n", unicode_str_unicode_str_suite_name);
    unicode_str_destroy(&local);
    return false;
  }
  if (out == NULL) {
    color_log(LOG_COLOR_RED, "%s: unicode_str_get returned NULL\n", unicode_str_unicode_str_suite_name);
    unicode_str_destroy(&local);
    return false;
  }
  byte_array expected = byte_array_from_str("test value");
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: strings do not match\n", unicode_str_unicode_str_suite_name);
    byte_array_free(&expected);
    unicode_str_destroy(&local);
    return false;
  }
  byte_array_free(&expected);
  unicode_str_destroy(&local);
  return true;
}

static bool test_unicode_str_set_codepoint() {
  color_log(LOG_COLOR_CYAN, "test_unicode_str_set_codepoint\n");
  code_point_t codepoints[] = {'h', 'e', 'l', 'l', 'o'};
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set_codepoint(local, codepoints, 5);
  if (result_size != 5) {
    color_log(LOG_COLOR_RED, "%s: codepoint count mismatch -- %lu != 5\n",
            unicode_str_unicode_str_suite_name, result_size);
    unicode_str_destroy(&local);
    return false;
  }
  size_t len = unicode_str_len(local);
  if (len != 5) {
    color_log(LOG_COLOR_RED, "%s: length should be 5, got %lu\n",
            unicode_str_unicode_str_suite_name, len);
    unicode_str_destroy(&local);
    return false;
  }
  unicode_str_destroy(&local);
  return true;
}

static bool test_unicode_str_append_char() {
  color_log(LOG_COLOR_CYAN, "test_unicode_str_append_char\n");
  const char *test_str = "test value";
  const char *postfix = " -- addition";
  struct unicode_str_t *local = unicode_str_create();
  unicode_str_set_char(local, test_str, strlen(test_str));
  const size_t postfix_result_len = unicode_str_append_char(local, postfix, strlen(postfix));
  if (postfix_result_len != strlen(postfix)) {
    color_log(LOG_COLOR_RED, "%s: append char failed to write correct bytes\n",
            unicode_str_unicode_str_suite_name);
    unicode_str_destroy(&local);
    return false;
  }
  const byte_array *out = NULL;
  unicode_str_get(local, &out);
  byte_array expected = byte_array_from_str("test value -- addition");
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: appended string mismatch\n", unicode_str_unicode_str_suite_name);
    byte_array_free(&expected);
    unicode_str_destroy(&local);
    return false;
  }
  byte_array_free(&expected);
  unicode_str_destroy(&local);
  return true;
}

static bool test_unicode_str_insert_at_char() {
  color_log(LOG_COLOR_CYAN, "test_unicode_str_insert_at_char\n");
  const char *test_str = "test value addition";
  const char *infix = " --";
  struct unicode_str_t *local = unicode_str_create();
  unicode_str_set_char(local, test_str, strlen(test_str));
  const size_t result_len = unicode_str_insert_at_char(local, infix, strlen(infix), 10);
  if (result_len != strlen(infix)) {
    color_log(LOG_COLOR_RED, "%s: insert at char failed\n", unicode_str_unicode_str_suite_name);
    unicode_str_destroy(&local);
    return false;
  }
  const byte_array *out = NULL;
  unicode_str_get(local, &out);
  byte_array expected = byte_array_from_str("test value -- addition");
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: inserted string mismatch\n", unicode_str_unicode_str_suite_name);
    byte_array_free(&expected);
    unicode_str_destroy(&local);
    return false;
  }
  byte_array_free(&expected);
  unicode_str_destroy(&local);
  return true;
}

static bool test_unicode_str_insert_at_codepoint() {
  color_log(LOG_COLOR_CYAN, "test_unicode_str_insert_at_codepoint\n");
  const char *test_str = "test value";
  struct unicode_str_t *local = unicode_str_create();
  unicode_str_set_char(local, test_str, strlen(test_str));
  bool result = unicode_str_insert_at_codepoint(local, 'X', 5);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: insert at codepoint failed\n", unicode_str_unicode_str_suite_name);
    unicode_str_destroy(&local);
    return false;
  }
  const byte_array *out = NULL;
  unicode_str_get(local, &out);
  byte_array expected = byte_array_from_str("test Xvalue");
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: inserted codepoint string mismatch\n", unicode_str_unicode_str_suite_name);
    byte_array_free(&expected);
    unicode_str_destroy(&local);
    return false;
  }
  byte_array_free(&expected);
  unicode_str_destroy(&local);
  return true;
}

static bool test_unicode_str_to_lower() {
  color_log(LOG_COLOR_CYAN, "test_unicode_str_to_lower\n");
  const char *test_str = "HELLO World";
  struct unicode_str_t *local = unicode_str_create();
  unicode_str_set_char(local, test_str, strlen(test_str));
  struct unicode_str_t *lower = unicode_str_to_lower(local);
  if (lower == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_lower returned NULL\n", unicode_str_unicode_str_suite_name);
    unicode_str_destroy(&local);
    return false;
  }
  const byte_array *out = NULL;
  unicode_str_get(lower, &out);
  byte_array expected = byte_array_from_str("hello world");
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: lowercase string mismatch\n", unicode_str_unicode_str_suite_name);
    byte_array_free(&expected);
    unicode_str_destroy(&lower);
    unicode_str_destroy(&local);
    return false;
  }
  byte_array_free(&expected);
  unicode_str_destroy(&lower);
  unicode_str_destroy(&local);
  return true;
}

static bool test_unicode_str_to_upper() {
  color_log(LOG_COLOR_CYAN, "test_unicode_str_to_upper\n");
  const char *test_str = "hello World";
  struct unicode_str_t *local = unicode_str_create();
  unicode_str_set_char(local, test_str, strlen(test_str));
  struct unicode_str_t *upper = unicode_str_to_upper(local);
  if (upper == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_upper returned NULL\n", unicode_str_unicode_str_suite_name);
    unicode_str_destroy(&local);
    return false;
  }
  const byte_array *out = NULL;
  unicode_str_get(upper, &out);
  byte_array expected = byte_array_from_str("HELLO WORLD");
  if (!compare_byte_arrays(expected, *out)) {
    color_log(LOG_COLOR_RED, "%s: uppercase string mismatch\n", unicode_str_unicode_str_suite_name);
    byte_array_free(&expected);
    unicode_str_destroy(&upper);
    unicode_str_destroy(&local);
    return false;
  }
  byte_array_free(&expected);
  unicode_str_destroy(&upper);
  unicode_str_destroy(&local);
  return true;
}

static bool test_unicode_str_to_cstr() {
  color_log(LOG_COLOR_CYAN, "test_unicode_str_to_cstr\n");
  const char *test_str = "test value";
  struct unicode_str_t *local = unicode_str_create();
  unicode_str_set_char(local, test_str, strlen(test_str));
  char *cstr = unicode_str_to_cstr(local);
  if (cstr == NULL) {
    color_log(LOG_COLOR_RED, "%s: to_cstr returned NULL\n", unicode_str_unicode_str_suite_name);
    unicode_str_destroy(&local);
    return false;
  }
  if (strcmp(cstr, test_str) != 0) {
    color_log(LOG_COLOR_RED, "%s: cstr mismatch -- expected:%s got:%s\n",
            unicode_str_unicode_str_suite_name, test_str, cstr);
    free(cstr);
    unicode_str_destroy(&local);
    return false;
  }
  free(cstr);
  unicode_str_destroy(&local);
  return true;
}

static void unicode_str_tests() {
  int failures = 0;

  if (!unicode_str_create_test()) {
    color_log(LOG_COLOR_RED, "unicode string create test failed.\n");
    failures++;
  }
  if (!unicode_str_set_and_get_test()) {
    color_log(LOG_COLOR_RED, "unicode_str_set_and_get_test failed\n");
    failures++;
  }
  if (!unicode_str_append_tests()) {
    color_log(LOG_COLOR_RED, "unicode_str_append_tests failed.\n");
    failures++;
  }
  if (!unicode_str_insert_at_tests()) {
    color_log(LOG_COLOR_RED, "unicode_str_insert_at_tests failed.\n");
    failures++;
  }
  if (!unicode_str_remove_range_tests()) {
    color_log(LOG_COLOR_RED, "unicode_str_remove_range_tests failed.\n");
    failures++;
  }
  if (!unicode_str_len_tests()) {
    color_log(LOG_COLOR_RED, "unicode_str_len_tests failed.\n");
    failures++;
  }
  if (!unicode_str_byte_len_tests()) {
    color_log(LOG_COLOR_RED, "unicode_str_byte_len_tests failed.\n");
    failures++;
  }
  if (!unicode_str_codepoint_at_tests()) {
    color_log(LOG_COLOR_RED, "unicode_str_codepoint_at_tests failed.\n");
    failures++;
  }
  if (!unicode_str_get_range_tests()) {
    color_log(LOG_COLOR_RED, "unicode_str_get_range_tests failed.\n");
    failures++;
  }
  if (!codepoint_idx_from_byte_idx_tests()) {
    color_log(LOG_COLOR_RED, "codepoint_idx_from_byte_idx_tests failed.\n");
    failures++;
  }
  if (!test_code_point_cmp_equal()) {
    color_log(LOG_COLOR_RED, "test_code_point_cmp_equal failed.\n");
    failures++;
  }
  if (!test_code_point_cmp_less()) {
    color_log(LOG_COLOR_RED, "test_code_point_cmp_less failed.\n");
    failures++;
  }
  if (!test_code_point_cmp_greater()) {
    color_log(LOG_COLOR_RED, "test_code_point_cmp_greater failed.\n");
    failures++;
  }
  if (!test_code_point_cmp_n_zero()) {
    color_log(LOG_COLOR_RED, "test_code_point_cmp_n_zero failed.\n");
    failures++;
  }
  if (!test_code_point_cmp_partial()) {
    color_log(LOG_COLOR_RED, "test_code_point_cmp_partial failed.\n");
    failures++;
  }
  if (!test_code_point_cmp_null_pointers()) {
    color_log(LOG_COLOR_RED, "test_code_point_cmp_null_pointers failed.\n");
    failures++;
  }
  if (!test_code_point_cmp_different_lengths()) {
    color_log(LOG_COLOR_RED, "test_code_point_cmp_different_lengths failed.\n");
    failures++;
  }
  if (!test_codepoint_idx_from_byte_idx_char()) {
    color_log(LOG_COLOR_RED, "test_codepoint_idx_from_byte_idx_char failed.\n");
    failures++;
  }
  if (!test_unicode_str_set_char()) {
    color_log(LOG_COLOR_RED, "test_unicode_str_set_char failed.\n");
    failures++;
  }
  if (!test_unicode_str_set_codepoint()) {
    color_log(LOG_COLOR_RED, "test_unicode_str_set_codepoint failed.\n");
    failures++;
  }
  if (!test_unicode_str_append_char()) {
    color_log(LOG_COLOR_RED, "test_unicode_str_append_char failed.\n");
    failures++;
  }
  if (!test_unicode_str_insert_at_char()) {
    color_log(LOG_COLOR_RED, "test_unicode_str_insert_at_char failed.\n");
    failures++;
  }
  if (!test_unicode_str_insert_at_codepoint()) {
    color_log(LOG_COLOR_RED, "test_unicode_str_insert_at_codepoint failed.\n");
    failures++;
  }
  if (!test_unicode_str_to_lower()) {
    color_log(LOG_COLOR_RED, "test_unicode_str_to_lower failed.\n");
    failures++;
  }
  if (!test_unicode_str_to_upper()) {
    color_log(LOG_COLOR_RED, "test_unicode_str_to_upper failed.\n");
    failures++;
  }
  if (!test_unicode_str_to_cstr()) {
    color_log(LOG_COLOR_RED, "test_unicode_str_to_cstr failed.\n");
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All unicode_str tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d unicode_str tests failed\n", failures);
  }
}
