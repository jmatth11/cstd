#ifndef CSTD_UNICODE_STR_H
#define CSTD_UNICODE_STR_H

#include "utf8.h"
#include <stdint.h>

#include "array_template.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t code_point_t;

generate_array_template(char, char);

struct unicode_t {
  char_array str;
};



#ifdef __cplusplus
}
#endif

#endif
