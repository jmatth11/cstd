#include "headers/log.h"

int main(void) {
  // ============================================================
  // Basic log messages
  // ============================================================
  info_log("This is an info message\n");
  debug_log("This is a debug message\n");
  error_log("This is an error message\n");

  // ============================================================
  // Formatted log messages
  // ============================================================
  info_log("Value: %d\n", 42);
  debug_log("String: %s, Float: %.2f\n", "hello", 3.14);
  error_log("Error code: %d\n", 404);

  // ============================================================
  // Color log messages
  // ============================================================
  color_log(LOG_COLOR_RED, "This is red text\n");
  color_log(LOG_COLOR_GREEN, "This is green text\n");
  color_log(LOG_COLOR_YELLOW, "This is yellow text\n");
  color_log(LOG_COLOR_BLUE, "This is blue text\n");
  color_log(LOG_COLOR_MAGENTA, "This is magenta text\n");
  color_log(LOG_COLOR_CYAN, "This is cyan text\n");

  // ============================================================
  // Bright color log messages
  // ============================================================
  color_log(LOG_COLOR_BRIGHT_RED, "This is bright red text\n");
  color_log(LOG_COLOR_BRIGHT_GREEN, "This is bright green text\n");
  color_log(LOG_COLOR_BRIGHT_YELLOW, "This is bright yellow text\n");

  // ============================================================
  // Detailed log messages with file/func/line info
  // ============================================================
  info_detailed("This is a detailed info message %s\n", "");
  debug_detailed("This is a detailed debug message with value %d\n", 100);
  error_detailed("This is a detailed error message %s\n", "");

  // ============================================================
  // Combined color and format
  // ============================================================
  color_log(LOG_COLOR_CYAN, "User: %s, Score: %d\n", "Alice", 95);

  return 0;
}
