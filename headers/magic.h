#ifndef CSTD_MAGIC_H
#define CSTD_MAGIC_H

#include "defs.h"

__BEGIN_DECLS

#define DEFER(func) __attribute__((__cleanup__(func)))

void cstd_freep_fn(void**);
void cstd_freec_fn(char**);
void cstd_freei_fn(int**);
void cstd_freed_fn(double**);
void cstd_freef_fn(float**);

#define AUTO_P DEFER(cstd_freep_fn)
#define AUTO_C DEFER(cstd_freec_fn)
#define AUTO_I DEFER(cstd_freei_fn)
#define AUTO_D DEFER(cstd_freed_fn)
#define AUTO_F DEFER(cstd_freef_fn)

__END_DECLS

#endif
