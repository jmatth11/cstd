#ifndef CSTD_LOGGING_H
#define CSTD_LOGGING_H

#include "defs.h"

__BEGIN_DECLS

/**
 * Log colors for terminal output.
 */
typedef enum log_color {
    LOG_COLOR_DEFAULT,
    LOG_COLOR_RED,
    LOG_COLOR_GREEN,
    LOG_COLOR_YELLOW,
    LOG_COLOR_BLUE,
    LOG_COLOR_MAGENTA,
    LOG_COLOR_CYAN,
    LOG_COLOR_WHITE,
    LOG_COLOR_BRIGHT_RED,
    LOG_COLOR_BRIGHT_GREEN,
    LOG_COLOR_BRIGHT_YELLOW,
    LOG_COLOR_BRIGHT_BLUE,
    LOG_COLOR_BRIGHT_MAGENTA,
    LOG_COLOR_BRIGHT_CYAN,
    LOG_COLOR_BRIGHT_WHITE
} log_color;

/**
 * Log messages as INFO.
 *
 * @param[in] str The string to print.
 * @param[in] ... Options for the string.
 */
void info_log(const char *str, ...) __nonnull((1)) __format(1, 2);
/**
 * Log messages as DEBUG.
 *
 * @param[in] str The string to print.
 * @param[in] ... Options for the string.
 */
void debug_log(const char *str, ...) __nonnull((1)) __format(1, 2);
/**
 * Log messages as ERROR.
 *
 * @param[in] str The string to print.
 * @param[in] ... Options for the string.
 */
void error_log(const char *str, ...) __nonnull((1)) __format(1, 2);
/**
 * Log messages with a specific color.
 *
 * @param[in] color The color to use.
 * @param[in] str The string to print.
 * @param[in] ... Options for the string.
 */
void color_log(enum log_color color, const char *str, ...) __nonnull((2)) __format(2, 3);

/**
 * Log messages as INFO with debugging info.
 *
 * @param[in] str The string to print.
 * @param[in] ... Options for the string.
 */
#define info_detailed(str, ...) info_log("file:%s func:%s line:%d -- " str, __FILE__, __func__, __LINE__, __VA_ARGS__);
/**
 * Log messages as DEBUG with debugging info.
 *
 * @param[in] str The string to print.
 * @param[in] ... Options for the string.
 */
#define debug_detailed(str, ...) debug_log("file:%s func:%s line:%d -- " str, __FILE__, __func__, __LINE__, __VA_ARGS__);
/**
 * Log messages as ERROR with debugging info.
 *
 * @param[in] str The string to print.
 * @param[in] ... Options for the string.
 */
#define error_detailed(str, ...) error_log("file:%s func:%s line:%d -- " str, __FILE__, __func__, __LINE__, __VA_ARGS__);

__END_DECLS

#endif
