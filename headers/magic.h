#ifndef CSTD_MAGIC_H
#define CSTD_MAGIC_H

#include "defs.h"

__BEGIN_DECLS

/**
 * Defer a cleanup function to be called when the variable goes out of scope.
 * This is similar to Go's defer statement.
 *
 * @param func The cleanup function to call.
 *
 * Example usage:
 *   void cleanup_int(int *i) { free(i); }
 *   void example() {
 *     int *ptr __attribute__((__cleanup__(cleanup_int))) = malloc(sizeof(int));
 *   }
 */
#define DEFER(func) __attribute__((__cleanup__(func)))

/**
 * Free a void pointer and set it to NULL.
 *
 * @param[in,out] p The pointer to free.
 */
void cstd_freep_fn(void**);

/**
 * Free a char pointer and set it to NULL.
 *
 * @param[in,out] c The pointer to free.
 */
void cstd_freec_fn(char**);

/**
 * Free an int pointer and set it to NULL.
 *
 * @param[in,out] i The pointer to free.
 */
void cstd_freei_fn(int**);

/**
 * Free a double pointer and set it to NULL.
 *
 * @param[in,out] d The pointer to free.
 */
void cstd_freed_fn(double**);

/**
 * Free a float pointer and set it to NULL.
 *
 * @param[in,out] f The pointer to free.
 */
void cstd_freef_fn(float**);

/**
 * Auto-cleanup macro for void pointers.
 * Use with: void *ptr AUTO_P;
 */
#define AUTO_P DEFER(cstd_freep_fn)

/**
 * Auto-cleanup macro for char pointers.
 * Use with: char *ptr AUTO_C;
 */
#define AUTO_C DEFER(cstd_freec_fn)

/**
 * Auto-cleanup macro for int pointers.
 * Use with: int *ptr AUTO_I;
 */
#define AUTO_I DEFER(cstd_freei_fn)

/**
 * Auto-cleanup macro for double pointers.
 * Use with: double *ptr AUTO_D;
 */
#define AUTO_D DEFER(cstd_freed_fn)

/**
 * Auto-cleanup macro for float pointers.
 * Use with: float *ptr AUTO_F;
 */
#define AUTO_F DEFER(cstd_freef_fn)

__END_DECLS

#endif
