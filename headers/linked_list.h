#ifndef CSTD_LINKED_LIST_H
#define CSTD_LINKED_LIST_H

#include "defs.h"
#include <stdbool.h>
#include <stddef.h>

__BEGIN_DECLS

/**
 * Linked list node structure.
 */
struct linked_list_t {
  /** Pointer to the next node in the list. */
  struct linked_list_t *next;
  /** Pointer to the previous node in the list. */
  struct linked_list_t *prev;
  /** Pointer to the value stored in this node. */
  void *value;
};

/**
 * Create a new linked list node with the given value.
 *
 * @param[in] value The value to store in the node.
 * @return The newly created linked list node, NULL on error.
 */
struct linked_list_t *linked_list_create(void *value) __THROWNL;

/**
 * Initialize an existing linked list node.
 *
 * @param[in] ll The linked list node to initialize.
 * @return True on success, false on error.
 */
bool linked_list_init(struct linked_list_t *ll) __THROWNL __nonnull((1));

/**
 * Insert a value at the specified position in the linked list.
 *
 * @param[in] ll The linked list node (head of list).
 * @param[in] pos The position at which to insert the value.
 * @param[in] value The value to insert.
 * @return True on success, false on error.
 */
bool linked_list_insert(struct linked_list_t *ll, size_t pos,
                        void *value) __THROWNL __nonnull((1, 3));

/**
 * Append a value to the end of the linked list.
 *
 * @param[in] ll The linked list node (head of list).
 * @param[in] value The value to append.
 * @return True on success, false on error.
 */
bool linked_list_append(struct linked_list_t *ll, void *value) __THROWNL
    __nonnull((1, 2));

/**
 * Get the node at the specified position in the linked list.
 *
 * @param[in] ll The linked list node (head of list).
 * @param[in] pos The position of the node to retrieve.
 * @return The node at the specified position, NULL if not found.
 */
struct linked_list_t *linked_list_get_pos(struct linked_list_t *ll,
                                          size_t pos) __THROWNL __nonnull((1));

/**
 * Get the last node in the linked list.
 *
 * @param[in] ll The linked list node (head of list).
 * @return The last node in the list, NULL if error.
 */
struct linked_list_t *linked_list_get_end(struct linked_list_t *ll) __THROWNL
    __nonnull((1));

/**
 * Get the head of the given linked list.
 *
 * @param[in] ll A linked list node.
 * @returns The head linked list.
 */
struct linked_list_t *linked_list_head(struct linked_list_t *ll) __THROWNL;

/**
 * Get the length (number of nodes) in the linked list.
 *
 * @param[in] ll The linked list node (head of list).
 * @return The number of nodes in the list.
 */
size_t linked_list_get_len(struct linked_list_t *ll) __THROWNL __nonnull((1));

/**
 * Delete the node at the specified position in the linked list.
 *
 * @param[in] ll The linked list node (head of list).
 * @param[in] pos The position of the node to delete.
 * @return The new head of the list (may change if first node is deleted).
 */
struct linked_list_t* linked_list_delete(struct linked_list_t *ll, size_t pos) __THROWNL
    __nonnull((1));

/**
 * Delete the specified node from the linked list.
 *
 * @param[in] ll The node to delete.
 * @return The next node in the list, or NULL if none.
 */
struct linked_list_t* linked_list_delete_node(struct linked_list_t *ll) __THROWNL __nonnull((1));

/**
 * Free a single linked list node.
 * Does not free subsequent nodes or the value.
 *
 * @param[in] ll The node to free.
 */
void linked_list_free(struct linked_list_t *ll) __THROWNL;

/**
 * Free all linked list nodes starting from the given node.
 *
 * @param[in] ll The head of the list to free.
 */
void linked_list_free_all(struct linked_list_t *ll) __THROWNL;

__END_DECLS

#endif
