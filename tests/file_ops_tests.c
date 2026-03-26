static const char *file_ops_suite_name = "file_ops";

#include "file_ops.h"
#include "log.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool test_copy_file_basic() {
  color_log(LOG_COLOR_CYAN, "test_copy_file_basic start\n");
  
  FILE *src = tmpfile();
  if (src == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp source file\n", file_ops_suite_name);
    return false;
  }
  
  const char *content = "hello world";
  fputs(content, src);
  fflush(src);
  fseek(src, 0, SEEK_SET);
  
  FILE *dst = tmpfile();
  if (dst == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp dest file\n", file_ops_suite_name);
    fclose(src);
    return false;
  }
  
  bool result = copy_file(src, dst);
  fclose(src);
  
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: copy_file returned false\n", file_ops_suite_name);
    fclose(dst);
    return false;
  }
  
  fseek(dst, 0, SEEK_SET);
  char buf[256] = {0};
  fread(buf, 1, sizeof(buf) - 1, dst);
  fclose(dst);
  
  if (strcmp(buf, content) != 0) {
    color_log(LOG_COLOR_RED, "%s: content mismatch - expected \"%s\", got \"%s\"\n", file_ops_suite_name, content, buf);
    return false;
  }
  
  return true;
}

static bool test_copy_file_empty() {
  color_log(LOG_COLOR_CYAN, "test_copy_file_empty start\n");
  
  FILE *src = tmpfile();
  if (src == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp source file\n", file_ops_suite_name);
    return false;
  }
  
  FILE *dst = tmpfile();
  if (dst == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp dest file\n", file_ops_suite_name);
    fclose(src);
    return false;
  }
  
  bool result = copy_file(src, dst);
  fclose(src);
  
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: copy_file returned false for empty file\n", file_ops_suite_name);
    fclose(dst);
    return false;
  }
  
  fseek(dst, 0, SEEK_END);
  long size = ftell(dst);
  fclose(dst);
  
  if (size != 0) {
    color_log(LOG_COLOR_RED, "%s: empty file copy should have size 0, got %ld\n", file_ops_suite_name, size);
    return false;
  }
  
  return true;
}

static bool test_copy_file_large() {
  color_log(LOG_COLOR_CYAN, "test_copy_file_large start\n");
  
  FILE *src = tmpfile();
  if (src == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp source file\n", file_ops_suite_name);
    return false;
  }
  
  size_t large_size = 1024 * 100;
  char *large_content = malloc(large_size);
  if (large_content == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to allocate memory\n", file_ops_suite_name);
    fclose(src);
    return false;
  }
  
  memset(large_content, 'A', large_size);
  large_content[large_size - 1] = '\0';
  
  fputs(large_content, src);
  free(large_content);
  fflush(src);
  fseek(src, 0, SEEK_SET);
  
  FILE *dst = tmpfile();
  if (dst == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp dest file\n", file_ops_suite_name);
    fclose(src);
    return false;
  }
  
  bool result = copy_file(src, dst);
  fclose(src);
  
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: copy_file returned false for large file\n", file_ops_suite_name);
    fclose(dst);
    return false;
  }
  
  fseek(dst, 0, SEEK_END);
  long dst_size = ftell(dst);
  fclose(dst);
  
  if (dst_size != (long)(large_size - 1)) {
    color_log(LOG_COLOR_RED, "%s: large file size mismatch - expected %zu, got %ld\n", file_ops_suite_name, large_size - 1, dst_size);
    return false;
  }
  
  return true;
}

