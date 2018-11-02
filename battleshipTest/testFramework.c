#include <stdio.h>
#include "testFramework.h"

static int testCnt = 0;
static int testFailedCnt = 0;

void init_test(
          const char* functionName
) {
  fprintf(stdout, "===============================================================================\n");
  fprintf(stdout, "run test %s\n", functionName);

  testCnt++;
}

void eval_test(
          const TESTRESULT testResult,
          const char* functionName
) {
  if (FAIL == testResult) {
    fprintf(stderr, "\tFAIL: %s returns %d\n", functionName, testResult);
    testFailedCnt++;
  }
}

TESTRESULT run_test(
          const int testResult,
          const char* functionName
) {
  TESTRESULT result = OK;
  init_test(functionName);

  if (testResult < 0 || testResult > 1) {
    result = FAIL;
  } else {
    result = (TESTRESULT)testResult;
  }

  eval_test(testResult, functionName);

  return testResult;
}

void printStatistic(
          void
) {
  fprintf(stdout, "===============================================================================\n\n");

  if (0 < testFailedCnt) {
    fprintf(stdout, "FAIL:\t%d\ttest(s) out of %d failed!\n", testFailedCnt, testCnt);
  }

  fprintf(stdout, "OK:\t%d\ttest(s) out of %d are ok!\n", testCnt - testFailedCnt, testCnt);
}
