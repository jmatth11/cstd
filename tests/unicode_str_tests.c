#include "unicode_str.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "helpers.c"

const char *suite_name = "unicode_str";

static bool unicode_str_create_test() {
  struct unicode_str_t *local = unicode_str_create();
  bool result = local != NULL;
  unicode_str_destroy(local);
  return result;
}

static bool unicode_str_set_and_get_test() {
  printf("unicode_str_set_and_get_test start\n");
  byte_array test_str = byte_array_from_str("test value");
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    fprintf(stderr, "%s: result_size != test_str.len -- %lu != %lu\n",
            suite_name, result_size, test_str.len);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    fprintf(stderr, "%s: unicode string get failed\n", suite_name);
    return false;
  }
  if (out == NULL) {
    fprintf(stderr, "%s: unicode string get returned NULL\n", suite_name);
    return false;
  }
  if (!compare_byte_arrays(test_str, *out)) {
    fprintf(stderr, "%s: strings in set_and_get were not the same -- expected:\"%s\" != got:\"%s\"\n",
            suite_name, test_str.byte_data, out->byte_data);
    return false;
  }
  unicode_str_destroy(local);
  byte_array_free(&test_str);
  return true;
}

static bool unicode_str_append_tests() {
  printf("unicode_str_append_tests start\n");
  byte_array expected = byte_array_from_str("test value -- addition");
  byte_array postfix = byte_array_from_str(" -- addition");
  byte_array test_str = byte_array_from_str("test value");
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    fprintf(stderr, "%s: result_size != test_str_len -- %lu != %lu\n",
            suite_name, result_size, test_str.len);
    return false;
  }
  const size_t postfix_result_len =
      unicode_str_append(local, postfix.byte_data, postfix.len);
  if (postfix_result_len != postfix.len) {
    fprintf(stderr,
            "%s: unicode str append failed to write the correct number of "
            "bytes -- expected %lu, got %lu\n",
            suite_name, postfix.len, postfix_result_len);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    fprintf(stderr, "%s: unicode string get failed\n", suite_name);
    return false;
  }
  if (out == NULL) {
    fprintf(stderr, "%s: unicode string get returned NULL\n", suite_name);
    return false;
  }
  if (!compare_byte_arrays(expected, *out)) {
    fprintf(stderr, "%s: strings in append were not the same -- expected:%s != got:%s\n",
            suite_name, expected.byte_data, out->byte_data);
    return false;
  }
  unicode_str_destroy(local);
  byte_array_free(&expected);
  byte_array_free(&postfix);
  byte_array_free(&test_str);
  return true;
}

static bool unicode_str_insert_at_tests() {
  printf("unicode_str_insert_at_tests start\n");
  byte_array expected = byte_array_from_str("test value -- addition");
  byte_array infix = byte_array_from_str(" --");
  byte_array test_str = byte_array_from_str("test value addition");
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    fprintf(stderr, "%s: result_size != test_str_len -- %lu != %lu\n",
            suite_name, result_size, test_str.len);
    return false;
  }
  const size_t infix_result_len =
      unicode_str_insert_at(local, infix.byte_data, infix.len, 10);
  if (infix_result_len != infix.len) {
    fprintf(stderr,
            "%s: unicode str insert_at failed to write the correct number of "
            "bytes -- expected %lu, got %lu\n",
            suite_name, infix.len, infix_result_len);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    fprintf(stderr, "%s: unicode string get failed\n", suite_name);
    return false;
  }
  if (out == NULL) {
    fprintf(stderr, "%s: unicode string get returned NULL\n", suite_name);
    return false;
  }
  if (!compare_byte_arrays(expected, *out)) {
    fprintf(stderr, "%s: strings in insert_at were not the same -- expected:%s != got:%s\n",
            suite_name, expected.byte_data, out->byte_data);
    return false;
  }
  unicode_str_destroy(local);
  byte_array_free(&expected);
  byte_array_free(&infix);
  byte_array_free(&test_str);
  return true;
}

