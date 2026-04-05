#include "headers/gap_buffer.h"
#include <stdio.h>

int main(void) {
  // initialize gap buffer
  struct gap_buffer_t gb;
  if (!gap_buffer_init(&gb, 64)) {
    fprintf(stderr, "Failed to initialize gap buffer\n");
    return 1;
  }

  // print length
  printf("Initial length: %zu\n", gap_buffer_get_len(&gb));

  // --------------------------------
  // insert characters into gap buffer
  gap_buffer_insert(&gb, 'H');
  gap_buffer_insert(&gb, 'e');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'o');
  gap_buffer_insert(&gb, '!');
  printf("After inserting 'Hello!': %zu\n", gap_buffer_get_len(&gb));

  // --------------------------------
  // move cursor and insert into buffer
  gap_buffer_move_cursor(&gb, 5);
  gap_buffer_insert(&gb, ' ');
  gap_buffer_insert(&gb, 'W');
  gap_buffer_insert(&gb, 'o');
  gap_buffer_insert(&gb, 'r');
  gap_buffer_insert(&gb, 'l');
  gap_buffer_insert(&gb, 'd');
  printf("After inserting ' World': %zu\n", gap_buffer_get_len(&gb));

  // --------------------------------
  // getting the string from a gap buffer
  code_point_t *str = gap_buffer_get_str(&gb);
  printf("Content: ");
  for (size_t i = 0; i < gap_buffer_get_len(&gb); i++) {
    printf("%c", (char)str[i]);
  }
  printf("\n");
  free(str);

  // --------------------------------
  // move and delete character at certain position
  gap_buffer_move_cursor(&gb, 5);
  gap_buffer_delete(&gb);
  printf("After delete at pos 5, length: %zu\n", gap_buffer_get_len(&gb));

  str = gap_buffer_get_str(&gb);
  printf("Content after delete: ");
  for (size_t i = 0; i < gap_buffer_get_len(&gb); i++) {
    printf("%c", (char)str[i]);
  }
  printf("\n");
  free(str);

  // --------------------------------
  // Delete sequence from gap buffer
  gap_buffer_move_cursor(&gb, 10);
  gap_buffer_delete_seq(&gb, 6);
  printf("After deleting 6 chars to left of pos 10, length: %zu\n",
         gap_buffer_get_len(&gb));

  str = gap_buffer_get_str(&gb);
  printf("Content after seq delete: ");
  for (size_t i = 0; i < gap_buffer_get_len(&gb); i++) {
    printf("%c", (char)str[i]);
  }
  printf("\n");
  free(str);

  // --------------------------------
  // Insert "word" into gap buffer.
  gap_buffer_move_cursor(&gb, 4);
  code_point_t word[] = {'W', 'o', 'r', 'd', 's'};
  gap_buffer_insert_word(&gb, 4, word, 5);
  printf("After inserting 'Words' at pos 4, length: %zu\n",
         gap_buffer_get_len(&gb));

  str = gap_buffer_get_str(&gb);
  printf("Content after insert_word: ");
  for (size_t i = 0; i < gap_buffer_get_len(&gb); i++) {
    printf("%c", (char)str[i]);
  }
  printf("\n");
  free(str);

  // --------------------------------
  // Free gap buffer
  gap_buffer_free(&gb);
  printf("Gap buffer freed successfully\n");

  return 0;
}
