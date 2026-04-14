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
char *str_dup(const char *str, size_t len) __nonnull((1));

/**
 * @brief Copy up-to min(dest_len, src_len) of src into dest.
 * Properly applies null-terminator at the end of the copy for dest.
 *
 * @param[out] dest The destination string.
 * @param[in] dest_len The length of destination string.
 * @param[in] src The source string.
 * @param[in] src_len The length of the source string.
 * @return The dest pointer if successful, NULL on failure.
 */
char *str_cpy(char *restrict dest, size_t dest_len, const char *restrict src,
              size_t src_len);

/**
 * Generate formatted string.
 * This function handles generating the formatted string in a newly
 * allocated string as the return value.
 * Caller is responsible for freeing the memory.
 *
 * @param[in] fmt The format string.
 * @param[in] ... The options for format.
 * @return Newly allocated string.
 */
char *str_fmt(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

/**
 * Concat two strings.
 * User is responsible for freeing returned string.
 *
 * @param a String a.
 * @param b String b.
 * @param[out] output_length The output's length.
 * @return Newly concated string, NULL on failure.
 */
char *concat(const char *restrict a, const char *restrict b,
             size_t *output_length);

/**
 * Get the length of a string representation of the given integer.
 *
 * @param[in] num The integer value.
 * @return The length of the string representation.
 */
size_t to_str_length_int(int num);

/**
 * Get the length of a string representation of the given double.
 *
 * @param[in] num The double value.
 * @return The length of the string representation.
 */
size_t to_str_length_double(double num);

/**
 * Get the length of a string representation of the given long.
 *
 * @param[in] num The long value.
 * @return The length of the string representation.
 */
size_t to_str_length_long(long num);

/**
 * Generic macro to get the length of a string representation of any supported
 * type. Supports: float, double, long, int.
 *
 * @param[in] n The value to get the string length for.
 * @return The length of the string representation.
 */
#define to_str_length(n)                                                       \
  _Generic((n),                                                                \
      float: to_str_length_double,                                             \
      double: to_str_length_double,                                            \
      long: to_str_length_long,                                                \
      default: to_str_length_int)(n)

/**
 * Convert an integer to a string.
 * The caller is responsible for freeing the memory.
 *
 * @param[in] num The integer value.
 * @return Newly allocated string representation, NULL on error.
 */
char *to_str_int(int num);

/**
 * Convert a double to a string.
 * The caller is responsible for freeing the memory.
 *
 * @param[in] num The double value.
 * @return Newly allocated string representation, NULL on error.
 */
char *to_str_double(double num);

/**
 * Convert a long to a string.
 * The caller is responsible for freeing the memory.
 *
 * @param[in] num The long value.
 * @return Newly allocated string representation, NULL on error.
 */
char *to_str_long(long num);

#define to_str(n)                                                              \
  _Generic((n),                                                                \
      float: to_str_double,                                                    \
      double: to_str_double,                                                   \
      long: to_str_long,                                                       \
      default: to_str_int)(n)

__END_DECLS

#endif
