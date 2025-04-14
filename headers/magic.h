#ifndef CSTD_MAGIC_H
#define CSTD_MAGIC_H

#define DEFER(func) __attribute__((__cleanup__(func)))

extern inline void cstd_freep_fn(void**);
extern inline void cstd_freec_fn(char**);
extern inline void cstd_freei_fn(int**);
extern inline void cstd_freed_fn(double**);
extern inline void cstd_freef_fn(float**);

#define AUTO_P DEFER(cstd_freep_fn)
#define AUTO_C DEFER(cstd_freec_fn)
#define AUTO_I DEFER(cstd_freei_fn)
#define AUTO_D DEFER(cstd_freed_fn)
#define AUTO_F DEFER(cstd_freef_fn)

#endif
