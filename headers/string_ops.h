#ifndef CSTD_STRING_OPERATIONS_H
#define CSTD_STRING_OPERATIONS_H

#include <stdbool.h>
#include <stddef.h>

#include "defs.h"

__BEGIN_DECLS

/**
 * Create a duplicate of the given string up to length.
 * Includes null-terminated value.
 *
 * @param[in] str The string to duplicate.
 * @param[in] len The length.
 * @return Duplicated null-terminated string.
 */
char* str_dup(const char *str, size_t len) __nonnull((1));

/**
 * Get the length of a string representation of the given value.
 */
size_t to_str_length_int(int num);
size_t to_str_length_float(double num);
size_t to_str_length_long(long num);

#define to_str_length(n) _Generic((n), \
      float : to_str_length_float, \
      double : to_str_length_float, \
      long : to_str_length_long, \
      default : to_str_length_int \
    )(n)

/**
 * Convert the given value to a string.
 * The caller is responsible for freeing the memory.
 */
char* to_str_int(int num);
char* to_str_float(double num);
char* to_str_long(long num);

#define to_str(n) _Generic((n), \
      float : to_str_float, \
      double : to_str_float, \
      long : to_str_long, \
      default : to_str_int \
    )(n)

__END_DECLS

#endif
