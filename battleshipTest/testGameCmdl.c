#include <stdio.h>
#include "testFramework.h"
#include "unittests.h"

int main(
  int argc,
  char* argv[]
) {
  TESTRESULT error = 0;

  error = run_test(test_ai_getShootPosition_range(), "test_ai_getShootPosition_range()");

  error = run_test(test_ai_getShootPosition_unique(), "test_ai_getShootPosition_unique()");

  error = run_test(test_randomGen_rand(), "test_randomGen_rand()");

  printStatistic();

  return (int)error;
}
