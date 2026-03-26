#include <stdio.h>
#include "log.h"
#include "string_ops_tests.c"
#include "unicode_str_tests.c"
#include "arena_tests.c"
#include "array_template_tests.c"
#include "base_str_tests.c"
#include "crypt_tests.c"
#include "file_ops_tests.c"
#include "gap_buffer_tests.c"
#include "hash_map_tests.c"
#include "linked_list_tests.c"

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

  color_log(LOG_COLOR_CYAN, "starting crypt tests\n");
  crypt_tests();

  color_log(LOG_COLOR_CYAN, "starting file_ops tests\n");
  file_ops_tests();

  color_log(LOG_COLOR_CYAN, "starting gap_buffer tests\n");
  gap_buffer_tests();

  color_log(LOG_COLOR_CYAN, "starting hash_map tests\n");
  hash_map_tests();

  color_log(LOG_COLOR_CYAN, "starting linked_list tests\n");
  linked_list_tests();

  color_log(LOG_COLOR_GREEN, "end tests\n");
  return 0;
}

