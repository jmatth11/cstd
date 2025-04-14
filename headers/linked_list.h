#ifndef CSTD_LINKED_LIST_H
#define CSTD_LINKED_LIST_H

#include "defs.h"
#include <stdbool.h>
#include <stddef.h>

__BEGIN_DECLS

struct linked_list_t {
  struct linked_list_t *next;
  struct linked_list_t *prev;
  void *value;
};

struct linked_list_t *linked_list_create(void *value) __THROWNL;

bool linked_list_init(struct linked_list_t *ll) __THROWNL __nonnull((1));

bool linked_list_insert(struct linked_list_t *ll, size_t pos,
                        void *value) __THROWNL __nonnull((1, 3));

bool linked_list_append(struct linked_list_t *ll, void *value) __THROWNL
    __nonnull((1, 2));

struct linked_list_t *linked_list_get_pos(struct linked_list_t *ll,
                                          size_t pos) __THROWNL __nonnull((1));

struct linked_list_t *linked_list_get_end(struct linked_list_t *ll) __THROWNL
    __nonnull((1));

size_t linked_list_get_len(struct linked_list_t *ll) __THROWNL __nonnull((1));

bool linked_list_delete(struct linked_list_t *ll, size_t pos) __THROWNL
    __nonnull((1));

bool linked_list_delete_node(struct linked_list_t *ll) __THROWNL __nonnull((1));

void linked_list_free(struct linked_list_t *ll) __THROWNL;

void linked_list_free_all(struct linked_list_t *ll) __THROWNL;

__END_DECLS

#endif
