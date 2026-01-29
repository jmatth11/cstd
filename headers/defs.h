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

/**
 * Marks a function as non-throwable.
 */
#ifndef __THROWNL
#ifndef __EMSCRIPTEN__
#define __THROWNL __attribute__((__nothrow__))
#else
#define __THROWNL
#endif
#endif

/**
 * Mark parameters on a function as nonnull.
 *
 * Example: void func(int *a, char *b) __nonnull((2));
 * In the example parameter 2 cannot be passed NULL.
 *
 * However this does not stop someone from passing in a nulled
 * "char *" variable. The person still has to check their own variables
 * before passing them in.
 */
#ifndef __nonnull
#ifndef __EMSCRIPTEN__
#define __nonnull(params) __attribute__((__nonnull__ params))
#else
#define __nonnull(params)
#endif
#endif

/**
 * Mark function as possibly unused.
 */
#ifndef UNUSED
#ifndef __EMSCRIPTEN__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif

/**
 * Mark function as deprecated.
 *
 * Example: __deprecated("Use version x of this function") void do_thing();
 */
#ifndef __deprecated
#ifndef __EMSCRIPTEN__
#define __deprecated(msg) __attribute__((deprecated msg))
#else
#define __deprecated
#endif
#endif

/**
 * Mark a function as constaint.
 * Meaning it has no side effects to allow the compiler to optimize.
 *
 * Example: void immut_func() __const;
 */
#ifndef __const
#ifndef __EMSCRIPTEN__
#define __const __attribute__((const))
#else
#define __const
#endif
#endif

/**
 * Specifies an argument to a function is a file descriptor.
 * This allows -fanalyzer to through warnings about if the file descriptor
 * has been closed before passing in.
 */
#ifndef __fd_arg
#ifndef __EMSCRIPTEN__
#define __fd_arg(N) __attribute__((fd_arg N))
#else
#define __const
#endif
#endif

#endif
