#include "headers/gap_buffer.h"
#include "utf8.h"
#include <stdlib.h>
#include <string.h>

#define GAP_DEFAULT_BUFFER_SIZE 16

static bool resize(struct gap_buffer_t *gb) {
  const size_t new_size = ((double)gb->cap) * 1.7;
  code_point_t *tmp_buff =
      (code_point_t *)realloc(gb->buffer, new_size * sizeof(code_point_t));
  if (tmp_buff == NULL)
    return false;
  gb->buffer = tmp_buff;
  gb->cap = new_size;
  return true;
}

static bool resize_buffer(struct gap_buffer_t *gb) {
  if (!resize(gb)) {
    return false;
  }
  size_t i = gb->len, j = gb->cap;
  for (; i > gb->cursor_end; --i, --j) {
    gb->buffer[j - 1] = gb->buffer[i - 1];
  }
  gb->len = gb->cap;
  gb->cursor_end = j;
  return true;
  return true;
}

size_t gap_buffer_byte_length(struct gap_buffer_t *gb, size_t index) {
  const size_t gap_len = gap_buffer_get_len(gb);
  if (index > gap_len)
    return 0;
  size_t byte_len = 0;
  for (size_t i = 0; i < index; ++i) {
    code_point_t tmp = 0;
    gap_buffer_get_char(gb, i, &tmp);
    const enum octet_type oct = octet_type_from_code_point(tmp);
    byte_len += octet_type_count(oct);
  }
  return byte_len;
}

bool gap_buffer_init(struct gap_buffer_t *gb, size_t buf_size) {
  if (gb == NULL) {
    return false;
  }
  if (buf_size <= 0) {
    buf_size = GAP_DEFAULT_BUFFER_SIZE;
  }
  size_t alloc_size = buf_size * sizeof(code_point_t);
  gb->buffer = (code_point_t *)malloc(alloc_size);
  if (gb->buffer == NULL) {
    return false;
  }
  gb->len = buf_size;
  gb->cap = buf_size;
  gb->cursor_start = 0;
  gb->cursor_end = buf_size;
  gb->get_str = gap_buffer_get_str;
  gb->get_len = gap_buffer_get_len;
  return true;
}

bool gap_buffer_move_cursor(struct gap_buffer_t *gb, size_t pos) {
  if (pos > gb->cap)
    return false;
  const size_t gap_len = gb->cursor_end - gb->cursor_start;
  if (pos > gb->cursor_start) {
    size_t pos_offset = pos + gap_len;
    if (pos_offset > gb->cap) {
      pos_offset = gb->cap;
    }
    const size_t start_idx = gb->cursor_end;
    for (size_t i = start_idx; i < pos_offset; ++i) {
      gb->buffer[gb->cursor_start] = gb->buffer[i];
      gb->cursor_start++;
    }
    gb->cursor_end = pos_offset;
  } else if (pos < gb->cursor_start) {
    size_t i = gb->cursor_start - 1;
    size_t j = gb->cursor_end;
    for (; i >= pos; --i, --j) {
      gb->buffer[j - 1] = gb->buffer[i];
      // break after we handle 0 otherwise it will wrap
      if (i == 0) {
        // decrement j in this case because we miss the last decrement
        j--;
        break;
      }
    }
    gb->cursor_end = j;
    gb->cursor_start = pos;
  }
  return true;
}

void gap_buffer_get_char(const struct gap_buffer_t *gb, size_t pos,
                         code_point_t *out) {
  if (pos > gb->cap)
    return;
  size_t idx = pos;
  if (idx >= gb->cursor_start) {
    idx = pos + (gb->cursor_end - gb->cursor_start);
  }
  *out = gb->buffer[idx];
}

size_t gap_buffer_get_len(const struct gap_buffer_t *gb) {
  return gb->len - (gb->cursor_end - gb->cursor_start);
}

bool gap_buffer_insert(struct gap_buffer_t *gb, code_point_t c) {
  if (gb->cursor_start >= gb->cursor_end) {
    if (!resize_buffer(gb))
      return false;
  }
  gb->buffer[gb->cursor_start] = c;
  gb->cursor_start++;
  return true;
}

bool gap_buffer_insert_word(struct gap_buffer_t *gb, size_t pos,
                            code_point_t *input, size_t len) {
  if (!gap_buffer_move_cursor(gb, pos))
    return false;
  for (size_t i = 0; i < len; ++i) {
    if (!gap_buffer_insert(gb, input[i]))
      return false;
  }
  return true;
}

bool gap_buffer_delete(struct gap_buffer_t *gb) {
  if (gb->cursor_start == 0)
    return false;
  gb->cursor_start--;
  return true;
}

bool gap_buffer_delete_seq(struct gap_buffer_t *gb, size_t n) {
  if (n > gb->cursor_start)
    return false;
  gb->cursor_start -= n;
  return true;
}

code_point_t *gap_buffer_get_str(struct gap_buffer_t *gb) {
  const size_t len = gap_buffer_get_len(gb);
  if (len == 0)
    return NULL;
  code_point_t *result = malloc(sizeof(code_point_t) * (len + 1));
  for (size_t i = 0; i < len; ++i) {
    code_point_t tmp = ' ';
    gap_buffer_get_char(gb, i, &tmp);
    result[i] = tmp;
  }
  // insert null-terminator
  result[len] = '\0';
  return result;
}

void gap_buffer_free(struct gap_buffer_t *gb) {
  if (gb == NULL) {
    return;
  }
  free(gb->buffer);
  gb->buffer = NULL;
  gb->len = 0;
  gb->cap = 0;
  gb->cursor_end = 0;
  gb->cursor_start = 0;
}
