#ifndef CSTD_MAGIC_H
#define CSTD_MAGIC_H

#include <stdlib.h>

#define DEFER(func) __attribute__((__cleanup__(func)))

static __attribute__((unused)) void __cstd_freep_fn(void **p) {
  if (*p == NULL) return;
  free(*p);
  *p = NULL;
}

#define AUTO_FREE DEFER(__cstd_freep_fn)

#endif
