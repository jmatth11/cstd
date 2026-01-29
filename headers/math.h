#ifndef CSTD_MATH_FUNC_H
#define CSTD_MATH_FUNC_H

#include <stdint.h>
#include "headers/defs.h"

#if defined (__clang__) || defined (__GNUC__)
typedef int32_t v4si __vector_size(16);
#else
#error "This header is only meant to be used with gcc or clang compilers"
#endif

#endif
