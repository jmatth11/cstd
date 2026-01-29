#ifndef CSTD_FILE_OPS_H
#define CSTD_FILE_OPS_H

#include <stdio.h>
#include <stdbool.h>

/**
 * Copy src file into dst file.
 *
 * @param[in] src The source file.
 * @param[in] dst The destination file.
 * @return True on success, false otherwise.
 */
bool copy_file(FILE *restrict src, FILE *restrict dst);

#endif
