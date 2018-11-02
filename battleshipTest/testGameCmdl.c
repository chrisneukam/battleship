#include <stdio.h>
#include "testFramework.h"
#include "unittests.h"

int main(int argc, char* argv[]
) {
  TESTRESULT error = 0;

  error = run_test(test_ki_getShootPosition(), "test_ki_getShootPosition()");

  printStatistic();

  return (int)error;
}