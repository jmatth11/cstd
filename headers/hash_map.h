#ifndef CSTD_HASH_MAP_H
#define CSTD_HASH_MAP_H

#include <stdbool.h>
#include <stddef.h>
#include "unicode_str.h"
#include "defs.h"

__BEGIN_DECLS

struct hash_map;

/**
 * Create a hash map with a given map size.
 *
 * @param[in] n The size of the map.
 * @return The allocated hash map, NULL if error.
 */
struct hash_map * hash_map_create(size_t n) __THROWNL;

/**
 * Destroy a given hash map.
 * Frees internal data and frees the given hash map.
 *
 * @param[out] hm The hash map.
 */
void hash_map_destroy(struct hash_map *hm) __THROWNL __nonnull((1));

/**
 * Get an entry's value by the given key if it exists.
 *
 * @param[in] hm The hash map.
 * @param[in] key The lookup key.
 * @param[out] out The value to populate.
 *    It's populated with all values stored in this key.
 * @return True on success, false for not found or error.
 */
bool hash_map_get(struct hash_map *hm, const char *key, void **out) __THROWNL __nonnull((1));

/**
 * Set a value in the hash for a lookup key.
 *
 * @param[in] hm The hash map.
 * @param[in] key The lookup key.
 * @param[in] value The value to store. A single value.
  */
bool hash_map_set(struct hash_map *hm, const char *key, void *value) __THROWNL __nonnull((1));

/**
 * Remove a key and value from the hash map.
 *
 * @param[in] hm The hash map.
 * @param[in] key The lookup key.
 * @return True for success, false otherwise.
 */
bool hash_map_remove(struct hash_map*hm, const char *key) __THROWNL __nonnull((1));

/**
 * Remove a specific value in the entry stored at the given lookup key.
 *
 * @param[in] hm The hash map.
 * @param[in] key The lookup key.
 * @param[in] value The specific value to remove.
 * @return True for success, false otherwise.
 */
bool hash_map_remove_value(struct hash_map* hm, const char *key, const void*) __THROWNL __nonnull((1));

__END_DECLS

#endif
