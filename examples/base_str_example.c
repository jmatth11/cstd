#include "headers/base_str.h"
#include <stdio.h>
#include <string.h>

int main(void) {
  // instantiate base string
  struct base_str_t str;
  enum base_str_error err = new_base_str(&str, 32);
  if (err != C_STR_NO_ERROR) {
    fprintf(stderr, "Failed to create base_str\n");
    return 1;
  }

  // set the string
  const char *init = "Hello";
  err = str.set(&str, init, strlen(init));
  if (err != C_STR_NO_ERROR) {
    fprintf(stderr, "Failed to set string\n");
    free_base_str(&str);
    return 1;
  }
  printf("Initial string: %s (len=%d)\n", init, str.length(&str));

  // append to the string
  const char *world_text = ", World!";
  err = str.append(&str, world_text, strlen(world_text));
  if (err != C_STR_NO_ERROR) {
    fprintf(stderr, "Failed to append string\n");
    free_base_str(&str);
    return 1;
  }

  // copy string
  char *out;
  str.copy(&str, &out);
  printf("After append: %s (len=%d)\n", out, str.length(&str));
  free(out);

  // get specific character from string.
  char c;
  str.at(&str, 0, &c);
  printf("Character at index 0: %c\n", c);

  // second append
  const char *test_str = " This is a test.";
  err = str.append(&str, test_str, strlen(test_str));
  if (err != C_STR_NO_ERROR) {
    fprintf(stderr, "Failed to append string\n");
    free_base_str(&str);
    return 1;
  }

  // second copy
  char *out2;
  str.copy(&str, &out2);
  const int local_len = str.length(&str);
  printf("After second append: %s (len=%d)\n", out2, local_len);
  free(out2);

  // free base string
  free_base_str(&str);
  printf("base_str freed successfully\n");

  return 0;
}
