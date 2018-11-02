#include <stdlib.h>
#include <time.h>
#include "common.h"
#include "ai.h"

int ai_getShootPosition(
  POSITION* position
) {
  int error = 0;

  if (NULL != position) {
    /* initialize random seed: */
    srand((unsigned int)time(NULL));

    /* generate secret number between POSITION_MIN and POSITION_MAX: */
    position->row = rand() % POSITION_MAX + POSITION_MIN;
    position->column = rand() % POSITION_MAX + POSITION_MIN;
  } else {
    error = 1;
  }

  return error;
}
