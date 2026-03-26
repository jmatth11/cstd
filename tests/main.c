#include <stdio.h>
#include "log.h"
#include "string_ops_tests.c"
#include "unicode_str_tests.c"
#include "arena_tests.c"
#include "array_template_tests.c"
#include "base_str_tests.c"

int main(void) {
  color_log(LOG_COLOR_CYAN, "starting tests\n");

  color_log(LOG_COLOR_CYAN, "starting string_ops tests\n");
  string_ops_tests();

  color_log(LOG_COLOR_CYAN, "starting unicode_str tests\n");
  unicode_str_tests();

  color_log(LOG_COLOR_CYAN, "starting arena_alloc tests\n");
  arena_alloc_tests();

  color_log(LOG_COLOR_CYAN, "starting array_template tests\n");
  array_template_tests();

  color_log(LOG_COLOR_CYAN, "starting base_str tests\n");
  base_str_tests();

  color_log(LOG_COLOR_GREEN, "end tests\n");
  return 0;
}
