#include "headers/unicode_str.h"
#include "utf8.h"
#include <ctype.h>
#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct unicode_str_t {
  byte_array bytes;
};

static byte_array byte_array_from_str(const char *str, size_t len) {
  byte_array result;
  byte_array_init(&result, len);
  for (size_t i = 0; i < len; ++i) {
    result.byte_data[i] = (uint8_t)str[i];
  }
  result.len = len;
  return result;
}

size_t codepoint_idx_from_byte_idx(const uint8_t *arr, size_t len,
                                   size_t index) {
  size_t codepoint_idx = 0;
  for (size_t i = 0; i < index;) {
    if (i >= len)
      return 0;
    enum octet_type oct = get_oct_type(arr[i]);
    size_t skip = octet_type_count(oct);
    i += skip;
    ++codepoint_idx;
  }
  return codepoint_idx;
}

size_t codepoint_idx_from_byte_idx_char(const char *arr, size_t len,
                                        size_t index) {
  byte_array local_arr = byte_array_from_str(arr, len);
  const size_t n =
      codepoint_idx_from_byte_idx(local_arr.byte_data, local_arr.len, index);
  byte_array_free(&local_arr);
  return n;
}

struct unicode_str_t *unicode_str_create() {
  struct unicode_str_t *result = malloc(sizeof(struct unicode_str_t));
  if (!byte_array_init(&result->bytes, 2)) {
    return NULL;
  }
  return result;
}

static inline size_t find_valid_position(byte_array *arr, size_t at) {
  size_t byte_idx = 0;
  for (size_t i = 0; i < at; ++i) {
    if (i >= arr->len)
      return 0;
    enum octet_type oct = get_oct_type(arr->byte_data[byte_idx]);
    size_t skip = octet_type_count(oct);
    byte_idx += skip;
  }
  return byte_idx;
}

/**
 * Resize array to specific size.
 */
static inline void resize(byte_array *str, size_t len) {
  if (len >= str->cap) {
    size_t new_cap = ((double)len * array_template_capacity_increase_constant);
    str->byte_data = realloc(str->byte_data, sizeof(char) * new_cap);
    str->cap = new_cap;
  }
}

/**
 * Resize array to specific size.
 */
static inline void resize_less(byte_array *str, size_t len) {
  if (len < (str->cap - 100)) {
    size_t new_cap = len + 50;
    str->byte_data = realloc(str->byte_data, sizeof(char) * new_cap);
    str->cap = new_cap;
  }
}

static inline bool insert_range(const uint8_t *data, byte_array *arr,
                                size_t offset, size_t len) {
  for (size_t i = offset; i < (offset + len); ++i) {
    if (!byte_array_insert(arr, data[i]))
      return false;
  }
  return true;
}

static inline bool insert_range_at(const uint8_t *data, byte_array *arr,
                                   size_t offset, size_t len, size_t at) {
  size_t at_offset = 0;
  for (size_t i = offset; i < (offset + len); ++i) {
    if ((at + at_offset) > arr->len)
      return false;
    arr->byte_data[at + at_offset] = data[i];
    ++at_offset;
  }
  return true;
}

static inline bool insert_replacement_char(byte_array *arr) {
  uint8_t buff[4] = {0};
  struct code_point point = {
      .type = octet_type_from_code_point(replacement_character),
      .val = replacement_character,
  };
  size_t n = utf8_write(buff, 4, 0, point);
  if (n == 0) {
    return false;
  }
  for (size_t i = 0; i < n; ++i) {
    if (!byte_array_insert(arr, buff[i])) {
      return false;
    }
  }
  return true;
}

static inline bool insert_replacement_char_at(byte_array *arr, size_t at) {
  uint8_t buff[4] = {0};
  struct code_point point = {
      .type = octet_type_from_code_point(replacement_character),
      .val = replacement_character,
  };
  size_t n = utf8_write(buff, 4, 0, point);
  if (n == 0) {
    return false;
  }
  for (size_t i = 0; i < n; ++i) {
    arr->byte_data[at + i] = buff[i];
  }
  return true;
}

size_t unicode_str_set(struct unicode_str_t *str, const uint8_t *other,
                       size_t len) {
  // reset string
  str->bytes.len = 0;
  return unicode_str_append(str, other, len);
}

