#ifndef CSTD_CRYPT_H
#define CSTD_CRYPT_H

#include "defs.h"

__BEGIN_DECLS

/**
 * Generate a hash representation of the given string.
 *
 * @param[in] str The string.
 * @return The hash value.
 */
unsigned long hash_from_str(const char *str) __THROWNL __nonnull((1));

__END_DECLS

#endif
