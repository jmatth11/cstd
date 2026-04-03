#include <stdio.h>
#include "headers/array_template.h"

generate_array_template(int, int);

int main(void) {
    int_array arr;

    if (!int_array_init(&arr, 4)) {
        fprintf(stderr, "Failed to initialize array\n");
        return 1;
    }
    printf("Initialized array with capacity: %zu\n", arr.cap);

    for (int i = 0; i < 10; i++) {
        if (!int_array_insert(&arr, i * 10)) {
            fprintf(stderr, "Failed to insert element\n");
            int_array_free(&arr);
            return 1;
        }
    }
    printf("Inserted 10 elements. Length: %zu, Capacity: %zu\n", arr.len, arr.cap);

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

    int_array_fast_remove(&arr, 0);
    printf("After fast remove at index 0: ");
    for (size_t i = 0; i < arr.len; i++) {
        int val;
        int_array_get(&arr, i, &val);
        printf("%d ", val);
    }
    printf("\n");

    int_array_free(&arr);
    printf("Array freed successfully\n");

    return 0;
}
