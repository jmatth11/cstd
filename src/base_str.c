#include "headers/base_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef C_STR_ARRAY_INC_CONSTANT
#define C_STR_ARRAY_INC_CONSTANT 1.2
#endif

struct internal_base_str {
  char *data;
  size_t len;
  size_t cap;
};

static inline void resize(struct internal_base_str *str, size_t len) {
  if (str == NULL || len == 0) {
    return;
  }
  if (len >= str->cap) {
    const size_t new_cap = ((double)len * C_STR_ARRAY_INC_CONSTANT);
    char* result = realloc(str->data, sizeof(char) * new_cap);
    str->data = result;
    str->cap = new_cap;
  }
}

base_str_error append(struct base_str_t *data, const char *str, size_t len) {
  if (data == NULL || str == NULL) {
    return C_STR_NULL_PARAM;
  }
  if (len == 0) {
    return C_STR_NO_ERROR;
  }
  const size_t d_len = data->_internal->len;
  const size_t new_len = d_len + len;
  resize(data->_internal, new_len);
  if (data->_internal->data == NULL) {
    return C_STR_MALLOC_ERROR;
  }
  strncpy(&data->_internal->data[d_len], str, len);
  data->_internal->data[new_len] = '\0';
  data->_internal->len = new_len;
  return C_STR_NO_ERROR;
}

int length(const struct base_str_t *data) {
  if (data == NULL) {
    return 0;
  }
  return data->_internal->len;
}

base_str_error get_str(const struct base_str_t *data, char **out) {
  if (data == NULL) {
    return C_STR_NULL_PARAM;
  }
  *out = data->_internal->data;
  return C_STR_NO_ERROR;
}

base_str_error get_const_str(const struct base_str_t *data, const char **out) {
  if (data == NULL) {
    return C_STR_NULL_PARAM;
  }
  *out = data->_internal->data;
  return C_STR_NO_ERROR;
}

base_str_error copy(const struct base_str_t *data, char **out) {
  if (data == NULL) {
    return C_STR_NULL_PARAM;
  }
  const size_t len = data->_internal->len;
  char *result = (char *)malloc(sizeof(char) * (len + 1));
  if (result == NULL) {
    return C_STR_MALLOC_ERROR;
  }
  if (strncpy(result, data->_internal->data, len) == NULL) {
    free(result);
    return C_STR_MALLOC_ERROR;
  }
  result[len] = '\0';
  *out = result;
  return C_STR_NO_ERROR;
}

base_str_error set(struct base_str_t *data, const char *str, size_t len) {
  if (data == NULL || str == NULL) {
    return C_STR_NULL_PARAM;
  }
  if (len == 0) {
    return C_STR_NO_ERROR;
  }
  resize(data->_internal, len);
  if (data->_internal->data == NULL) {
    return C_STR_MALLOC_ERROR;
  }
  strncpy(data->_internal->data, str, len);
  data->_internal->data[len] = '\0';
  data->_internal->len = len;
  return C_STR_NO_ERROR;
}

base_str_error at(const struct base_str_t *data, size_t idx, char *out) {
  if (data == NULL) {
    return C_STR_NULL_PARAM;
  }
  const size_t len = data->_internal->len;
  if (idx > len) {
    return C_STR_OUT_OF_BOUNDS;
  }
  *out = data->_internal->data[idx];
  return C_STR_NO_ERROR;
}

base_str_error new_base_str(struct base_str_t *data, size_t cap) {
  if (data == NULL) {
    return C_STR_NULL_PARAM;
  }
  // add for null-terminator
  ++cap;
  char *tmp = (char *)malloc(sizeof(char) * cap);
  if (tmp == NULL) {
    return C_STR_MALLOC_ERROR;
  }
  tmp[0] = '\0';
  data->_internal =
      (struct internal_base_str *)malloc(sizeof(struct internal_base_str));
  if (data->_internal == NULL) {
    return C_STR_MALLOC_ERROR;
  }
  data->at = at;
  data->set = set;
  data->append = append;
  data->length = length;
  data->get_str = get_str;
  data->get_const_str = get_const_str;
  data->copy = copy;
  data->_internal->data = tmp;
  data->_internal->len = 0;
  data->_internal->cap = cap;
  return C_STR_NO_ERROR;
}

base_str_error new_base_str_with_string(struct base_str_t *data,
                                        const char *str, size_t len) {
  if (data == NULL || str == NULL) {
    return C_STR_NULL_PARAM;
  }
  if (len <= 0) {
    len = 1;
  }
  size_t cap = ((double)len * C_STR_ARRAY_INC_CONSTANT);
  base_str_error err = new_base_str(data, cap);
  if (err != C_STR_NO_ERROR) {
    return err;
  }
  data->set(data, str, len);
  return C_STR_NO_ERROR;
}

void free_base_str(struct base_str_t *data) {
  if (data == NULL) {
    return;
  }
  if (data->_internal != NULL) {
    free(data->_internal->data);
    free(data->_internal);
  }
  data->_internal = NULL;
}
