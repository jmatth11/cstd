#include "headers/magic.h"

#include <stdlib.h>

void cstd_freep_fn(void **p) {
  if (*p == NULL)
    return;
  free(*p);
  *p = NULL;
}

void cstd_freec_fn(char **c) { cstd_freep_fn((void **)c); }
void cstd_freei_fn(int **i) { cstd_freep_fn((void **)i); }

void cstd_freed_fn(double **d) { cstd_freep_fn((void **)d); }

void cstd_freef_fn(float **f) { cstd_freep_fn((void **)f); }
