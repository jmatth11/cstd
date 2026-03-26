#include "headers/log.h"
#include <stdarg.h>
#include <stdio.h>

static const char *log_color_codes[] = {
    [LOG_COLOR_DEFAULT] = "\033[0m",
    [LOG_COLOR_RED] = "\033[31m",
    [LOG_COLOR_GREEN] = "\033[32m",
    [LOG_COLOR_YELLOW] = "\033[33m",
    [LOG_COLOR_BLUE] = "\033[34m",
    [LOG_COLOR_MAGENTA] = "\033[35m",
    [LOG_COLOR_CYAN] = "\033[36m",
    [LOG_COLOR_WHITE] = "\033[37m",
    [LOG_COLOR_BRIGHT_RED] = "\033[91m",
    [LOG_COLOR_BRIGHT_GREEN] = "\033[92m",
    [LOG_COLOR_BRIGHT_YELLOW] = "\033[93m",
    [LOG_COLOR_BRIGHT_BLUE] = "\033[94m",
    [LOG_COLOR_BRIGHT_MAGENTA] = "\033[95m",
    [LOG_COLOR_BRIGHT_CYAN] = "\033[96m",
    [LOG_COLOR_BRIGHT_WHITE] = "\033[97m"
};

void info_log(const char *str, ...) {
  va_list argp;
  va_start(argp, str);
  vfprintf(stdout, str, argp);
  va_end(argp);
}

void debug_log(const char *str, ...) {
  va_list argp;
  va_start(argp, str);
  vfprintf(stdout, str, argp);
  va_end(argp);
}

void error_log(const char *str, ...) {
  va_list argp;
  va_start(argp, str);
  vfprintf(stderr, str, argp);
  va_end(argp);
}

void color_log(enum log_color color, const char *str, ...) {
  if (color < 0 || color >= sizeof(log_color_codes) / sizeof(log_color_codes[0])) {
    color = LOG_COLOR_DEFAULT;
  }
  va_list argp;
  va_start(argp, str);
  printf("%s", log_color_codes[color]);
  vfprintf(stdout, str, argp);
  printf("%s", log_color_codes[LOG_COLOR_DEFAULT]);
  va_end(argp);
}
