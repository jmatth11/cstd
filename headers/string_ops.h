#ifndef CSTD_STRING_OPERATIONS_H
#define CSTD_STRING_OPERATIONS_H

#include <stdbool.h>
#include <stddef.h>

#include "defs.h"

/**
 * Create a duplicate of the given string up to length.
 * Includes null-terminated value.
 *
 * @param[in] str The string to duplicate.
 * @param[in] len The length.
 * @return Duplicated null-terminated string.
 */
char* str_dup(const char *str, size_t len) __nonnull((1));

#endif
