#ifndef CSTD_DEFS_H
#define CSTD_DEFS_H

#ifdef __cplusplus

#ifndef __BEGIN_DECLS
#define __BEGIN_DECLS extern "C" {
#endif

#ifndef __END_DECLS
#define __END_DECLS }
#endif

#else

#define __BEGIN_DECLS
#define __END_DECLS

#endif

#ifndef __THROWNL
#define __THROWNL __attribute__((__nothrow__))
#endif

#ifndef __nonnull
#define __nonnull(params) __attribute__((__nonnull__ params))
#endif

#ifndef UNUSED
#define UNUSED __attribute__((unused))
#endif

#endif
