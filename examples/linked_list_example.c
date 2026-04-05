#include "headers/linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // ============================================================
  // Create linked list
  // ============================================================
  struct linked_list_t *list = linked_list_create(NULL);
  if (list == NULL) {
    fprintf(stderr, "Failed to create linked list\n");
    return 1;
  }
  printf("Linked list created\n");

  // ============================================================
  // Append values to the list
  // ============================================================
  int *val1 = malloc(sizeof(int));
  *val1 = 10;
  int *val2 = malloc(sizeof(int));
  *val2 = 20;
  int *val3 = malloc(sizeof(int));
  *val3 = 30;

  linked_list_append(list, val1);
  linked_list_append(list, val2);
  linked_list_append(list, val3);
  printf("Appended 3 values\n");

  // ============================================================
  // Get length of list
  // ============================================================
  printf("List length: %zu\n", linked_list_get_len(list));

  // ============================================================
  // Get values at specific positions
  // ============================================================
  struct linked_list_t *node = linked_list_get_pos(list, 0);
  if (node != NULL && node->value != NULL) {
    printf("Value at pos 0: %d\n", *(int *)node->value);
  }
  node = linked_list_get_pos(list, 1);
  if (node != NULL && node->value != NULL) {
    printf("Value at pos 1: %d\n", *(int *)node->value);
  }
  node = linked_list_get_pos(list, 2);
  if (node != NULL && node->value != NULL) {
    printf("Value at pos 2: %d\n", *(int *)node->value);
  }

  // ============================================================
  // Insert a value at position 1
  // ============================================================
  int *val_insert = malloc(sizeof(int));
  *val_insert = 15;
  linked_list_insert(list, 1, val_insert);
  printf("Inserted %d at position 1\n", *val_insert);

  // ============================================================
  // Get values after insertion
  // ============================================================
  printf("List length after insert: %zu\n", linked_list_get_len(list));
  for (size_t i = 0; i < linked_list_get_len(list); i++) {
    node = linked_list_get_pos(list, i);
    if (node != NULL && node->value != NULL) {
      printf("Value at pos %zu: %d\n", i, *(int *)node->value);
    }
  }

  // ============================================================
  // Get last node
  // ============================================================
  struct linked_list_t *last = linked_list_get_end(list);
  if (last != NULL && last->value != NULL) {
    printf("Last value: %d\n", *(int *)last->value);
  }

  // ============================================================
  // Get head of list
  // ============================================================
  struct linked_list_t *head = linked_list_head(list);
  if (head != NULL && head->value != NULL) {
    printf("Head value: %d\n", *(int *)head->value);
  }

  // ============================================================
  // Delete node at position 2
  // ============================================================
  // Note: we use the delete_and_free variant so it cleans up the value for us.
  list = linked_list_delete_and_free(list, 2);
  printf("Deleted node at position 2\n");
  printf("List length after delete: %zu\n", linked_list_get_len(list));

  // ============================================================
  // Print remaining values
  // ============================================================
  printf("Remaining values:\n");
  for (size_t i = 0; i < linked_list_get_len(list); i++) {
    node = linked_list_get_pos(list, i);
    if (node != NULL && node->value != NULL) {
      printf("  pos %zu: %d\n", i, *(int *)node->value);
    }
  }

  // ============================================================
  // Free all nodes and their values
  // ============================================================
  struct linked_list_t *cur = list;
  while (cur != NULL) {
    free(cur->value);
    cur = cur->next;
  }
  linked_list_free_all(list);
  printf("Linked list freed\n");

  return 0;
}
