#include "headers/queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // ============================================================
  // Create queue
  // ============================================================
  struct simple_queue_t *queue = simple_queue_create();
  if (queue == NULL) {
    fprintf(stderr, "Failed to create queue\n");
    return 1;
  }
  printf("Queue created\n");

  // ============================================================
  // Check empty queue
  // ============================================================
  printf("Is empty: %s\n", simple_queue_is_empty(queue) ? "yes" : "no");
  printf("Queue length: %zu\n", simple_queue_len(queue));

  // ============================================================
  // Push values onto queue
  // ============================================================
  int *val1 = malloc(sizeof(int));
  *val1 = 10;
  int *val2 = malloc(sizeof(int));
  *val2 = 20;
  int *val3 = malloc(sizeof(int));
  *val3 = 30;

  simple_queue_push(queue, val1);
  simple_queue_push(queue, val2);
  simple_queue_push(queue, val3);
  printf("Pushed 3 values\n");

  printf("Queue length: %zu\n", simple_queue_len(queue));
  printf("Is empty: %s\n", simple_queue_is_empty(queue) ? "yes" : "no");

  // ============================================================
  // Pop values from queue (FIFO order)
  // ============================================================
  void *out = NULL;
  simple_queue_pop(queue, &out);
  printf("Popped: %d\n", *(int *)out);
  free(out);

  simple_queue_pop(queue, &out);
  printf("Popped: %d\n", *(int *)out);
  free(out);

  simple_queue_pop(queue, &out);
  printf("Popped: %d\n", *(int *)out);
  free(out);

  printf("Queue length after popping all: %zu\n", simple_queue_len(queue));
  printf("Is empty: %s\n", simple_queue_is_empty(queue) ? "yes" : "no");

  // ============================================================
  // Push and pop multiple times
  // ============================================================
  for (int i = 1; i <= 5; i++) {
    int *v = malloc(sizeof(int));
    *v = i * 100;
    simple_queue_push(queue, v);
  }
  printf("Pushed 5 more values (100, 200, 300, 400, 500)\n");

  printf("Queue length: %zu\n", simple_queue_len(queue));

  printf("Popping all:\n");
  while (!simple_queue_is_empty(queue)) {
    simple_queue_pop(queue, &out);
    printf("  Popped: %d\n", *(int *)out);
    free(out);
  }

  // ============================================================
  // Destroy queue
  // ============================================================
  simple_queue_destroy(&queue);
  printf("Queue destroyed\n");

  return 0;
}
