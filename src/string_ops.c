#include "headers/string_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_dup(const char *str, size_t len) {
  char *result = malloc((sizeof(char) * len) + 1);
  if (strncpy(result, str, len) == NULL)
    return NULL;
  result[len] = '\0';
  return result;
}

size_t to_str_length_int(int num) { return snprintf(NULL, 0, "%d", num) + 1; }
size_t to_str_length_float(double num) {
  return snprintf(NULL, 0, "%f", num) + 1;
}
size_t to_str_length_long(long num) {
  return snprintf(NULL, 0, "%ld", num) + 1;
}

char *to_str_int(int num) {
  size_t n = to_str_length(num);
  char *result = calloc(n + 1, sizeof(char));
  if (result == NULL)
    return NULL;
  (void)snprintf(result, n, "%d", num);
  result[n] = '\0';
  return result;
}
char *to_str_double(double num) {
  size_t n = to_str_length(num);
  char *result = calloc(n + 1, sizeof(char));
  if (result == NULL)
    return NULL;
  (void)snprintf(result, n, "%f", num);
  result[n] = '\0';
  return result;
}
char *to_str_long(long num) {
  size_t n = to_str_length(num);
  char *result = calloc(n + 1, sizeof(char));
  if (result == NULL)
    return NULL;
  (void)snprintf(result, n, "%ld", num);
  result[n] = '\0';
  return result;
}
