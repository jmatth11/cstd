#include "unicode_str.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static byte_array byte_array_from_str(const char *str) {
  const size_t len = strlen(str);
  byte_array result;
  byte_array_init(&result, len);
  for (size_t i = 0; i < len; ++i) {
    result.byte_data[i] = (uint8_t)str[i];
  }
  result.len = len;
  return result;
}

static bool compare_byte_arrays(const byte_array arr1, const byte_array arr2) {
  // printf("comparing \"%s\"(%lu) to \"%s\"(%lu)\n", arr1.byte_data, arr1.len,
  // arr2.byte_data, arr2.len);
  if (arr1.len != arr2.len)
    return false;
  for (size_t i = 0; i < arr1.len; ++i) {
    if (arr1.byte_data[i] != arr2.byte_data[i])
      return false;
  }
  return true;
}

static bool compare_byte_array_and_uint8(const byte_array arr1,
                                         const uint8_t *arr2) {
  // printf("comparing \"%s\"(%lu) to \"%s\"(%lu)\n", arr1.byte_data, arr1.len,
  // arr2.byte_data, arr2.len);
  // define upper limit just so we aren't going forever.
  const size_t str_cmp_limit = 1024;
  size_t arr2_len = 0;
  char cur_char = ' ';
  while (arr2_len < str_cmp_limit) {
    cur_char = arr2[arr2_len];
    if (cur_char == '\0') {
      break;
    }
    ++arr2_len;
  }
  if (arr2_len == str_cmp_limit) {
    fprintf(stderr, "hit string compare limit, something is most likely wrong.\n");
    return false;
  }
  if (arr1.len != arr2_len)
    return false;
  for (size_t i = 0; i < arr1.len; ++i) {
    if (arr1.byte_data[i] != arr2[i])
      return false;
  }
  return true;
}

static void debug_byte_array(const byte_array arr) {
  printf("arr debug:\n");
  printf("- byte_array[%lu]{\n", arr.len);
  for (size_t i = 0; i < arr.len; ++i) {
    printf("\t%d(%c), \n", arr.byte_data[i], arr.byte_data[i]);
  }
  printf("}\n");
}
