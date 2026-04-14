#include "headers/string_ops.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_dup(const char *str, size_t len) {
  size_t result_len = len;
  char *result = malloc(sizeof(char) * (result_len + 1));
  return str_cpy(result, result_len, str, len);
}

char *str_cpy(char *restrict dest, size_t dest_len, const char *restrict src,
              size_t src_len) {
  // take shortest length
  size_t len = src_len;
  if (dest_len < len) {
    len = dest_len;
  }
  if (strncpy(dest, src, len) == NULL) {
    return NULL;
  }
  // ensure null-termination
  dest[len] = '\0';
  return dest;
}

char *str_fmt(const char *fmt, ...) {
  va_list argp, argp_copy;
  va_start(argp, fmt);
  va_copy(argp_copy, argp);
  size_t n = vsnprintf(NULL, 0, fmt, argp);
  if (n == 0) {
    va_end(argp);
    va_end(argp_copy);
    return NULL;
  }
  char *result = calloc(n + 1, sizeof(char));
  if (result == NULL) {
    va_end(argp);
    va_end(argp_copy);
    return NULL;
  }
  (void)vsnprintf(result, n + 1, fmt, argp_copy);
  result[n] = '\0';
  va_end(argp);
  va_end(argp_copy);
  return result;
}

char *concat(const char *restrict a, const char *restrict b,
             size_t *output_length) {
  if (a == NULL || b == NULL) {
    return NULL;
  }
  const size_t new_len = snprintf(NULL, 0, "%s%s", a, b);
  char *buf = (char *)calloc(new_len + 1, sizeof(char));
  if (snprintf(buf, new_len + 1, "%s%s", a, b) <= 0) {
    free(buf);
    return NULL;
  }
  *output_length = new_len;
  return buf;
}

size_t to_str_length_int(int num) { return snprintf(NULL, 0, "%d", num); }
size_t to_str_length_double(double num) { return snprintf(NULL, 0, "%f", num); }
size_t to_str_length_long(long num) { return snprintf(NULL, 0, "%ld", num); }

char *to_str_int(int num) {
  size_t n = to_str_length(num);
  char *result = calloc(n + 1, sizeof(char));
  if (result == NULL)
    return NULL;
  (void)snprintf(result, n + 1, "%d", num);
  result[n] = '\0';
  return result;
}
char *to_str_double(double num) {
  size_t n = to_str_length(num);
  char *result = calloc(n + 1, sizeof(char));
  if (result == NULL)
    return NULL;
  (void)snprintf(result, n + 1, "%f", num);
  result[n] = '\0';
  return result;
}
char *to_str_long(long num) {
  size_t n = to_str_length(num);
  char *result = calloc(n + 1, sizeof(char));
  if (result == NULL)
    return NULL;
  (void)snprintf(result, n + 1, "%ld", num);
  result[n] = '\0';
  return result;
}
