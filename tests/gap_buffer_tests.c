static const char *gap_buffer_suite_name = "gap_buffer";

#include "gap_buffer.h"
#include "unicode_str.h"
#include "log.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool test_gap_buffer_init_basic() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_init_basic\n");
  struct gap_buffer_t gb;
  bool result = gap_buffer_init(&gb, 16);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: gap_buffer_init returned false\n", gap_buffer_suite_name);
    return false;
  }
  if (gb.cap != 16) {
    color_log(LOG_COLOR_RED, "%s: capacity mismatch - expected 16, got %zu\n", gap_buffer_suite_name, gb.cap);
    gap_buffer_free(&gb);
    return false;
  }
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_init_zero_size() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_init_zero_size\n");
  struct gap_buffer_t gb;
  bool result = gap_buffer_init(&gb, 0);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: gap_buffer_init with 0 returned false\n", gap_buffer_suite_name);
    return false;
  }
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_insert_basic() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_insert_basic\n");
  struct gap_buffer_t gb;
  if (!gap_buffer_init(&gb, 16)) {
    color_log(LOG_COLOR_RED, "%s: init failed\n", gap_buffer_suite_name);
    return false;
  }
  
  code_point_t c = 'a';
  bool result = gap_buffer_insert(&gb, c);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: gap_buffer_insert returned false\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  size_t len = gap_buffer_get_len(&gb);
  if (len != 1) {
    color_log(LOG_COLOR_RED, "%s: length should be 1, got %zu\n", gap_buffer_suite_name, len);
    gap_buffer_free(&gb);
    return false;
  }
  
  code_point_t out = 0;
  gap_buffer_get_char(&gb, 0, &out);
  if (out != 'a') {
    color_log(LOG_COLOR_RED, "%s: char mismatch - expected 'a', got %u\n", gap_buffer_suite_name, out);
    gap_buffer_free(&gb);
    return false;
  }
  
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_insert_multiple() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_insert_multiple\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 16);
  
  gap_buffer_insert(&gb, 'h');
  gap_buffer_insert(&gb, 'e');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'o');
  
  size_t len = gap_buffer_get_len(&gb);
  if (len != 5) {
    color_log(LOG_COLOR_RED, "%s: length should be 5, got %zu\n", gap_buffer_suite_name, len);
    gap_buffer_free(&gb);
    return false;
  }
  
  code_point_t *str = gap_buffer_get_str(&gb);
  if (str == NULL) {
    color_log(LOG_COLOR_RED, "%s: get_str returned NULL\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  if (str[0] != (code_point_t)'h' || str[1] != (code_point_t)'e' || 
      str[2] != (code_point_t)'l' || str[3] != (code_point_t)'l' || str[4] != (code_point_t)'o') {
    color_log(LOG_COLOR_RED, "%s: string content mismatch - got %u,%u,%u,%u,%u\n", 
              gap_buffer_suite_name, str[0], str[1], str[2], str[3], str[4]);
    free(str);
    gap_buffer_free(&gb);
    return false;
  }
  
  free(str);
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_move_cursor() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_move_cursor\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 16);
  
  gap_buffer_insert(&gb, 'a');
  gap_buffer_insert(&gb, 'b');
  gap_buffer_insert(&gb, 'c');
  
  bool result = gap_buffer_move_cursor(&gb, 1);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: move_cursor returned false\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  gap_buffer_insert(&gb, 'X');
  
  code_point_t *str = gap_buffer_get_str(&gb);
  if (str == NULL) {
    color_log(LOG_COLOR_RED, "%s: get_str returned NULL after cursor move\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  if (str[0] != (code_point_t)'a' || str[1] != (code_point_t)'X' || 
      str[2] != (code_point_t)'b' || str[3] != (code_point_t)'c') {
    color_log(LOG_COLOR_RED, "%s: expected aXbc, got %u,%u,%u,%u\n", 
              gap_buffer_suite_name, str[0], str[1], str[2], str[3]);
    free(str);
    gap_buffer_free(&gb);
    return false;
  }
  
  free(str);
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_delete() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_delete\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 16);
  
  gap_buffer_insert(&gb, 'h');
  gap_buffer_insert(&gb, 'e');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'o');
  
  bool result = gap_buffer_delete(&gb);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: delete returned false\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  size_t len = gap_buffer_get_len(&gb);
  if (len != 4) {
    color_log(LOG_COLOR_RED, "%s: length after delete should be 4, got %zu\n", gap_buffer_suite_name, len);
    gap_buffer_free(&gb);
    return false;
  }
  
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_delete_seq() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_delete_seq\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 16);
  
  gap_buffer_insert(&gb, 'h');
  gap_buffer_insert(&gb, 'e');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'o');
  
  bool result = gap_buffer_delete_seq(&gb, 3);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: delete_seq returned false\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  size_t len = gap_buffer_get_len(&gb);
  if (len != 2) {
    color_log(LOG_COLOR_RED, "%s: length after delete_seq should be 2, got %zu\n", gap_buffer_suite_name, len);
    gap_buffer_free(&gb);
    return false;
  }
  
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_get_str() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_get_str\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 16);
  
  gap_buffer_insert(&gb, 't');
  gap_buffer_insert(&gb, 'e');
  gap_buffer_insert(&gb, 's');
  gap_buffer_insert(&gb, 't');
  
  code_point_t *str = gap_buffer_get_str(&gb);
  if (str == NULL) {
    color_log(LOG_COLOR_RED, "%s: get_str returned NULL\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  if (str[0] != (code_point_t)'t' || str[1] != (code_point_t)'e' || 
      str[2] != (code_point_t)'s' || str[3] != (code_point_t)'t') {
    color_log(LOG_COLOR_RED, "%s: expected test, got %u,%u,%u,%u\n", 
              gap_buffer_suite_name, str[0], str[1], str[2], str[3]);
    free(str);
    gap_buffer_free(&gb);
    return false;
  }
  
  free(str);
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_get_str_empty() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_get_str_empty\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 16);
  
  code_point_t *str = gap_buffer_get_str(&gb);
  if (str != NULL) {
    color_log(LOG_COLOR_RED, "%s: get_str should return NULL for empty buffer\n", gap_buffer_suite_name);
    free(str);
    gap_buffer_free(&gb);
    return false;
  }
  
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_get_len_empty() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_get_len_empty\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 16);
  
  size_t len = gap_buffer_get_len(&gb);
  if (len != 0) {
    color_log(LOG_COLOR_RED, "%s: empty buffer length should be 0, got %zu\n", gap_buffer_suite_name, len);
    gap_buffer_free(&gb);
    return false;
  }
  
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_insert_word() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_insert_word\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 32);
  
  code_point_t word[] = {'h', 'e', 'l', 'l', 'o'};
  bool result = gap_buffer_insert_word(&gb, 0, word, 5);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: insert_word returned false\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  size_t len = gap_buffer_get_len(&gb);
  if (len != 5) {
    color_log(LOG_COLOR_RED, "%s: length should be 5, got %zu\n", gap_buffer_suite_name, len);
    gap_buffer_free(&gb);
    return false;
  }
  
  code_point_t *str = gap_buffer_get_str(&gb);
  if (str[0] != (code_point_t)'h' || str[1] != (code_point_t)'e' || 
      str[2] != (code_point_t)'l' || str[3] != (code_point_t)'l' || str[4] != (code_point_t)'o') {
    color_log(LOG_COLOR_RED, "%s: expected hello, got %u,%u,%u,%u,%u\n", 
              gap_buffer_suite_name, str[0], str[1], str[2], str[3], str[4]);
    free(str);
    gap_buffer_free(&gb);
    return false;
  }
  
  free(str);
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_insert_word_at_position() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_insert_word_at_position\n");
  struct gap_buffer_t gb;
  gap_buffer_init(&gb, 32);
  
  code_point_t word1[] = {'h', 'e', 'l', 'l', 'o'};
  gap_buffer_insert_word(&gb, 0, word1, 5);
  
  code_point_t word2[] = {' ', 'w', 'o', 'r', 'l', 'd'};
  bool result = gap_buffer_insert_word(&gb, 5, word2, 6);
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: insert_word at pos returned false\n", gap_buffer_suite_name);
    gap_buffer_free(&gb);
    return false;
  }
  
  code_point_t *str = gap_buffer_get_str(&gb);
  size_t len = gap_buffer_get_len(&gb);
  code_point_t expected[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
  size_t exp_len = sizeof(expected) / sizeof(expected[0]);
  if (len != exp_len) {
    color_log(LOG_COLOR_RED, "%s: length mismatch - expected %zu, got %zu\n", 
              gap_buffer_suite_name, exp_len, len);
    free(str);
    gap_buffer_free(&gb);
    return false;
  }
  for (size_t i = 0; i < exp_len; i++) {
    if (str[i] != expected[i]) {
      color_log(LOG_COLOR_RED, "%s: hello world mismatch at index %zu - expected %u, got %u\n", 
                gap_buffer_suite_name, i, expected[i], str[i]);
      free(str);
      gap_buffer_free(&gb);
      return false;
    }
  }
  
  free(str);
  gap_buffer_free(&gb);
  return true;
}

static bool test_gap_buffer_free_null() {
  color_log(LOG_COLOR_CYAN, "test_gap_buffer_free_null\n");
  gap_buffer_free(NULL);
  return true;
}

static void gap_buffer_tests() {
  int failures = 0;

  if (!test_gap_buffer_init_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_init_basic failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_init_zero_size()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_init_zero_size failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_insert_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_insert_basic failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_insert_multiple()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_insert_multiple failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_move_cursor()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_move_cursor failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_delete()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_delete failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_delete_seq()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_delete_seq failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_get_str()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_get_str failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_get_str_empty()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_get_str_empty failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_get_len_empty()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_get_len_empty failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_insert_word()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_insert_word failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_insert_word_at_position()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_insert_word_at_position failed\n", gap_buffer_suite_name);
    failures++;
  }
  if (!test_gap_buffer_free_null()) {
    color_log(LOG_COLOR_RED, "%s: test_gap_buffer_free_null failed\n", gap_buffer_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All gap_buffer tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d gap_buffer tests failed\n", failures);
  }
}
