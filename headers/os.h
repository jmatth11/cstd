#ifndef CSTD_OS_FUNCTIONS_H
#define CSTD_OS_FUNCTIONS_H

#include "defs.h"
#include <stdbool.h>

__BEGIN_DECLS

/**
 * Check if system is little endian or big.
 * @return True for little, false for big.
 */
inline bool is_little_endian();

__END_DECLS

#endif
