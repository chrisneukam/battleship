#include <stdlib.h>
#include "position.h"

#ifndef ABS
#define ABS(X) (((X) < 0) ? -(X) : (X))
#endif

static int swap(
  int* a,
  int* b
) {
  int error = 0;
  int tmp = 0;
  
  if ((NULL != a) && (NULL != b)) {
    tmp = *a;
    *a = *b;
    *b = tmp;
  } else {
    error = 1;
  }

  return error;
}

/* bubblesort */
int util_sort(
  int* data,
  const int length
) {
  int error = 0;
  int i = 0;
  int j = 0;

  if (NULL != data) {
    for (i = 0; i < length - 1; i++) {
      for (j = 0; j < length - i - 1; j++) {
        if (data[j] > data[j + 1]) {
          error = swap(&data[j], &data[j + 1]);
        }
      }
    }
  } else {
    error = 1;
  }

  return error;
}

int util_array_equal(
  int* data,
  const int length,
  int* allEqual
) {
  int error = 0;
  int idx = 0;
  int memory = 0;

  if ((NULL != data) && (NULL != allEqual)) {
    *allEqual = 1;
    memory = data[0];

    for (idx = 1; idx < length; idx++) {
      if (memory != data[idx]) {
        *allEqual = 0;
        break;
      }
    }
  } else {
    error = 1;
  }

  return error;
}

int util_array_sequence(
  int* data,
  const int length,
  int* sequencial
) {
  int error = 0;
  int idx = 0;

  if ((NULL != data) && (NULL != sequencial)) {
    *sequencial = 1;

    for (idx = 1; idx < length; idx++) {
      if (ABS(data[idx] - data[idx - 1]) != 1) {
        *sequencial = 0;
        break;
      }
    }
  } else {
    error = 1;
  }

  return error;
}

int util_position2string(
  char* string,
  const int length,
  const POSITION position
) {
  int error = 0;
  int idx = 0;

  if ((NULL != string) && (length >= 2)) {
    for (idx = 0; idx < length; idx++) {
      string[idx] = '\0';
    }

    if ((position.row >= POSITION_MIN) && (position.row <= POSITION_MAX)) {
      string[0] = (char)position.row + 'A';
    } else {
      error |= 1;
    }

    if ((position.column >= POSITION_MIN) && (position.column <= POSITION_MAX)) {
      string[1] = (char)position.column + '1';
    } else {
      error |= 1;
    }
  } else {
    error = 1;
  }

  return error;
}

int util_string2position(
  char* string,
  const int length,
  POSITION* position
) {
  int error = 0;

  if ((NULL != string) && (NULL != position) && (length >= 2)) {
    if ((string[0] >= 'a') && (string[0] <= 'z')) {
      position->row = (int)(string[0] - 'a');
    } else if ((string[0] >= 'A') && (string[0] <= 'Z')) {
      position->row = (int)(string[0] - 'A');
    } else {
      error |= 1;
    }

    if ((string[1] >= '1') && (string[1] <= '9')) {
      position->column = (int)(string[1] - '1');
    } else {
      error |= 1;
    }
  } else {
    error = 1;
  }

  return error;
}
