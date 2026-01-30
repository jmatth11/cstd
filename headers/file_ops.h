#ifndef CSTD_FILE_OPS_H
#define CSTD_FILE_OPS_H

#include "defs.h"
#include <stdio.h>
#include <stdbool.h>

__BEGIN_DECLS

/**
 * Copy src file into dst file.
 *
 * @param[in] src The source file.
 * @param[in] dst The destination file.
 * @return True on success, false otherwise.
 */
bool copy_file(FILE *restrict src, FILE *restrict dst);

__END_DECLS

#endif
