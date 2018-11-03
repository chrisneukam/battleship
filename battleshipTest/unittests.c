#include <stdlib.h>
#include "testFramework.h"
#include "unittests.h"
#include "common.h"
#include "ship.h"
#include "ai.h"
#include "randomGen.h"

int test_randomGen_rand(
  void
) {
  TESTRESULT error = OK;
  RANDOMGENERATOR* randomGen = NULL;
  const int length = 11;
  int memory[11] = {0};
  int run = 0;
  int run2 = 0;
  int cnt = 0;

  initialize_ranndomGen(&randomGen,
                        length);

  for (run = 0; run < length; run++) {
    memory[run] = randomGen_rand(randomGen);
  }

  for (run = 0; run < length; run++) {
    for (run2 = run; run2 < length; run2++) {
      if ((memory[run] == memory[run2]) && (run != run2)) {
        cnt++;
      }
    }
  }

  if (cnt > 0) {
    error = FAIL;
  }

  free_randomGen(&randomGen);

  return error;
}

int test_ai_getShootPosition(
  void
) {
  TESTRESULT error = OK;
  POSITION position[NUM_POSITIONS_ON_FIELD] = {0};
  AI* cpu_ai = NULL;
  int run = 0;
  int run2 = 0;
  int cnt = 0;

  initialize_ai(&cpu_ai);

  for (run = 0; run < NUM_POSITIONS_ON_FIELD; run++) {
    ai_getShootPosition(&position[run],
                        cpu_ai);

    if (position[run].row < POSITION_MIN || position[run].row > POSITION_MAX) {
      error = FAIL;
      break;
    }

    if (position[run].column < POSITION_MIN || position[run].column > POSITION_MAX) {
      error = FAIL;
      break;
    }
  }

  for (run = 0; run < NUM_POSITIONS_ON_FIELD; run++) {
    for (run2 = run; run2 < NUM_POSITIONS_ON_FIELD; run2++) {
      if ((position[run].row == position[run2].row) && (position[run].column == position[run2].column) && (run != run2)) {
        cnt++;
      }
    }

    if (cnt > 0) {
      break;
    }

    cnt = 0;
  }

  if (cnt > 0) {
    error = FAIL;
  }

  free_ai(&cpu_ai);

  return (int)error;
}
