#include <stdio.h>
#include "common.h"
#include "ship.h"
#include "ai.h"

static int testCnt = 0;
static int testFailedCnt = 0;

typedef enum _test_result {
  OK,
  FAIL
} TESTRESULT;

static void init_test(
          const char* functionName
) {
  fprintf(stdout, "===============================================================================\n");
  fprintf(stdout, "run test %s\n", functionName);

  testCnt++;
}

static void eval_test(
          const TESTRESULT testResult,
          const char* functionName
) {
  if (FAIL == testResult) {
    fprintf(stderr, "\tFAIL: %s returns %d\n", functionName, testResult);
    testFailedCnt++;
  }
}

static TESTRESULT run_test(
          const int testResult,
          const char* functionName
) {
  init_test(functionName);

  eval_test(testResult, functionName);

  return testResult;
}

static void printStatistic(void
) {
  fprintf(stdout, "===============================================================================\n\n");

  if (0 < testFailedCnt) {
    fprintf(stdout, "FAIL:\t%d\ttest(s) out of %d failed!\n", testFailedCnt, testCnt);
  }

  fprintf(stdout, "OK:\t%d\ttest(s) out of %d are ok!\n", testCnt - testFailedCnt, testCnt);
}

static TESTRESULT test_ki_getShootPosition(void
) {
  TESTRESULT error = OK;
  POSITION position;
  int run = 0;

  for (run = 0; run < 100000000; run++) {
    ki_getShootPosition(&position);

    if (position.row < 0 || position.row > 7) {
      error = FAIL;
      break;
    }

    if (position.column < 0 || position.column > 7) {
      error = FAIL;
      break;
    }
  }


  return error;
}

int main(int argc, char* argv[]
) {
  TESTRESULT error = 0;

  error = run_test(test_ki_getShootPosition(), "test_ki_getShootPosition()");

  printStatistic();

  return (int)error;
}