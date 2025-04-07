#ifndef CSTD_MAGIC_H
#define CSTD_MAGIC_H

#include <stdlib.h>

#define DEFER(func) __attribute__((__cleanup__(func)))

inline void cstd_freep_fn(void**);
inline void cstd_freec_fn(char**);
inline void cstd_freei_fn(int**);
inline void cstd_freed_fn(double**);
inline void cstd_freef_fn(float**);

#define AUTO_P DEFER(__cstd_freep_fn)
#define AUTO_C DEFER(__cstd_freec_fn)
#define AUTO_I DEFER(__cstd_freei_fn)
#define AUTO_D DEFER(__cstd_freed_fn)
#define AUTO_F DEFER(__cstd_freef_fn)

#endif