static bool test_copy_file_binary() {
  color_log(LOG_COLOR_CYAN, "test_copy_file_binary start\n");
  
  FILE *src = tmpfile();
  if (src == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp source file\n", file_ops_suite_name);
    return false;
  }
  
  uint8_t binary_content[] = {0x00, 0x01, 0x02, 0xFF, 0xFE, 0xFD, 0x00, 0x7F};
  fwrite(binary_content, 1, sizeof(binary_content), src);
  fflush(src);
  fseek(src, 0, SEEK_SET);
  
  FILE *dst = tmpfile();
  if (dst == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp dest file\n", file_ops_suite_name);
    fclose(src);
    return false;
  }
  
  bool result = copy_file(src, dst);
  fclose(src);
  
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: copy_file returned false for binary\n", file_ops_suite_name);
    fclose(dst);
    return false;
  }
  
  fseek(dst, 0, SEEK_END);
  long size = ftell(dst);
  fseek(dst, 0, SEEK_SET);
  
  if (size != sizeof(binary_content)) {
    color_log(LOG_COLOR_RED, "%s: binary size mismatch - expected %zu, got %ld\n", file_ops_suite_name, sizeof(binary_content), size);
    fclose(dst);
    return false;
  }
  
  uint8_t read_content[16] = {0};
  fread(read_content, 1, sizeof(read_content), dst);
  fclose(dst);
  
  if (memcmp(binary_content, read_content, sizeof(binary_content)) != 0) {
    color_log(LOG_COLOR_RED, "%s: binary content mismatch\n", file_ops_suite_name);
    return false;
  }
  
  return true;
}

static bool test_copy_file_multiline() {
  color_log(LOG_COLOR_CYAN, "test_copy_file_multiline start\n");
  
  FILE *src = tmpfile();
  if (src == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp source file\n", file_ops_suite_name);
    return false;
  }
  
  const char *content = "line 1\nline 2\nline 3\n";
  fputs(content, src);
  fflush(src);
  fseek(src, 0, SEEK_SET);
  
  FILE *dst = tmpfile();
  if (dst == NULL) {
    color_log(LOG_COLOR_RED, "%s: failed to create temp dest file\n", file_ops_suite_name);
    fclose(src);
    return false;
  }
  
  bool result = copy_file(src, dst);
  fclose(src);
  
  if (!result) {
    color_log(LOG_COLOR_RED, "%s: copy_file returned false\n", file_ops_suite_name);
    fclose(dst);
    return false;
  }
  
  fseek(dst, 0, SEEK_END);
  long size = ftell(dst);
  fseek(dst, 0, SEEK_SET);
  
  if (size != (long)strlen(content)) {
    color_log(LOG_COLOR_RED, "%s: multiline size mismatch - expected %zu, got %ld\n", file_ops_suite_name, strlen(content), size);
    fclose(dst);
    return false;
  }
  
  char buf[256] = {0};
  fread(buf, 1, sizeof(buf) - 1, dst);
  fclose(dst);
  
  if (strcmp(buf, content) != 0) {
    color_log(LOG_COLOR_RED, "%s: multiline content mismatch\n", file_ops_suite_name);
    return false;
  }
  
  return true;
}

static void file_ops_tests() {
  int failures = 0;

  if (!test_copy_file_basic()) {
    color_log(LOG_COLOR_RED, "%s: test_copy_file_basic failed\n", file_ops_suite_name);
    failures++;
  }
  if (!test_copy_file_empty()) {
    color_log(LOG_COLOR_RED, "%s: test_copy_file_empty failed\n", file_ops_suite_name);
    failures++;
  }
  if (!test_copy_file_large()) {
    color_log(LOG_COLOR_RED, "%s: test_copy_file_large failed\n", file_ops_suite_name);
    failures++;
  }
  if (!test_copy_file_binary()) {
    color_log(LOG_COLOR_RED, "%s: test_copy_file_binary failed\n", file_ops_suite_name);
    failures++;
  }
  if (!test_copy_file_multiline()) {
    color_log(LOG_COLOR_RED, "%s: test_copy_file_multiline failed\n", file_ops_suite_name);
    failures++;
  }

  if (failures == 0) {
    color_log(LOG_COLOR_GREEN, "All file_ops tests passed\n");
  } else {
    color_log(LOG_COLOR_RED, "%d file_ops tests failed\n", failures);
  }
}
