#include "log.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static const char *log_suite_name = "log";

static bool test_info_log() {
  color_log(LOG_COLOR_CYAN, "test_info_log start\n");
  info_log("test info message");
  info_log("test info with value: %d", 42);
  info_log("test info with multiple: %d, %s, %f", 1, "hello", 3.14);
  return true;
}

static bool test_debug_log() {
  color_log(LOG_COLOR_CYAN, "test_debug_log start\n");
  debug_log("test debug message");
  debug_log("test debug with value: %d", 100);
  debug_log("test debug with multiple: %d, %s, %c", 2, "world", 'X');
  return true;
}

static bool test_error_log() {
  color_log(LOG_COLOR_CYAN, "test_error_log start\n");
  error_log("test error message");
  error_log("test error with value: %d", -1);
  error_log("test error with multiple: %s, %lu", "fail", 12345UL);
  return true;
}

static bool test_color_log() {
  color_log(LOG_COLOR_CYAN, "test_color_log start\n");
  color_log(LOG_COLOR_DEFAULT, "default color");
  color_log(LOG_COLOR_RED, "red color");
  color_log(LOG_COLOR_GREEN, "green color");
  color_log(LOG_COLOR_YELLOW, "yellow color");
  color_log(LOG_COLOR_BLUE, "blue color");
  color_log(LOG_COLOR_MAGENTA, "magenta color");
  color_log(LOG_COLOR_CYAN, "cyan color");
  color_log(LOG_COLOR_WHITE, "white color");
  color_log(LOG_COLOR_BRIGHT_RED, "bright red color");
  color_log(LOG_COLOR_BRIGHT_GREEN, "bright green color");
  color_log(LOG_COLOR_BRIGHT_YELLOW, "bright yellow color");
  color_log(LOG_COLOR_BRIGHT_BLUE, "bright blue color");
  color_log(LOG_COLOR_BRIGHT_MAGENTA, "bright magenta color");
  color_log(LOG_COLOR_BRIGHT_CYAN, "bright cyan color");
  color_log(LOG_COLOR_BRIGHT_WHITE, "bright white color");
  return true;
}

static bool test_color_log_with_format() {
  color_log(LOG_COLOR_CYAN, "test_color_log_with_format start\n");
  color_log(LOG_COLOR_GREEN, "formatted: %d", 42);
  color_log(LOG_COLOR_RED, "multi: %d, %s, %f", 100, "test", 2.5);
  color_log(LOG_COLOR_BLUE, "empty string: %s", "");
  color_log(LOG_COLOR_YELLOW, "pointer: %p", (void*)0x1234);
  return true;
}

static void log_tests() {
  int failures = 0;

  if (!test_info_log()) {
    color_log(LOG_COLOR_RED, "%s: test_info_log failed\n", log_suite_name);
    failures++;
  }
  if (!test_debug_log()) {
    color_log(LOG_COLOR_RED, "%s: test_debug_log failed\n", log_suite_name);
    failures++;
  }
  if (!test_error_log()) {
    color_log(LOG_COLOR_RED, "%s: test_error_log failed\n", log_suite_name);
    failures++;
  }
  if (!test_color_log()) {
    color_log(LOG_COLOR_RED, "%s: test_color_log failed\n", log_suite_name);
    failures++;
  }
  if (!test_color_log_with_format()) {
    color_log(LOG_COLOR_RED, "%s: test_color_log_with_format failed\n", log_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All log tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d log tests failed\n", failures);
  }
}
