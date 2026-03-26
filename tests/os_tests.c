#include "log.h"
#include "os.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static const char *os_suite_name = "os";

static bool test_is_little_endian() {
  color_log(LOG_COLOR_CYAN, "test_is_little_endian start\n");
  bool result = is_little_endian();
  color_log(LOG_COLOR_CYAN, "is_little_endian returned: %s\n", result ? "true" : "false");

  bool result2 = is_little_endian();
  if (result != result2) {
    color_log(LOG_COLOR_RED, "%s: is_little_endian returned inconsistent result\n", os_suite_name);
    return false;
  }

  return true;
}

static void os_tests() {
  int failures = 0;

  if (!test_is_little_endian()) {
    color_log(LOG_COLOR_RED, "%s: test_is_little_endian failed\n", os_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All os tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d os tests failed\n", failures);
  }
}