static bool unicode_str_remove_range_tests() {
  printf("unicode_str_remove_range_tests start\n");
  byte_array expected = byte_array_from_str("123789");
  byte_array test_str = byte_array_from_str("123456789");
  const size_t expected_remove_len = 3;
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    fprintf(stderr, "%s: result_size != test_str_len -- %lu != %lu\n",
            suite_name, result_size, test_str.len);
    return false;
  }
  const size_t remove_result_len =
      unicode_str_remove_range(local, 3, expected_remove_len);
  if (remove_result_len != expected_remove_len) {
    fprintf(stderr,
            "%s: unicode str remove_range failed to write the correct number of "
            "bytes -- expected %lu, got %lu\n",
            suite_name, expected_remove_len, remove_result_len);
    return false;
  }
  const byte_array *out = NULL;
  if (!unicode_str_get(local, &out)) {
    fprintf(stderr, "%s: unicode string get failed\n", suite_name);
    return false;
  }
  if (out == NULL) {
    fprintf(stderr, "%s: unicode string get returned NULL\n", suite_name);
    return false;
  }
  if (!compare_byte_arrays(expected, *out)) {
    fprintf(stderr, "%s: strings in remove_range were not the same -- expected:%s != got:%s\n",
            suite_name, expected.byte_data, out->byte_data);
    return false;
  }
  unicode_str_destroy(local);
  byte_array_free(&expected);
  byte_array_free(&test_str);
  return true;
}

static bool unicode_str_len_tests() {
  printf("unicode_str_len_tests start\n");
  byte_array expected = byte_array_from_str("123456");
  const size_t expected_len = 6;
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, expected.byte_data, expected.len);
  if (result_size != expected_len) {
    fprintf(stderr, "%s: expected result_size != expected_len -- %lu != %lu\n",
            suite_name, result_size, expected.len);
    return false;
  }
  const size_t len_result = unicode_str_len(local);
  if (len_result != expected_len) {
    fprintf(stderr, "%s: len_result result_size != expected_len -- %lu != %lu\n",
            suite_name, len_result, expected_len);
    return false;
  }
  byte_array expected_unicode = byte_array_from_str("Д");
  const size_t expected_codepoint_len = 1;
  const size_t expected_byte_len = 2;
  const size_t unicode_result_size = unicode_str_set(local, expected_unicode.byte_data, expected_unicode.len);
  if (unicode_result_size != expected_byte_len) {
    fprintf(stderr, "%s: expected_byte_len result_size != expected_len -- %lu != %lu\n",
            suite_name, result_size, expected_byte_len);
    return false;
  }
  const size_t codepoint_len_result = unicode_str_len(local);
  if (codepoint_len_result != expected_codepoint_len) {
    fprintf(stderr, "%s: codepoint_len_result result_size != expected_len -- %lu != %lu\n",
            suite_name, codepoint_len_result, expected_codepoint_len);
    return false;
  }
  unicode_str_destroy(local);
  byte_array_free(&expected);
  return true;
}

static bool unicode_str_byte_len_tests() {
  printf("unicode_str_byte_len_tests start\n");
  byte_array expected = byte_array_from_str("123456");
  const size_t expected_len = 6;
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, expected.byte_data, expected.len);
  if (result_size != expected_len) {
    fprintf(stderr, "%s: expected result_size != expected_len -- %lu != %lu\n",
            suite_name, result_size, expected_len);
    return false;
  }
  const size_t len_result = unicode_str_byte_len(local);
  if (len_result != expected_len) {
    fprintf(stderr, "%s: len_result result_size != expected_len -- %lu != %lu\n",
            suite_name, len_result, expected_len);
    return false;
  }
  byte_array expected_unicode = byte_array_from_str("Д");
  const size_t expected_unicode_len = 2;
  const size_t unicode_result_size = unicode_str_set(local, expected_unicode.byte_data, expected_unicode.len);
  if (unicode_result_size != expected_unicode_len) {
    fprintf(stderr, "%s: expected_unicode result_size != expected_len -- %lu != %lu\n",
            suite_name, result_size, expected_unicode_len);
    return false;
  }
  const size_t unicode_len_result = unicode_str_byte_len(local);
  if (unicode_len_result != expected_unicode_len) {
    fprintf(stderr, "%s: unicode_len_result result_size != expected_len -- %lu != %lu\n",
            suite_name, unicode_len_result, expected_unicode_len);
    return false;
  }
  unicode_str_destroy(local);
  byte_array_free(&expected);
  return true;
}