size_t unicode_str_set_char(struct unicode_str_t *str, const char *other,
                            size_t len) {
  byte_array arr = byte_array_from_str(other, len);
  const size_t result = unicode_str_set(str, arr.byte_data, arr.len);
  byte_array_free(&arr);
  return result;
}

bool unicode_str_get(struct unicode_str_t *str, const byte_array **out) {
  *out = &str->bytes;
  return true;
}

size_t unicode_str_append_char(struct unicode_str_t *str, const char *other,
                               size_t len) {
  // TODO maybe use internal buffer from unicode_str_t and then verify
  // rather than have copy buffer
  byte_array arr = byte_array_from_str(other, len);
  const size_t result = unicode_str_append(str, arr.byte_data, arr.len);
  byte_array_free(&arr);
  return result;
}

size_t unicode_str_append(struct unicode_str_t *str, const uint8_t *other,
                          size_t len) {
  if (!utf8_verify_str(other, len)) {
    printf("failed verify\n");
    return 0;
  }
  size_t cur_len = len;
  size_t size = 0;
  bool currently_invalid = false;
  for (size_t cur_idx = 0; cur_idx < len;) {
    struct code_point result = utf8_next(other, cur_len, cur_idx);
    if (result.type == OCT_INVALID) {
      if (!currently_invalid) {
        // place unicode replacement character
        if (!insert_replacement_char(&str->bytes)) {
          return size;
        }
        // 4 bytes for replace character
        size += 4;
      }
      currently_invalid = true;
      // push past invalid char
      cur_idx += 1;
      continue;
    }
    currently_invalid = false;
    size_t byte_size = octet_type_count(result.type);
    if (!insert_range(other, &str->bytes, cur_idx, byte_size)) {
      return size;
    }
    cur_idx += byte_size;
    size += byte_size;
  }
  return size;
}

bool unicode_str_insert_at_codepoint(struct unicode_str_t *str,
                                     const code_point_t other, size_t offset) {
  uint8_t buf[4] = {0};
  uint8_t n = utf8_write_code_point(buf, 4, 0, other);
  return unicode_str_insert_at(str, buf, n, offset) == n;
}

size_t unicode_str_insert_at_char(struct unicode_str_t *str, const char *other,
                                  size_t len, size_t offset) {
  byte_array arr = byte_array_from_str(other, len);
  const size_t result =
      unicode_str_insert_at(str, arr.byte_data, arr.len, offset);
  byte_array_free(&arr);
  return result;
}

size_t unicode_str_insert_at(struct unicode_str_t *str, const uint8_t *other,
                             size_t len, size_t offset) {
  if (offset > str->bytes.len)
    return 0;
  // TODO maybe remove and just let replacement characters in
  if (!utf8_verify_str(other, len)) {
    return 0;
  }
  const size_t new_len = str->bytes.len + len;
  const size_t valid_offset = find_valid_position(&str->bytes, offset);
  if (valid_offset == 0 && offset != 0) {
    return 0;
  }
  resize(&str->bytes, new_len);
  if (str->bytes.len > 0) {
    for (size_t i = str->bytes.len; i >= valid_offset; --i) {
      const size_t cur_idx = i - 1;
      str->bytes.byte_data[cur_idx + len] = str->bytes.byte_data[cur_idx];
    }
  }
  size_t cur_len = len;
  size_t size = 0;
  bool currently_invalid = false;
  for (size_t byte_idx = valid_offset, other_idx = 0; other_idx < len;) {
    struct code_point result = utf8_next(other, cur_len, other_idx);
    if (result.type == OCT_INVALID) {
      if (!currently_invalid) {
        // place unicode replacement character
        if (!insert_replacement_char_at(&str->bytes, byte_idx)) {
          return size;
        }
        // 4 bytes for replace character
        size += 4;
        byte_idx += 4;
      }
      currently_invalid = true;
      // push past invalid char
      other_idx += 1;
      continue;
    }
    currently_invalid = false;
    size_t byte_size = octet_type_count(result.type);
    if (!insert_range_at(other, &str->bytes, other_idx, byte_size, byte_idx)) {
      fprintf(stderr, "insert_range_at failed\n");
      return size;
    }
    other_idx += byte_size;
    byte_idx += byte_size;
    size += byte_size;
  }
  str->bytes.len += size;
  return size;
}

