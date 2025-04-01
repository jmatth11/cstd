#include "headers/queue.h"
#include "headers/linked_list.h"
#include <stdlib.h>

struct simple_queue_t {
  struct linked_list_t *head;
};

struct simple_queue_t* simple_queue_create() {
  struct simple_queue_t *result = malloc(sizeof(struct simple_queue_t));
  result->head = NULL;
  return result;
}
bool simple_queue_push(struct simple_queue_t *queue, void* entry) {
  if (queue->head == NULL) {
    queue->head = linked_list_create(entry);
    return true;
  }
  return linked_list_append(queue->head, entry);
}
bool simple_queue_pop(struct simple_queue_t *queue, void** out) {
  if (queue->head == NULL) return true;
  struct linked_list_t *node = queue->head;
  queue->head = node->next;
  *out = node->value;
  return linked_list_delete_node(node);
}
size_t simple_queue_len(struct simple_queue_t *queue) {
  if (queue->head == NULL) return 0;
  return linked_list_get_len(queue->head);
}
void simple_queue_destroy(struct simple_queue_t *queue) {
  if (queue->head != NULL) {
    linked_list_free_all(queue->head);
  }
  free(queue);
}
