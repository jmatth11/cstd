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
#ifndef __EMSCRIPTEN__
#define __THROWNL __attribute__((__nothrow__))
#else
#define __THROWNL
#endif
#endif

#ifndef __nonnull
#ifndef __EMSCRIPTEN__
#define __nonnull(params) __attribute__((__nonnull__ params))
#else
#define __nonnull(params)
#endif
#endif

#ifndef UNUSED
#ifndef __EMSCRIPTEN__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif

#endif
