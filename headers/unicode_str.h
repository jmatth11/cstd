#ifndef CSTD_UNICODE_STR_H
#define CSTD_UNICODE_STR_H

#include "defs.h"
#include "utf8.h"
#include <stdbool.h>
#include <stdint.h>

#include "array_template.h"

__BEGIN_DECLS

typedef uint32_t code_point_t;

generate_array_template(byte, uint8_t);

struct unicode_str_t;

struct unicode_str_t *unicode_str_create() __THROWNL;

size_t unicode_str_set(struct unicode_str_t *str, const uint8_t *other,
                     size_t len) __THROWNL __nonnull((1, 2));

bool unicode_str_get(struct unicode_str_t *str, const byte_array **out) __THROWNL
    __nonnull((1));

size_t unicode_str_append(struct unicode_str_t *str, const uint8_t *other,
                        size_t len) __THROWNL __nonnull((1, 2));

size_t unicode_str_insert_at(struct unicode_str_t *str, const uint8_t *other,
                           size_t len, size_t offset) __THROWNL
    __nonnull((1, 2));

size_t unicode_str_remove_range(struct unicode_str_t *str, size_t offset,
                              size_t len) __THROWNL __nonnull((1));

size_t unicode_str_len(struct unicode_str_t *str) __THROWNL __nonnull((1));

size_t unicode_str_byte_len(struct unicode_str_t *str) __THROWNL __nonnull((1));

bool unicode_str_codepoint_at(struct unicode_str_t *str, size_t index,
                              code_point_t *out) __THROWNL __nonnull((1));

bool unicode_str_get_range(struct unicode_str_t *str, size_t index, size_t len,
                           uint8_t **out) __THROWNL __nonnull((1));

void unicode_str_destroy(struct unicode_str_t *str) __THROWNL __nonnull((1));

__END_DECLS

#endif
