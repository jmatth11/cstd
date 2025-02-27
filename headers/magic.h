#ifndef CSTD_MAGIC_H
#define CSTD_MAGIC_H

#define macro_var(name) name##__LINE__
#define defer(start, end) for ( \
  int macro_var(_i_) = (start, 0); \
  !macro_var(_i_); \
  (macro_var(_i_) += 1), end) \

#endif
