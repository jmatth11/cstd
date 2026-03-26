static const char *crypt_suite_name = "crypt";

#include "crypt.h"
#include "log.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool test_hash_from_str_basic() {
  color_log(LOG_COLOR_CYAN, "test_hash_from_str_basic start\n");
  unsigned long hash = hash_from_str("hello");
  if (hash == 0) {
    color_log(LOG_COLOR_RED, "%s: hash returned 0\n", crypt_suite_name);
    return false;
  }
  return true;
}

static bool test_hash_from_str_empty() {
  color_log(LOG_COLOR_CYAN, "test_hash_from_str_empty start\n");
  unsigned long hash = hash_from_str("");
  if (hash != 5381) {
    color_log(LOG_COLOR_RED, "%s: empty string hash should be 5381, got %lu\n", crypt_suite_name, hash);
    return false;
  }
  return true;
}

static bool test_hash_from_str_known_values() {
  color_log(LOG_COLOR_CYAN, "test_hash_from_str_known_values start\n");
  unsigned long hash = hash_from_str("hello");
  unsigned long expected = 210714636441;
  if (hash != expected) {
    color_log(LOG_COLOR_RED, "%s: \"hello\" hash expected %lu, got %lu\n", crypt_suite_name, expected, hash);
    return false;
  }

  hash = hash_from_str("test");
  expected = 6385723493;
  if (hash != expected) {
    color_log(LOG_COLOR_RED, "%s: \"test\" hash expected %lu, got %lu\n", crypt_suite_name, expected, hash);
    return false;
  }

  hash = hash_from_str("a");
  expected = 177670;
  if (hash != expected) {
    color_log(LOG_COLOR_RED, "%s: \"a\" hash expected %lu, got %lu\n", crypt_suite_name, expected, hash);
    return false;
  }

  hash = hash_from_str("aa");
  expected = 5863207;
  if (hash != expected) {
    color_log(LOG_COLOR_RED, "%s: \"aa\" hash expected %lu, got %lu\n", crypt_suite_name, expected, hash);
    return false;
  }

  return true;
}

static bool test_hash_from_str_different_strings() {
  color_log(LOG_COLOR_CYAN, "test_hash_from_str_different_strings start\n");
  unsigned long hash1 = hash_from_str("abc");
  unsigned long hash2 = hash_from_str("def");
  if (hash1 == hash2) {
    color_log(LOG_COLOR_RED, "%s: different strings should produce different hashes\n", crypt_suite_name);
    return false;
  }
  return true;
}

static bool test_hash_from_str_special_chars() {
  color_log(LOG_COLOR_CYAN, "test_hash_from_str_special_chars start\n");
  unsigned long hash = hash_from_str("hello world");
  if (hash == 0) {
    color_log(LOG_COLOR_RED, "%s: hash with space returned 0\n", crypt_suite_name);
    return false;
  }

  hash = hash_from_str("hello\nworld");
  if (hash == 0) {
    color_log(LOG_COLOR_RED, "%s: hash with newline returned 0\n", crypt_suite_name);
    return false;
  }

  hash = hash_from_str("!@#$%^&*()");
  if (hash == 0) {
    color_log(LOG_COLOR_RED, "%s: hash with special chars returned 0\n", crypt_suite_name);
    return false;
  }

  return true;
}

static bool test_hash_from_str_repeatable() {
  color_log(LOG_COLOR_CYAN, "test_hash_from_str_repeatable start\n");
  unsigned long hash1 = hash_from_str("repeatable_test_string");
  unsigned long hash2 = hash_from_str("repeatable_test_string");
  if (hash1 != hash2) {
    color_log(LOG_COLOR_RED, "%s: same string should produce same hash\n", crypt_suite_name);
    return false;
  }
  return true;
}

static bool test_hash_from_str_numbers() {
  color_log(LOG_COLOR_CYAN, "test_hash_from_str_numbers start\n");
  unsigned long hash = hash_from_str("123456789");
  if (hash == 0) {
    color_log(LOG_COLOR_RED, "%s: hash with numbers returned 0\n", crypt_suite_name);
    return false;
  }

  hash = hash_from_str("0");
  if (hash == 0) {
    color_log(LOG_COLOR_RED, "%s: hash with \"0\" returned 0\n", crypt_suite_name);
    return false;
  }

  return true;
}

static void crypt_tests() {
  int failures = 0;

  if (!test_hash_from_str_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_from_str_basic failed\n", crypt_suite_name);
    failures++;
  }
  if (!test_hash_from_str_empty()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_from_str_empty failed\n", crypt_suite_name);
    failures++;
  }
  if (!test_hash_from_str_known_values()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_from_str_known_values failed\n", crypt_suite_name);
    failures++;
  }
  if (!test_hash_from_str_different_strings()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_from_str_different_strings failed\n", crypt_suite_name);
    failures++;
  }
  if (!test_hash_from_str_special_chars()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_from_str_special_chars failed\n", crypt_suite_name);
    failures++;
  }
  if (!test_hash_from_str_repeatable()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_from_str_repeatable failed\n", crypt_suite_name);
    failures++;
  }
  if (!test_hash_from_str_numbers()) {
    color_log(LOG_COLOR_RED, "%s: test_hash_from_str_numbers failed\n", crypt_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All crypt tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d crypt tests failed\n", failures);
  }
}
