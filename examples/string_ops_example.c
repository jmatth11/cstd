#include "headers/string_ops.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // ============================================================
  // String duplication
  // ============================================================
  const char *original = "Hello, World!";
  char *dup = str_dup(original, 5);
  printf("Original: %s\n", original);
  printf("Duplicated (len 5): %s\n", dup);
  free(dup);

  // ============================================================
  // Formatted string generation
  // ============================================================
  char *formatted = str_fmt("Name: %s, Age: %d, Score: %.2f", "Alice", 25, 98.5);
  printf("Formatted: %s\n", formatted);
  free(formatted);

  // ============================================================
  // String concatenation
  // ============================================================
  const char *hello = "Hello, ";
  const char *world = "World!";
  size_t out_len = 0;
  char *concated = concat(hello, world, &out_len);
  printf("Concat: %s (len: %zu)\n", concated, out_len);
  free(concated);

  // ============================================================
  // to_str_length - get length of string representation
  // ============================================================
  int i = 12345;
  double d = 3.14159;
  long l = 9876543210;
  float f = 2.5f;

  printf("String length of int %d: %zu\n", i, to_str_length(i));
  printf("String length of double %.5f: %zu\n", d, to_str_length(d));
  printf("String length of long %ld: %zu\n", l, to_str_length(l));
  printf("String length of float %.1f: %zu\n", f, to_str_length(f));

  // ============================================================
  // to_str - convert values to strings
  // ============================================================
  char *int_str = to_str(42);
  printf("to_str int: %s\n", int_str);
  free(int_str);

  char *double_str = to_str(3.14159);
  printf("to_str double: %s\n", double_str);
  free(double_str);

  char *long_str = to_str(1234567890L);
  printf("to_str long: %s\n", long_str);
  free(long_str);

  char *float_str = to_str(2.5f);
  printf("to_str float: %s\n", float_str);
  free(float_str);
  return 0;
}
