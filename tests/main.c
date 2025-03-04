#include <stdio.h>
#include "unicode_str_tests.c"

int main(void) {
  printf("starting tests\n");

  printf("starting unicode_str tests\n");
  unicode_str_tests();

  printf("end tests\n");
  return 0;
}