static bool unicode_str_codepoint_at_tests() {
  printf("unicode_str_codepoint_at_tests start\n");
  byte_array expected = byte_array_from_str("Я был когда-то странной");
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, expected.byte_data, expected.len);
  if (result_size != expected.len) {
    fprintf(stderr, "%s: expected result_size != expected_len -- %lu != %lu\n",
            suite_name, result_size, expected.len);
    return false;
  }
  code_point_t out = 0;
  if (!unicode_str_codepoint_at(local, 9, &out)) {
    fprintf(stderr, "%s: getting codepoint failed.\n",
            suite_name);
    return false;
  }
  byte_array single_unicode_codepoint = byte_array_from_str("д");
  struct code_point rune = utf8_next(single_unicode_codepoint.byte_data, single_unicode_codepoint.len, 0);
  if (rune.val != out) {
    fprintf(stderr, "%s: Code points did not match expected:%d got:%d.\n",
            suite_name, rune.val, out);
    return false;
  }
  unicode_str_destroy(local);
  byte_array_free(&expected);
  byte_array_free(&single_unicode_codepoint);
  return true;
}

static bool unicode_str_get_range_tests() {
  printf("unicode_str_get_range_tests start\n");
  byte_array test_str = byte_array_from_str("Я был когда-то странной");
  const size_t start_index = 6;
  byte_array expected = byte_array_from_str("когда-то");
  const size_t expected_codepoint_len = 8;
  struct unicode_str_t *local = unicode_str_create();
  const size_t result_size = unicode_str_set(local, test_str.byte_data, test_str.len);
  if (result_size != test_str.len) {
    fprintf(stderr, "%s: expected result_size != expected_len -- %lu != %lu\n",
            suite_name, result_size, test_str.len);
    return false;
  }
  uint8_t *out = NULL;
  if (!unicode_str_get_range(local, start_index, expected_codepoint_len, &out)) {
    fprintf(stderr, "%s: getting range failed.\n",
            suite_name);
    return false;
  }
  if (!compare_byte_array_and_uint8(expected, out)) {
    fprintf(stderr, "%s: strings in get_range were not the same -- expected:\"%s\" != got:\"%s\"\n",
            suite_name, expected.byte_data, out);
    return false;
  }
  free(out);
  unicode_str_destroy(local);
  byte_array_free(&test_str);
  return true;
}

static void unicode_str_tests() {
  if (!unicode_str_create_test()) {
    fprintf(stderr, "unicode string create test failed.\n");
  }
  if (!unicode_str_set_and_get_test()) {
    fprintf(stderr, "unicode_str_set_and_get_test failed\n");
  }
  if (!unicode_str_append_tests()) {
    fprintf(stderr, "unicode_str_append_tests failed.\n");
  }
  if (!unicode_str_insert_at_tests()) {
    fprintf(stderr, "unicode_str_insert_at_tests failed.\n");
  }
  if (!unicode_str_remove_range_tests()) {
    fprintf(stderr, "unicode_str_remove_range_tests failed.\n");
  }
  if (!unicode_str_len_tests()) {
    fprintf(stderr, "unicode_str_len_tests failed.\n");
  }
  if (!unicode_str_byte_len_tests()) {
    fprintf(stderr, "unicode_str_byte_len_tests failed.\n");
  }
  if (!unicode_str_codepoint_at_tests()) {
    fprintf(stderr, "unicode_str_codepoint_at_tests failed.\n");
  }
  if (!unicode_str_get_range_tests()) {
    fprintf(stderr, "unicode_str_get_range_tests failed.\n");
  }
}
