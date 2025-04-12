#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include "headers/defs.h"
#include <stdbool.h>
#include <stdlib.h>

/* constant to multiple capacity by when increasing array size */
#define array_template_capacity_increase_constant 1.7

/* tokens for the struct type and internal data array */
#define array_template_type(name) name##_array
#define array_template_data(name) name##_data

/**
 * The array template struct type
 *
 * @property len The length of items in the array
 * @property cap The available capacity of the array
 * @property <name>_data The array
 */
#define create_array_template(name, type)                                      \
  typedef struct array_template_type(name) {                                   \
    size_t len;                                                                \
    size_t cap;                                                                \
    type *array_template_data(name);                                           \
  }                                                                            \
  array_template_type(name);

/**
 * Initialize the template array with a given size
 *
 * @param[in] arr The template array to get initialized
 * @param[in] N The size to allocate to
 * @return 1 for nominal case, 0 if malloc failed.
 */
#define init_array_template(name, type)                                        \
  UNUSED static inline bool name##_array_init(array_template_type(name) * arr, \
                                              size_t N) {                      \
    if (N < 0)                                                                 \
      N = 1;                                                                   \
    arr->array_template_data(name) = (type *)malloc(N * sizeof(type));         \
    if (arr->array_template_data(name) == NULL) {                              \
      return false;                                                            \
    }                                                                          \
    arr->len = 0;                                                              \
    arr->cap = N;                                                              \
    return true;                                                               \
  }

/**
 * Free the template array.
 * len and cap are set to 0.
 *
 * @param[in] arr The template array to free
 */
#define free_array_template(name, type)                                        \
  UNUSED static inline void name##_array_free(array_template_type(name) *      \
                                              arr) {                           \
    free(arr->array_template_data(name));                                      \
    arr->array_template_data(name) = NULL;                                     \
    arr->len = arr->cap = 0;                                                   \
  }

/**
 * Insert an item into the template array.
 *
 * @param[in] arr The template array
 * @param[in] obj The item to insert
 * @return 1 for nominal case, 0 if realloc failed. (original array is still
 * valid)
 */
#define insert_array_template(name, type)                                      \
  UNUSED static inline bool name##_array_insert(                               \
      array_template_type(name) * arr, type obj) {                             \
    if (arr->len >= arr->cap) {                                                \
      if (arr->cap <= 0)                                                       \
        arr->cap = 1;                                                          \
      arr->cap +=                                                              \
          ((double)arr->cap * array_template_capacity_increase_constant);      \
      type *newArr = (type *)realloc(arr->array_template_data(name),           \
                                     arr->cap * sizeof(type));                 \
      if (newArr == NULL) {                                                    \
        return false;                                                          \
      }                                                                        \
      arr->array_template_data(name) = newArr;                                 \
    }                                                                          \
    arr->array_template_data(name)[arr->len++] = obj;                          \
    return true;                                                               \
  }

/**
 * Get an item from the template array.
 *
 * @param[in] arr The template array
 * @param[in] index The index to access
 * @param[out] out Set to the item at the index, if index out of bounds it's not
 * set.
 */
#define get_array_template(name, type)                                         \
  UNUSED static inline void name##_array_get(                                  \
      const array_template_type(name) * arr, size_t index, type * out) {       \
    if (index < arr->len && index >= 0)                                        \
      *out = arr->array_template_data(name)[index];                            \
  }

/**
 * Fast remove of an element in the template array.
 * This function replaces the removed entry with the last entry and
 * decrements the length property.
 *
 * @param[in] arr The template array.
 * @param[in] idx The index to remove.
 * @return True on success, false otherwise.
 */
#define fast_remove_array_template(name, type)                                 \
  UNUSED static inline bool name##_array_fast_remove(                          \
      array_template_type(name) * arr, size_t idx) {                           \
    if (idx >= arr->len || idx < 0)                                            \
      return false;                                                            \
    if (idx == (arr->len - 1)) {                                               \
      --arr->len;                                                              \
      return true;                                                             \
    }                                                                          \
    arr->array_template_data(name)[idx] =                                      \
        arr->array_template_data(name)[arr->len - 1];                          \
    --arr->len;                                                                \
    return true;                                                               \
  }

/**
 * Generate all template array functions
 */
#define generate_array_template(name, type)                                    \
  create_array_template(name, type) init_array_template(name, type)            \
      free_array_template(name, type) insert_array_template(name, type)        \
          get_array_template(name, type)                                       \
              fast_remove_array_template(name, type)

#endif
