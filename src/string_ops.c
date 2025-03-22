#include "headers/string_ops.h"
#include <stdlib.h>
#include <string.h>

char* str_dup(const char *str, size_t len) {
  char *result = malloc((sizeof(char)*len)+1);
  if (strncpy(result, str, len) == NULL) return NULL;
  result[len] = '\0';
  return result;
}
