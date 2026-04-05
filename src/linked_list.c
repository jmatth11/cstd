#include <stdio.h>
#include <stdlib.h>

#include "headers/linked_list.h"

struct linked_list_t *linked_list_create(void *value) {
  struct linked_list_t *result = malloc(sizeof(struct linked_list_t));
  if (result == NULL) {
    return NULL;
  }
  linked_list_init(result);
  result->value = value;
  return result;
}

bool linked_list_init(struct linked_list_t *ll) {
  ll->next = NULL;
  ll->prev = NULL;
  ll->value = NULL;
  return true;
}

static inline struct linked_list_t *find_pos(struct linked_list_t *ll,
                                             size_t target_pos) {
  if (ll == NULL)
    return NULL;
  struct linked_list_t *cur = ll;
  size_t idx = 0;
  while (cur != NULL) {
    if (idx == target_pos) {
      break;
    }
    cur = cur->next;
    ++idx;
  }
  if (idx != target_pos) {
    return NULL;
  }
  return cur;
}

static inline struct linked_list_t *find_end(struct linked_list_t *ll) {
  if (ll == NULL)
    return NULL;
  struct linked_list_t *cur = ll;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  return cur;
}

struct linked_list_t *linked_list_head(struct linked_list_t *ll) {
  if (ll == NULL)
    return NULL;
  struct linked_list_t *cur = ll;
  while (cur->prev != NULL) {
    cur = cur->prev;
  }
  return cur;
}

static inline size_t find_len(struct linked_list_t *ll) {
  struct linked_list_t *cur = ll;
  size_t result = 0;
  while (cur != NULL) {
    ++result;
    cur = cur->next;
  }
  return result;
}

bool linked_list_insert(struct linked_list_t *ll, size_t pos, void *value) {
  struct linked_list_t *obj = NULL;
  // insertion happens at the index so we need the node just before
  // that index.
  if (pos > 0) {
    obj = find_pos(ll, pos - 1);
    if (obj == NULL) {
      return false;
    }
  }
  struct linked_list_t *tmp =
      (struct linked_list_t *)malloc(sizeof(struct linked_list_t));
  if (tmp == NULL)
    return false;
  linked_list_init(tmp);
  tmp->value = value;
  tmp->prev = obj;
  if (obj != NULL) {
    if (obj->next != NULL) {
      obj->next->prev = tmp;
      tmp->next = obj->next;
    }
    obj->next = tmp;
  } else {
    // if obj is null we are inserting a new head.
    tmp->next = ll;
  }
  return true;
}

bool linked_list_append(struct linked_list_t *ll, void *value) {
  struct linked_list_t *obj = find_end(ll);
  if (obj == NULL)
    return false;
  struct linked_list_t *tmp =
      (struct linked_list_t *)malloc(sizeof(struct linked_list_t));
  if (tmp == NULL)
    return false;
  linked_list_init(tmp);
  tmp->prev = obj;
  tmp->value = value;
  obj->next = tmp;
  return true;
}

struct linked_list_t *linked_list_get_pos(struct linked_list_t *ll,
                                          size_t pos) {
  return find_pos(ll, pos);
}

struct linked_list_t *linked_list_get_end(struct linked_list_t *ll) {
  return find_end(ll);
}

size_t linked_list_get_len(struct linked_list_t *ll) { return find_len(ll); }

struct linked_list_t *linked_list_delete_and_free(struct linked_list_t *ll,
                                                  size_t pos) {
  struct linked_list_t *result = ll;
  struct linked_list_t *obj = find_pos(ll, pos);
  if (obj == NULL)
    return ll;
  // we are deleting the head.
  if (pos == 0) {
    result = obj->next;
  }
  if (obj->prev != NULL) {
    obj->prev->next = obj->next;
  }
  if (obj->next != NULL) {
    obj->next->prev = obj->prev;
  }
  free(obj->value);
  linked_list_free(obj);
  return result;
}

struct linked_list_t *linked_list_delete(struct linked_list_t *ll, size_t pos) {
  struct linked_list_t *result = ll;
  struct linked_list_t *obj = find_pos(ll, pos);
  if (obj == NULL)
    return ll;
  // we are deleting the head.
  if (pos == 0) {
    result = obj->next;
  }
  if (obj->prev != NULL) {
    obj->prev->next = obj->next;
  }
  if (obj->next != NULL) {
    obj->next->prev = obj->prev;
  }
  linked_list_free(obj);
  return result;
}

struct linked_list_t *linked_list_delete_node(struct linked_list_t *ll) {
  struct linked_list_t *result = NULL;
  if (ll->prev != NULL) {
    result = ll->prev;
    ll->prev->next = ll->next;
  }
  if (ll->next != NULL) {
    if (result == NULL) {
      result = ll->next;
    }
    ll->next->prev = ll->prev;
  }
  linked_list_free(ll);
  return result;
}

void linked_list_free(struct linked_list_t *ll) {
  if (ll == NULL) {
    return;
  }
  ll->next = NULL;
  ll->prev = NULL;
  ll->value = NULL;
  free(ll);
}

void linked_list_free_all(struct linked_list_t *ll) {
  if (ll == NULL) {
    return;
  }
  struct linked_list_t *cur = ll;
  while (cur != NULL) {
    struct linked_list_t *n = cur->next;
    linked_list_free(cur);
    cur = n;
  }
}
