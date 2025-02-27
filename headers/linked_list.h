#ifndef CSTD_LINKED_LIST_H
#define CSTD_LINKED_LIST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
#define __THROWNL __attribute__((__nothrow__))
#define __nonnull(params) __attribute__((__nonnull__ params))

struct linked_list {
  struct linked_list *next;
  struct linked_list *prev;
  void* value;
};

int linked_list_init(struct linked_list *ll) __THROWNL __nonnull ((1));
int linked_list_insert(struct linked_list *ll, size_t pos, void* value) __THROWNL __nonnull ((1,3));
int linked_list_append(struct linked_list *ll, void* value) __THROWNL __nonnull ((1,2));
struct linked_list* linked_list_get_pos(struct linked_list *ll, size_t pos) __THROWNL __nonnull ((1));
struct linked_list* linked_list_get_end(struct linked_list *ll) __THROWNL __nonnull ((1));
size_t linked_list_get_len(struct linked_list *ll) __THROWNL __nonnull ((1));
int linked_list_delete(struct linked_list *ll, size_t pos) __THROWNL __nonnull ((1));
int linked_list_delete_node(struct linked_list *ll) __THROWNL __nonnull ((1));
void linked_list_free(struct linked_list *ll) __THROWNL __nonnull ((1));
void linked_list_free_all(struct linked_list *ll) __THROWNL __nonnull ((1));

#ifdef __cplusplus
}
#endif

#endif
