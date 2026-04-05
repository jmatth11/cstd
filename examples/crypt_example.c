#include "headers/crypt.h"
#include <stdio.h>

/**
 * Example shows iterating over a list of strings and getting a hash for each.
 */
int main(void) {
  const char *strings[] = {"hello",  "world", "test", "password",
                           "123456", "admin", "hello"};
  size_t num_strings = sizeof(strings) / sizeof(strings[0]);

  for (size_t i = 0; i < num_strings; i++) {
    // ============================================================
    // Grab Hash of string.
    // ============================================================
    unsigned long hash = hash_from_str(strings[i]);
    printf("hash_from_str(\"%s\") = %lu\n", strings[i], hash);
  }

  return 0;
}
