#ifndef CSTD_BASE_C_STR
#define CSTD_BASE_C_STR

#include "defs.h"
#include <stdlib.h>

__BEGIN_DECLS

/**
 * Enums for error base_str error codes.
 */
typedef enum base_str_error {
    /* success */
    C_STR_NO_ERROR,
    /* malloc error */
    C_STR_MALLOC_ERROR,
    /* out of bounds */
    C_STR_OUT_OF_BOUNDS
} base_str_error;

/**
 * Internal base_str structure.
 */
struct internal_base_str;

/**
 * Structure to handle dealing with strings in a more convenient way.
 */
typedef struct base_str_t {
    /* internal */
    struct internal_base_str *_internal;
    /**
     * Append the given string to this string.
     * @param[in] struct base_str* The base_str object.
     * @param[in] const char* The string to append.
     * @param[in] size_t The size of the string to copy.
     * @returns base_str_error.
     */
    base_str_error (*append)(struct base_str_t*, const char *, size_t);
    /**
     * Get the length of the string. (does not include null-terminator
     * @param[in] const struct base_str* The base_str structure.
     * @returns The length.
     */
    int (*length)(const struct base_str_t*);
    /**
     * Get the underlying string.
     * @param[in] const struct base_str* The base_str structure.
     * @param[out] char** The pointer to return out the string to.
     * @returns base_str_error.
     */
    base_str_error (*get_str)(const struct base_str_t*, char **);
    /**
     * Get the underlying string as a const char*.
     * @param[in] const struct base_str* The base_str structure.
     * @param[out] const char** The pointer to return out the string to.
     * @returns base_str_error.
     */
    base_str_error (*get_const_str)(const struct base_str_t*, const char **);
    /**
     * Set the underlying string with the given string.
     * @param[in] struct base_str* The base_str structure.
     * @param[in] const char* The string data.
     * @param[in] size_t The size of the given string.
     * @returns base_str_error.
     */
    base_str_error (*set)(struct base_str_t*, const char *, const size_t);
    /**
     * Get the character at the given index.
     * @param[in] struct base_str* The base_str structure.
     * @param[in] size_t The index value.
     * @param[out] char* The out param.
     * @returns base_str_error.
     */
    base_str_error (*at)(const struct base_str_t*, const size_t, char*);
    /**
     * Generate a copy of the string into the out parameter.
     * The caller is responsible for freeing the generated string.
     * @param[in] const struct base_str* The base_str structure.
     * @param[out] char** The pointer to return out the copied string to.
     * @returns base_str_error.
     */
    base_str_error (*copy)(const struct base_str_t*, char **);
} base_str;

/**
 * Initializes a new base_str structure with a certain size.
 * @param[in] struct base_str* The base_str structure to initialize.
 * @param[in] size_t The size to initialize to.
 * @returns base_str_error.
 */
base_str_error new_base_str(struct base_str_t*, size_t);

/**
 * Initializes a new base_str structure with a given string.
 * @param[in] struct base_str* The base_str structure to initialize.
 * @param[in] const char* The string to copy.
 * @param[in] size_t The size of the given string.
 * @returns base_str_error.
 */
base_str_error new_base_str_with_string(struct base_str_t*, const char*, size_t);

/**
 * Frees the internals of the base_str.
 * @param[in] struct base_str* The base_str to free.
 */
void free_base_str(struct base_str_t*);

__END_DECLS

#endif