size_t unicode_str_remove_range(struct unicode_str_t *str, size_t offset,
                                size_t len) {
  if (offset > str->bytes.len)
    return 0;
  size_t byte_idx = find_valid_position(&str->bytes, offset);
  size_t final_idx = find_valid_position(&str->bytes, offset + len);
  if ((byte_idx == 0 && offset != 0) || final_idx == 0)
    return 0;
  size_t diff = (final_idx - byte_idx);
  const size_t new_len = str->bytes.len - diff;
  if (final_idx == str->bytes.len) {
    str->bytes.len = new_len;
    resize_less(&str->bytes, str->bytes.len);
    return diff;
  }
  for (size_t i = 0; i < (str->bytes.len - final_idx); ++i) {
    str->bytes.byte_data[byte_idx + i] = str->bytes.byte_data[final_idx + i];
  }
  str->bytes.len = new_len;
  resize_less(&str->bytes, str->bytes.len);
  str->bytes.byte_data[new_len] = '\0';
  return diff;
}

size_t unicode_str_len(struct unicode_str_t *str) {
  return utf8_len(str->bytes.byte_data, str->bytes.len);
}

size_t unicode_str_byte_len(struct unicode_str_t *str) {
  return str->bytes.len;
}

bool unicode_str_codepoint_at(struct unicode_str_t *str, size_t index,
                              code_point_t *out) {
  const size_t idx = find_valid_position(&str->bytes, index);
  if (idx == 0 && index != 0)
    return false;
  struct code_point point =
      utf8_next(str->bytes.byte_data, str->bytes.len, idx);
  *out = point.val;
  return point.type != OCT_INVALID;
}

bool unicode_str_get_range(struct unicode_str_t *str, size_t index, size_t len,
                           uint8_t **out) {
  const size_t idx = find_valid_position(&str->bytes, index);
  const size_t end_idx = find_valid_position(&str->bytes, index + len);
  if (idx == 0 && index != 0)
    return false;
  if (end_idx == 0)
    return false;
  const size_t size = (end_idx - idx);
  uint8_t *result = malloc(sizeof(uint8_t) * size + 1);
  memcpy(result, &str->bytes.byte_data[idx], size);
  result[size] = '\0';
  *out = result;
  return true;
}

struct unicode_str_t *unicode_str_to_lower(struct unicode_str_t *str) {
  struct unicode_str_t *result = unicode_str_create();
  setlocale(LC_ALL, "");
  for (size_t i = 0; i < unicode_str_len(str); ++i) {
    code_point_t point = 0;
    if (!unicode_str_codepoint_at(str, i, &point)) {
      unicode_str_destroy(&result);
      return NULL;
    }
    if (!unicode_str_insert_at_codepoint(result, tolower(point), i)) {
      unicode_str_destroy(&result);
      return NULL;
    }
  }
  return result;
}

struct unicode_str_t *unicode_str_to_upper(struct unicode_str_t *str) {
  struct unicode_str_t *result = unicode_str_create();
  setlocale(LC_ALL, "");
  for (size_t i = 0; i < unicode_str_len(str); ++i) {
    code_point_t point = 0;
    if (!unicode_str_codepoint_at(str, i, &point)) {
      unicode_str_destroy(&result);
      return NULL;
    }
    if (!unicode_str_insert_at_codepoint(result, toupper(point), i)) {
      unicode_str_destroy(&result);
      return NULL;
    }
  }
  return result;
}

char *unicode_str_to_cstr(struct unicode_str_t *str) {
  char *result = malloc((sizeof(char) * str->bytes.len) + 1);
  for (size_t i = 0; i < str->bytes.len; ++i) {
    result[i] = (char)str->bytes.byte_data[i];
  }
  result[str->bytes.len] = '\0';
  return result;
}

void unicode_str_destroy(struct unicode_str_t **str) {
  if (*str == NULL) {
    return;
  }
  byte_array_free(&(*str)->bytes);
  free(*str);
  *str = NULL;
}
