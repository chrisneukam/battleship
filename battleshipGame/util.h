#ifndef _UTIL_H_
#define _UTIL_H_

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

#endif
