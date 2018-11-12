#ifndef _UTIL_H_
#define _UTIL_H_

#include "position.h"

int util_sort(
  int* data,
  const int length
);

int util_array_equal(
  int* data,
  const int length,
  int* allEqual
);

int util_array_sequence(
  int* data,
  const int length,
  int* sequencial
);

int util_string2position(
  char* string,
  const int length,
  POSITION* position
);

int util_position2string(
  char* string,
  const int length,
  const POSITION position
);

#endif
