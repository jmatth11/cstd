#ifndef CSTD_UNICODE_STR_H
#define CSTD_UNICODE_STR_H

#include "defs.h"
#include "utf8.h"
#include <stdbool.h>
#include <stdint.h>

#include "array_template.h"

__BEGIN_DECLS

/**
 * code point typedef, 32bit character representation.
 */
typedef uint32_t code_point_t;

generate_array_template(byte, uint8_t);

/**
 * Get the closest codepoint index from the given byte index.
 *
 * @param[in] arr The raw UTF-8 encoded string.
 * @param[in] len The length of the array in bytes.
 * @param[in] index The byte index.
 * @return The codepoint position, 0 is also used when an invalid UTF-8 string
 * is encountered.
 */
size_t codepoint_idx_from_byte_idx(const uint8_t *arr, size_t len,
                                   size_t index) __THROWNL;

/**
 * Get the closest codepoint index from the given byte index.
 *
 * @param[in] arr The raw UTF-8 encoded string.
 * @param[in] len The length of the array in bytes.
 * @param[in] index The byte index.
 * @return The codepoint position, 0 is also used when an invalid UTF-8 string
 * is encountered.
 */
size_t codepoint_idx_from_byte_idx_char(const char *arr, size_t len,
                                        size_t index) __THROWNL;

/**
 * Unicode structure for handling utf8-encoded strings.
 */
struct unicode_str_t;

/**
 * Create a unicode string structure.
 *
 * @see unicode_str_destory()
 * @return The newly allocated unicode string.
 */
struct unicode_str_t *unicode_str_create() __THROWNL;

/**
 * Set the unicode string with the given string.
 * This function validates the incoming string for valid UTF-8 encoding.
 *
 * @param[in] str The unicode string.
 * @param[in] other The incoming string to set.
 * @param[in] len The length of the incoming string in bytes.
 * @return The number of bytes written, 0 if no bytes or an error.
 */
size_t unicode_str_set(struct unicode_str_t *str, const uint8_t *other,
                       size_t len) __THROWNL __nonnull((1, 2));

/**
 * Set the unicode string with the given string.
 * This function validates the incoming string for valid UTF-8 encoding.
 *
 * @param[in] str The unicode string.
 * @param[in] other The incoming string to set.
 * @param[in] len The length of the incoming string in bytes.
 * @return The number of bytes written, 0 if no bytes or an error.
 */
size_t unicode_str_set_char(struct unicode_str_t *str, const char *other,
                            size_t len) __THROWNL __nonnull((1, 2));
/**
 * Get the unicode string as a byte_array.
 *
 * @param[in] str The unicode string.
 * @param[out] out The byte_array pointer to populate.
 * @return True if successful, false otherwise.
 */
bool unicode_str_get(struct unicode_str_t *str,
                     const byte_array **out) __THROWNL __nonnull((1));

/**
 * Append the given string to the unicode string.
 * This function validates the incoming string for valid UTF-8 encoding.
 *
 * @param[in] str The unicode string.
 * @param[in] other The incoming string to set.
 * @param[in] len The length of the incoming string in bytes.
 * @return The number of bytes written, 0 if no bytes or an error.
 */
size_t unicode_str_append(struct unicode_str_t *str, const uint8_t *other,
                          size_t len) __THROWNL __nonnull((1, 2));

/**
 * Append the given string to the unicode string.
 * This function validates the incoming string for valid UTF-8 encoding.
 *
 * @param[in] str The unicode string.
 * @param[in] other The incoming string to set.
 * @param[in] len The length of the incoming string in bytes.
 * @return The number of bytes written, 0 if no bytes or an error.
 */
size_t unicode_str_append_char(struct unicode_str_t *str, const char *other,
                               size_t len) __THROWNL __nonnull((1, 2));
/**
 * Insert the given string at a specified codepoint offset to the unicode
 * string. This function validates the incoming string for valid UTF-8 encoding.
 *
 * @param[in] str The unicode string.
 * @param[in] other The incoming string to set.
 * @param[in] len The length of the incoming string in bytes.
 * @param[in] offset The codepoint offset, not the byte offset.
 * @return The number of bytes written, 0 if no bytes or an error.
 */
size_t unicode_str_insert_at(struct unicode_str_t *str, const uint8_t *other,
                             size_t len, size_t offset) __THROWNL
    __nonnull((1, 2));

