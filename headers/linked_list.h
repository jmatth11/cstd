#ifndef CSTD_LINKED_LIST_H
#define CSTD_LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include "defs.h"

__BEGIN_DECLS

struct linked_list {
  struct linked_list *next;
  struct linked_list *prev;
  void* value;
};

bool linked_list_init(struct linked_list *ll) __THROWNL __nonnull ((1));
bool linked_list_insert(struct linked_list *ll, size_t pos, void* value) __THROWNL __nonnull ((1,3));
bool linked_list_append(struct linked_list *ll, void* value) __THROWNL __nonnull ((1,2));
struct linked_list* linked_list_get_pos(struct linked_list *ll, size_t pos) __THROWNL __nonnull ((1));
struct linked_list* linked_list_get_end(struct linked_list *ll) __THROWNL __nonnull ((1));
size_t linked_list_get_len(struct linked_list *ll) __THROWNL __nonnull ((1));
bool linked_list_delete(struct linked_list *ll, size_t pos) __THROWNL __nonnull ((1));
bool linked_list_delete_node(struct linked_list *ll) __THROWNL __nonnull ((1));
void linked_list_free(struct linked_list *ll) __THROWNL __nonnull ((1));
void linked_list_free_all(struct linked_list *ll) __THROWNL __nonnull ((1));

__END_DECLS

#endif
