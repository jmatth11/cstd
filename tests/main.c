#include "log.h"
#include "log_tests.c"
#include "os_tests.c"
#include "queue_tests.c"
#include "magic_tests.c"
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
  color_log(LOG_COLOR_CYAN, "\n--- starting tests --- \n");

  color_log(LOG_COLOR_CYAN, "\n-- starting log tests ---\n");
  log_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting os tests ---\n");
  os_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting queue tests ---\n");
  queue_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting magic tests ---\n");
  magic_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting string_ops tests ---\n");
  string_ops_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting unicode_str tests ---\n");
  unicode_str_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting arena_alloc tests ---\n");
  arena_alloc_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting array_template tests ---\n");
  array_template_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting base_str tests ---\n");
  base_str_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting crypt tests ---\n");
  crypt_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting file_ops tests ---\n");
  file_ops_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting gap_buffer tests ---\n");
  gap_buffer_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting hash_map tests ---\n");
  hash_map_tests();

  color_log(LOG_COLOR_CYAN, "\n-- starting linked_list tests ---\n");
  linked_list_tests();

  color_log(LOG_COLOR_GREEN, "\n-- end tests ---\n");
  return 0;
}

