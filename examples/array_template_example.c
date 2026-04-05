#include "headers/array_template.h"
#include <stdio.h>

generate_array_template(int, int);

int main(void) {
  int_array arr;

  // initialize array with capacity 4
  if (!int_array_init(&arr, 4)) {
    fprintf(stderr, "Failed to initialize array\n");
    return 1;
  }
  printf("Initialized array with capacity: %zu\n", arr.cap);

  // insert 10 items
  for (int i = 0; i < 10; i++) {
    if (!int_array_insert(&arr, i * 10)) {
      fprintf(stderr, "Failed to insert element\n");
      int_array_free(&arr);
      return 1;
    }
  }
  printf("Inserted 10 elements. Length: %zu, Capacity: %zu\n", arr.len,
         arr.cap);

  // get items from the array
  printf("Array contents: ");
  for (size_t i = 0; i < arr.len; i++) {
    int val;
    int_array_get(&arr, i, &val);
    printf("%d ", val);
  }
  printf("\n");

  int value;
  int_array_get(&arr, 5, &value);
  printf("Element at index 5: %d\n", value);

  // fast remove, removes element by swapping it with the end element and
  // decrementing the array length by 1
  int_array_fast_remove(&arr, 0);
  printf("After fast remove at index 0: ");
  for (size_t i = 0; i < arr.len; i++) {
    int val;
    int_array_get(&arr, i, &val);
    printf("%d ", val);
  }
  printf("\n");

  // free the array
  int_array_free(&arr);
  printf("Array freed successfully\n");

  return 0;
}
