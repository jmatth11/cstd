#ifndef CSTD_QUEUE_H
#define CSTD_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#include "defs.h"

/**
 * Simple queue structure.
 */
struct simple_queue_t;

/**
 * Create a simple queue.
 *
 * @return Simple queue structure.
 */
struct simple_queue_t* simple_queue_create();

/**
 * Push a new value onto the queue.
 *
 * @param[in] queue The simple queue.
 * @param[in] entry The entry to push.
 * @return True on success, false otherwise.
 */
bool simple_queue_push(struct simple_queue_t *queue, void* entry) __nonnull((1,2));

/**
 * Pop a value off the queue.
 *
 * @param[in] queue The simple queue.
 * @param[out] out The entry value.
 * @return True on success, false otherwise.
 */
bool simple_queue_pop(struct simple_queue_t *queue, void** out) __nonnull((1));

/**
 * Check if queue is empty.
 *
 * @param queue The simple queue.
 * @return True if empty, false otherwise.
 */
bool simple_queue_is_empty(struct simple_queue_t *queue) __nonnull((1));

/**
 * Return the length of the queue.
 *
 * @param[in] queue The simple queue.
 * @return The length of the queue.
 */
size_t simple_queue_len(struct simple_queue_t *queue) __nonnull((1));

/**
 * Destroy the given simple queue.
 *
 * @param[in] queue The simple queue.
 */
void simple_queue_destroy(struct simple_queue_t **queue) __nonnull((1));

#endif