/**
 * Insert the given string at a specified codepoint offset to the unicode
 * string. This function validates the incoming string for valid UTF-8 encoding.
 *
 * @param[in] str The unicode string.
 * @param[in] other The incoming string to set.
 * @param[in] len The length of the incoming string in bytes.
 * @param[in] offset The codepoint offset, not the byte offset.
 * @return The number of bytes written, 0 if no bytes or an error.
 */
size_t unicode_str_insert_at_char(struct unicode_str_t *str, const char *other,
                                  size_t len, size_t offset) __THROWNL
    __nonnull((1, 2));

/**
 * Insert the given codepoint at a specified codepoint offset to the unicode
 * string. This function validates the incoming codepoint is a valid UTF-8
 * character.
 *
 * @param[in] str The unicode string.
 * @param[in] other The incoming codepoint to set.
 * @param[in] offset The codepoint offset, not the byte offset.
 * @return True if successful, False otherwise.
 */
bool unicode_str_insert_at_codepoint(struct unicode_str_t *str,
                                     const code_point_t other,
                                     size_t offset) __THROWNL __nonnull((1));
/**
 * Remove a range from the unicode string.
 *
 * @param[in] str The unicode string.
 * @param[in] offset The codepoint offset, not the byte offset.
 * @param[in] len The length from the offset to remove, in codepoints.
 * @return The number of bytes removed, 0 if no bytes or an error.
 */
size_t unicode_str_remove_range(struct unicode_str_t *str, size_t offset,
                                size_t len) __THROWNL __nonnull((1));

/**
 * Get the codepoint length of the unicode string.
 *
 * @param[in] str The unicode string.
 * @return The number of codepoints.
 */
size_t unicode_str_len(struct unicode_str_t *str) __THROWNL __nonnull((1));

/**
 * Get the byte length of the unicode string.
 * Can be more than unicode_str_len since this is counting raw bytes.
 *
 * @param[in] str The unicode string.
 * @return The number of bytes.
 */
size_t unicode_str_byte_len(struct unicode_str_t *str) __THROWNL __nonnull((1));

/**
 * Get the codepoint at the given codepoint position.
 *
 * @param[in] str The unicode string.
 * @param[in] index The codepoint position, not the byte position.
 * @param[out] out The codepoint pointer to populate.
 * @return True if the codepoint position was found, false otherwise.
 */
bool unicode_str_codepoint_at(struct unicode_str_t *str, size_t index,
                              code_point_t *out) __THROWNL __nonnull((1));

/**
 * Get the range of codepoints as raw bytes at the given codepoint position and
 * length. You are responsible for freeing the returned range.
 *
 * @param[in] str The unicode string.
 * @param[in] index The codepoint position, not the byte position.
 * @param[in] len The length of the range based off the index in codepoint
 * length.
 * @param[out] out The raw uint8_t array to populate.
 * @return True if the codepoint position was found, false otherwise.
 */
bool unicode_str_get_range(struct unicode_str_t *str, size_t index, size_t len,
                           uint8_t **out) __THROWNL __nonnull((1));

/**
 * Return a newly allocated unicode string converted to lowercase.
 * Caller is responsible for destroying returned unicode string.
 *
 * @param[in] str The unicode string to convert.
 * @return Newly allocated lowercase unicode string.
 */
struct unicode_str_t *unicode_str_to_lower(struct unicode_str_t *str)
    __nonnull((1));

/**
 * Return a newly allocated unicode string converted to uppercase.
 * Caller is responsible for destroying returned unicode string.
 *
 * @param[in] str The unicode string to convert.
 * @return Newly allocated uppercase unicode string.
 */
struct unicode_str_t *unicode_str_to_upper(struct unicode_str_t *str)
    __nonnull((1));

/**
 * Return a newly allocated C string of the unicode string.
 * Caller is responsible for freeing the returned C string.
 *
 * @param[in] str The unicode string.
 * @return C string representation of the unicode string.
 */
char *unicode_str_to_cstr(struct unicode_str_t *str) __nonnull((1));

/**
 * Destroy the given unicode string internals.
 *
 * @param[out] str The unicode string.
 */
void unicode_str_destroy(struct unicode_str_t **str) __THROWNL __nonnull((1));

__END_DECLS

#endif
