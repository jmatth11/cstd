#include <stdio.h>
#include "string_ops_tests.c"
#include "unicode_str_tests.c"
#include "arena_tests.c"
#include "array_template_tests.c"

int main(void) {
  printf("starting tests\n");

  printf("starting string_ops tests\n");
  string_ops_tests();

  printf("starting unicode_str tests\n");
  unicode_str_tests();

  printf("starting arena_alloc tests\n");
  arena_alloc_tests();

  printf("starting array_template tests\n");
  array_template_tests();

  printf("end tests\n");
  return 0;
}
