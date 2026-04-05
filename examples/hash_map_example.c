#include "headers/hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // ============================================================
  // Create hash map
  // ============================================================
  struct hash_map_t *hm = hash_map_create(16);
  if (hm == NULL) {
    fprintf(stderr, "Failed to create hash map\n");
    return 1;
  }
  printf("Hash map created\n");

  // ============================================================
  // Set values with string keys
  // ============================================================
  // Note: Values must be heap-allocated if free_value=true is used
  // when destroying the hash map
  int *num1 = malloc(sizeof(int));
  *num1 = 42;
  int *num2 = malloc(sizeof(int));
  *num2 = 100;
  double *pi = malloc(sizeof(double));
  *pi = 3.14159;
  char *str = malloc(32);
  snprintf(str, 32, "Hello, Hash Map!");

  hash_map_set(hm, "number_one", num1);
  hash_map_set(hm, "number_two", num2);
  hash_map_set(hm, "pi", pi);
  hash_map_set(hm, "message", str);

  printf("Set 4 key-value pairs\n");

  // ============================================================
  // Get values
  // ============================================================
  void *val = NULL;
  if (hash_map_get(hm, "number_one", &val)) {
    printf("number_one = %d\n", *(int *)val);
  }
  if (hash_map_get(hm, "number_two", &val)) {
    printf("number_two = %d\n", *(int *)val);
  }
  if (hash_map_get(hm, "pi", &val)) {
    printf("pi = %f\n", *(double *)val);
  }
  if (hash_map_get(hm, "message", &val)) {
    printf("message = %s\n", (char *)val);
  }

  // ============================================================
  // Update existing key
  // ============================================================
  int *new_num = malloc(sizeof(int));
  *new_num = 999;
  // Note: set does not automatically free the original value, so
  // we do it manually. Use hash_map_set_and_free to handle this automatically.
  free(num1);
  hash_map_set(hm, "number_one", new_num);
  printf("Updated number_one to %d\n", *new_num);

  int *new_num2 = malloc(sizeof(int));
  *new_num2 = 420;
  hash_map_set_and_free(hm, "number_two", new_num2);
  printf("Updated number_two to %d\n", *new_num2);

  // ============================================================
  // Iterate over hash map
  // ============================================================
  printf("Iterating over hash map:\n");
  struct hash_map_iterator_t *it = hash_map_iterator(hm);
  struct hash_map_entry_t *entry = NULL;
  while ((entry = hash_map_iterator_next(it)) != NULL) {
    printf("  key: %s\n", entry->key);
  }
  free(it);

  // ============================================================
  // Remove a key
  // ============================================================
  void *removed = NULL;
  if (hash_map_remove_and_get(hm, "number_two", &removed)) {
    free(removed);
  }
  printf("Removed number_two\n");

  // ============================================================
  // Remove and get value
  // ============================================================
  void *removed_val = NULL;
  if (hash_map_remove_and_get(hm, "pi", &removed_val)) {
    printf("Removed pi, value was %f\n", *(double *)removed_val);
    free(removed_val);
  }

  // ============================================================
  // Destroy hash map
  // ============================================================
  // Note: Using free_value=true frees stored values for you,
  // otherwise you'd need to free them manually.
  hash_map_destroy(&hm, true);
  printf("Hash map destroyed\n");

  return 0;
}
