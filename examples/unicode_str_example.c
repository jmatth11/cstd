#include "headers/unicode_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // ============================================================
  // Create unicode string
  // ============================================================
  struct unicode_str_t *ustr = unicode_str_create();
  if (ustr == NULL) {
    fprintf(stderr, "Failed to create unicode string\n");
    return 1;
  }
  printf("Unicode string created\n");

  // ============================================================
  // Set string value
  // ============================================================
  const char *hello = "Hello";
  size_t bytes_written = unicode_str_set_char(ustr, hello, strlen(hello));
  printf("Set string: %s (bytes: %zu)\n", hello, bytes_written);

  // ============================================================
  // Get string length (codepoints and bytes)
  // ============================================================
  printf("Codepoint length: %zu\n", unicode_str_len(ustr));
  printf("Byte length: %zu\n", unicode_str_byte_len(ustr));

  // ============================================================
  // Append to string
  // ============================================================
  const char *world = ", World!";
  bytes_written = unicode_str_append_char(ustr, world, strlen(world));
  printf("Appended: %s (bytes: %zu)\n", world, bytes_written);

  // ============================================================
  // Get full string as C string
  // ============================================================
  char *cstr = unicode_str_to_cstr(ustr);
  printf("Full string: %s\n", cstr);
  free(cstr);

  // ============================================================
  // Insert at codepoint position
  // ============================================================
  const char *beautiful = " Beautiful";
  (void)unicode_str_insert_at_char(ustr, beautiful, strlen(beautiful), 6);
  cstr = unicode_str_to_cstr(ustr);
  printf("After insert at pos 6: %s\n", cstr);
  free(cstr);

  // ============================================================
  // Remove range
  // ============================================================
  unicode_str_remove_range(ustr, 0, 1);
  cstr = unicode_str_to_cstr(ustr);
  printf("After removing 1 codepoint from start: %s\n", cstr);
  free(cstr);

  // ============================================================
  // Get codepoint at position
  // ============================================================
  code_point_t cp = 0;
  if (unicode_str_codepoint_at(ustr, 0, &cp)) {
    printf("Codepoint at position 0: U+%04X\n", cp);
  }

  // ============================================================
  // Get range of codepoints
  // ============================================================
  uint8_t *range = NULL;
  if (unicode_str_get_range(ustr, 0, 5, &range)) {
    printf("Range of 5 codepoints from start: %s\n", (char *)range);
    free(range);
  }

  // ============================================================
  // Convert to lowercase
  // ============================================================
  struct unicode_str_t *lower = unicode_str_to_lower(ustr);
  cstr = unicode_str_to_cstr(lower);
  printf("Lowercase: %s\n", cstr);
  free(cstr);
  unicode_str_destroy(&lower);

  // ============================================================
  // Convert to uppercase
  // ============================================================
  struct unicode_str_t *upper = unicode_str_to_upper(ustr);
  cstr = unicode_str_to_cstr(upper);
  printf("Uppercase: %s\n", cstr);
  free(cstr);
  unicode_str_destroy(&upper);

  // ============================================================
  // Unicode string with emoji
  // ============================================================
  struct unicode_str_t *emoji_str = unicode_str_create();
  const char *emoji = "Hello 👋🌍";
  unicode_str_set_char(emoji_str, emoji, strlen(emoji));
  printf("Emoji string codepoint length: %zu\n", unicode_str_len(emoji_str));
  cstr = unicode_str_to_cstr(emoji_str);
  printf("Emoji string: %s\n", cstr);
  free(cstr);
  unicode_str_destroy(&emoji_str);

  // ============================================================
  // Destroy unicode string
  // ============================================================
  unicode_str_destroy(&ustr);
  printf("Unicode string destroyed\n");

  return 0;
}
