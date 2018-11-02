#include "testFramework.h"
#include "unittests.h"
#include "common.h"
#include "ship.h"
#include "ai.h"

int test_ai_getShootPosition(
  void
) {
  TESTRESULT error = OK;
  POSITION position;
  int run = 0;

  for (run = 0; run < 100000000; run++) {
    ai_getShootPosition(&position);

    if (position.row < 0 || position.row > 7) {
      error = FAIL;
      break;
    }

    if (position.column < 0 || position.column > 7) {
      error = FAIL;
      break;
    }
  }

  return (int)error;
}
