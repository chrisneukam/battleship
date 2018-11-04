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
  int error = 0;
  TESTRESULT result = OK;
  RANDOMGENERATOR* randomGen = NULL;
  const int length = 11;
  int memory[11] = {0};
  int run = 0;
  int run2 = 0;
  int cnt = 0;

  error = ranndomGen_initialize(&randomGen,
                                length);

  if (0 == error) {
    for (run = 0; run < length; run++) {
      memory[run] = randomGen_rand(randomGen);
    }

    /* TEST: each value returned by X rus of the random generator shall be unique */
    for (run = 0; run < length; run++) {
      for (run2 = run; run2 < length; run2++) {
        if ((memory[run] == memory[run2]) && (run != run2)) {
          cnt++;
        }
      }
    }
    if (cnt > 0) {
      result = FAIL;
    }

    error = randomGen_free(&randomGen);
    if (0 != error) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_ai_getShootPosition_range(
  void
) {
  int error = 0;
  TESTRESULT result = OK;
  POSITION position = {0};
  AI* cpu_ai = NULL;
  int run = 0;

  error = ai_initialize(&cpu_ai);

  if (0 == error) {
    for (run = 0; run < NUM_POSITIONS_ON_FIELD; run++) {
      error = ai_getShootPosition(&position,
                                  cpu_ai);
      if (0 != error) {
        result = FAIL;
        break;
      }

      /* TEST: row shall be in the allowed range */
      if (position.row < POSITION_MIN || position.row > POSITION_MAX) {
        result = FAIL;
        break;
      }

      /* TEST: column shall be in the allowed range */
      if (position.column < POSITION_MIN || position.column > POSITION_MAX) {
        result = FAIL;
        break;
      }
    }

    error = ai_free(&cpu_ai);
    if (0 != error) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_ai_getShootPosition_unique(
  void
) {
  int error = 0;
  TESTRESULT result = OK;
  POSITION position[NUM_POSITIONS_ON_FIELD] = {0};
  AI* cpu_ai = NULL;
  int run = 0;
  int run2 = 0;
  int cnt = 0;

  error = ai_initialize(&cpu_ai);

  if (0 == error) {
    for (run = 0; run < NUM_POSITIONS_ON_FIELD; run++) {
      error = ai_getShootPosition(&position[run],
                                  cpu_ai);
      if (0 != error) {
        result = FAIL;
        break;
      }
    }

    if (OK == result) {
      /* TEST: each position returned by NUM_POSITIONS_ON_FIELD rus of the shooting shall be unique */
      for (run = 0; run < NUM_POSITIONS_ON_FIELD; run++) {
        for (run2 = run; run2 < NUM_POSITIONS_ON_FIELD; run2++) {
          if ((position[run].row == position[run2].row) && (position[run].column == position[run2].column) && (run != run2)) {
            cnt++;
          }
        }

        if (cnt > 0) {
          break;
        } else {
          cnt = 0;
        }
      }
      if (cnt > 0) {
        result = FAIL;
      }
    }

    error = ai_free(&cpu_ai);
    if (0 != error) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}
