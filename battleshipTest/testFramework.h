#ifndef _TESTFRAMEWORK_H_
#define _TESTFRAMEWORK_H_

typedef enum _test_result {
  OK,
  FAIL
} TESTRESULT;

void init_test(
  const char* functionName
);

void eval_test(
  const TESTRESULT testResult,
  const char* functionName
);

TESTRESULT run_test(
  const int testResult,
  const char* functionName
);

void printStatistic(
  void
);

#endif
