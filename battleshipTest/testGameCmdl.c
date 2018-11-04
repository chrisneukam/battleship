#include <stdio.h>
#include "testFramework.h"
#include "unittests.h"

int main(
  int argc,
  char* argv[]
) {
  TESTRESULT error = 0;

  error = run_test(test_position_create(), "test_position_create()");
  error = run_test(test_randomGen_gcd(), "test_randomGen_gcd()");
  error = run_test(test_ai_getShootPosition_range(), "test_ai_getShootPosition_range()");
  error = run_test(test_ai_getShootPosition_unique(), "test_ai_getShootPosition_unique()");
  error = run_test(test_randomGen_rand(), "test_randomGen_rand()");
  error = run_test(test_ship_collision_FALSE(), "test_ship_collision_FALSE()");
  error = run_test(test_ship_collision_TRUE(), "test_ship_collision_TRUE()");

  printStatistic();

  return (int)error;
}
