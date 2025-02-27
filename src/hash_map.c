#include "headers/hash_map.h"
#include "headers/log.h"
#include "headers/crypt.h"
#include "headers/array_template.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct hash_map_entry_t {
  char *key;
  void *value;
};

generate_array_template(map_entry, struct hash_map_entry_t *)

generate_array_template(map, map_entry_array)

struct hash_map_t {
  map_array entries;
  pthread_mutex_t mutex;
};

static inline int mod(int hash, int cap) {
  return hash % cap;
}

static bool hash_map_add_new_entry(map_entry_array *row, const char *key, void* value) {
  struct hash_map_entry_t *entry = malloc(sizeof(struct hash_map_entry_t));
  size_t key_len = strlen(key);
  entry->key = malloc(sizeof(char) * (key_len+1));
  strncpy(entry->key, key, key_len);
  entry->key[key_len] = '\0';
  entry->value = value;;
  if (!map_entry_array_insert(row, entry)) {
    error_log("inserting new entry in hash map failed.\n");
    free(entry->key);
    free(entry);
    return false;
  }
  return true;
}

struct hash_map_t * hash_map_create(size_t N) {
  struct hash_map_t *hm = malloc(sizeof(struct hash_map_t));
  if (hm == NULL) {
    error_log("error hash map init.\n");
    return NULL;
  }
  if (!map_array_init(&hm->entries, N)) {
    free(hm);
    error_log("error hash map init entries.\n");
    return NULL;
  }
  if (pthread_mutex_init(&hm->mutex, NULL) < 0) {
    hash_map_destroy(hm, false);
    error_log("hash map mutex failed to initialize.\n");
    return NULL;
  }
  hm->entries.len = N;
  return hm;
}

void hash_map_destroy(struct hash_map_t *hm, bool free_value) {
  for (size_t i = 0; i < hm->entries.cap; ++i) {
    map_entry_array map_entry;
    map_array_get(&hm->entries, i, &map_entry);
    if (map_entry.len > 0) {
      for (size_t entry_idx = 0; entry_idx < map_entry.len; ++entry_idx) {
        struct hash_map_entry_t *entry = NULL;
        map_entry_array_get(&map_entry, entry_idx, &entry);
        if (entry != NULL) {
          free(entry->key);
          if (free_value && entry->value != NULL) {
            free(entry->value);
          }
          free(entry);
        }
      }
      map_entry_array_free(&map_entry);
    }
  }
  map_array_free(&hm->entries);
  pthread_mutex_destroy(&hm->mutex);
  free(hm);
}

bool hash_map_get(struct hash_map_t *hm, const char *key, void **out) {
  pthread_mutex_lock(&hm->mutex);
  int hash = hash_from_str(key);
  int idx = mod(hash, hm->entries.cap);
  size_t key_len = strlen(key);
  map_entry_array *row = &hm->entries.map_data[idx];
  if (row->map_entry_data == NULL) {
    pthread_mutex_unlock(&hm->mutex);
    return false;
  }
  bool result = false;
  for (size_t i = 0; i < row->len; ++i) {
    struct hash_map_entry_t *entry = NULL;
    map_entry_array_get(row, i, &entry);
    if (entry != NULL) {
      if (strncmp(entry->key, key, key_len) == 0) {
        *out = entry->value;
        result = true;
        break;
      }
    }
  }
  pthread_mutex_unlock(&hm->mutex);
  return result;
}

bool hash_map_set(struct hash_map_t *hm, const char *key, void *value) {
  pthread_mutex_lock(&hm->mutex);
  bool result = true;
  int hash = hash_from_str(key);
  int idx = mod(hash, hm->entries.cap);
  size_t key_len = strlen(key);
  bool exists = false;
  map_entry_array *row = &hm->entries.map_data[idx];
  if (row->map_entry_data == NULL) {
    if (!map_entry_array_init(row, 10)) {
      error_log("error init map entry in hash map get.\n");
      result = false;
    }
  } else {
    for (size_t i = 0; i < row->len; ++i) {
      struct hash_map_entry_t *existing_entry = NULL;
      map_entry_array_get(row, i, &existing_entry);
      if (existing_entry != NULL && strncmp(existing_entry->key, key, key_len) == 0) {
        exists = true;
        existing_entry->value = value;
        break;
      }
    }
  }
  if (result && !exists) {
    if (!hash_map_add_new_entry(row, key, value)) {
      result = false;
    }
  }
  pthread_mutex_unlock(&hm->mutex);
  return result;
}

bool hash_map_remove(struct hash_map_t* hm, const char *key) {
  pthread_mutex_lock(&hm->mutex);
  int hash = hash_from_str(key);
  int idx = mod(hash, hm->entries.cap);
  size_t key_len = strlen(key);
  map_entry_array *row = &hm->entries.map_data[idx];
  if (row->map_entry_data == NULL) {
    pthread_mutex_unlock(&hm->mutex);
    return false;
  }
  int remove_idx = -1;
  for (size_t i = 0; i < row->len; ++i) {
    struct hash_map_entry_t *existing_entry = NULL;
    map_entry_array_get(row, i, &existing_entry);
    if (existing_entry != NULL && strncmp(existing_entry->key, key, key_len) == 0) {
      remove_idx = i;
      free(existing_entry->key);
      free(existing_entry);
      break;
    }
  }
  bool result = false;
  if (remove_idx != -1) {
    result = true;
    map_entry_array_fast_remove(row, remove_idx);
  }
  pthread_mutex_unlock(&hm->mutex);
  return result;
}

bool hash_map_remove_and_get(struct hash_map_t* hm, const char *key, void **out) {
  pthread_mutex_lock(&hm->mutex);
  int hash = hash_from_str(key);
  int idx = mod(hash, hm->entries.cap);
  size_t key_len = strlen(key);
  map_entry_array *row = &hm->entries.map_data[idx];
  if (row->map_entry_data == NULL) {
    error_log("key does not exist.\n");
    pthread_mutex_unlock(&hm->mutex);
    return false;
  }
  int remove_idx = -1;
  for (size_t i = 0; i < row->len; ++i) {
    struct hash_map_entry_t *existing_entry = NULL;
    map_entry_array_get(row, i, &existing_entry);
    if (existing_entry != NULL && strncmp(existing_entry->key, key, key_len) == 0) {
      remove_idx = i;
      *out = existing_entry->value;
      break;
    }
  }
  bool found = remove_idx != -1;
  if (found) {
    map_entry_array_fast_remove(row, remove_idx);
  } else {
    error_log("hash map remove_value idx not found.\n");
  }
  pthread_mutex_unlock(&hm->mutex);
  return found;
}

