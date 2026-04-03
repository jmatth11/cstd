#include "log.h"
#include "magic.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static const char *magic_suite_name = "magic";

static bool test_cstd_freep_fn() {
  color_log(LOG_COLOR_CYAN, "test_cstd_freep_fn\n");
  void *ptr = malloc(100);
  if (ptr == NULL) {
    color_log(LOG_COLOR_RED, "%s: malloc failed\n", magic_suite_name);
    return false;
  }

  cstd_freep_fn(&ptr);
  if (ptr != NULL) {
    color_log(LOG_COLOR_RED, "%s: pointer should be NULL after free\n", magic_suite_name);
    return false;
  }

  return true;
}

static bool test_cstd_freep_fn_null() {
  color_log(LOG_COLOR_CYAN, "test_cstd_freep_fn_null\n");
  void *ptr = NULL;
  cstd_freep_fn(&ptr);
  if (ptr != NULL) {
    color_log(LOG_COLOR_RED, "%s: NULL pointer should remain NULL\n", magic_suite_name);
    return false;
  }
  return true;
}

static bool test_cstd_freec_fn() {
  color_log(LOG_COLOR_CYAN, "test_cstd_freec_fn\n");
  char *ptr = malloc(100);
  if (ptr == NULL) {
    color_log(LOG_COLOR_RED, "%s: malloc failed\n", magic_suite_name);
    return false;
  }

  cstd_freec_fn(&ptr);
  if (ptr != NULL) {
    color_log(LOG_COLOR_RED, "%s: char pointer should be NULL after free\n", magic_suite_name);
    return false;
  }

  return true;
}

static bool test_cstd_freei_fn() {
  color_log(LOG_COLOR_CYAN, "test_cstd_freei_fn\n");
  int *ptr = malloc(sizeof(int) * 10);
  if (ptr == NULL) {
    color_log(LOG_COLOR_RED, "%s: malloc failed\n", magic_suite_name);
    return false;
  }

  cstd_freei_fn(&ptr);
  if (ptr != NULL) {
    color_log(LOG_COLOR_RED, "%s: int pointer should be NULL after free\n", magic_suite_name);
    return false;
  }

  return true;
}

static bool test_cstd_freed_fn() {
  color_log(LOG_COLOR_CYAN, "test_cstd_freed_fn\n");
  double *ptr = malloc(sizeof(double) * 10);
  if (ptr == NULL) {
    color_log(LOG_COLOR_RED, "%s: malloc failed\n", magic_suite_name);
    return false;
  }

  cstd_freed_fn(&ptr);
  if (ptr != NULL) {
    color_log(LOG_COLOR_RED, "%s: double pointer should be NULL after free\n", magic_suite_name);
    return false;
  }

  return true;
}

static bool test_cstd_freef_fn() {
  color_log(LOG_COLOR_CYAN, "test_cstd_freef_fn\n");
  float *ptr = malloc(sizeof(float) * 10);
  if (ptr == NULL) {
    color_log(LOG_COLOR_RED, "%s: malloc failed\n", magic_suite_name);
    return false;
  }

  cstd_freef_fn(&ptr);
  if (ptr != NULL) {
    color_log(LOG_COLOR_RED, "%s: float pointer should be NULL after free\n", magic_suite_name);
    return false;
  }

  return true;
}

static void magic_tests() {
  int failures = 0;

  if (!test_cstd_freep_fn()) {
    color_log(LOG_COLOR_RED, "%s: test_cstd_freep_fn failed\n", magic_suite_name);
    failures++;
  }
  if (!test_cstd_freep_fn_null()) {
    color_log(LOG_COLOR_RED, "%s: test_cstd_freep_fn_null failed\n", magic_suite_name);
    failures++;
  }
  if (!test_cstd_freec_fn()) {
    color_log(LOG_COLOR_RED, "%s: test_cstd_freec_fn failed\n", magic_suite_name);
    failures++;
  }
  if (!test_cstd_freei_fn()) {
    color_log(LOG_COLOR_RED, "%s: test_cstd_freei_fn failed\n", magic_suite_name);
    failures++;
  }
  if (!test_cstd_freed_fn()) {
    color_log(LOG_COLOR_RED, "%s: test_cstd_freed_fn failed\n", magic_suite_name);
    failures++;
  }
  if (!test_cstd_freef_fn()) {
    color_log(LOG_COLOR_RED, "%s: test_cstd_freef_fn failed\n", magic_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All magic tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d magic tests failed\n", failures);
  }
}
