#include "headers/os.h"

#include <stdint.h>

bool is_little_endian(void) {
  uint16_t tmp = 1;
  const uint8_t *raw = (const uint8_t *)&tmp;
  return raw[0] == 1;
}
