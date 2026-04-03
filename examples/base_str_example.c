#include <stdio.h>
#include "headers/base_str.h"

int main(void) {
    struct base_str_t str;
    enum base_str_error err = new_base_str(&str, 32);
    if (err != C_STR_NO_ERROR) {
        fprintf(stderr, "Failed to create base_str\n");
        return 1;
    }

    const char *init = "Hello";
    err = str.set(&str, init, 5);
    if (err != C_STR_NO_ERROR) {
        fprintf(stderr, "Failed to set string\n");
        free_base_str(&str);
        return 1;
    }
    printf("Initial string: %s (len=%d)\n", init, str.length(&str));

    err = str.append(&str, ", World!", 9);
    if (err != C_STR_NO_ERROR) {
        fprintf(stderr, "Failed to append string\n");
        free_base_str(&str);
        return 1;
    }
    printf("After append: ");
    char *out;
    str.copy(&str, &out);
    printf("%s (len=%d)\n", out, str.length(&str));
    free(out);

    char c;
    str.at(&str, 0, &c);
    printf("Character at index 0: %c\n", c);

    err = str.append(&str, " This is a test.", 16);
    if (err != C_STR_NO_ERROR) {
        fprintf(stderr, "Failed to append string\n");
        free_base_str(&str);
        return 1;
    }
    char *out2;
    str.copy(&str, &out2);
    printf("After second append: %s (len=%d)\n", out2, str.length(&str));
    free(out2);

    char *copy;
    str.copy(&str, &copy);
    printf("Copied string: %s\n", copy);
    free(copy);

    free_base_str(&str);
    printf("base_str freed successfully\n");

    return 0;
}
