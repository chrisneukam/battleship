#include <stdio.h>
#include "testFramework.h"
#include "unittests.h"

int main(
  int argc,
  char* argv[]
) {
  TESTRESULT error = 0;

  error = run_test(test_util_sort(), "test_util_sort()");
  error = run_test(test_util_array_equal(), "test_util_array_equal()");
  error = run_test(test_util_array_no_equal(), "test_util_array_no_equal()");
  error = run_test(test_util_array_sequence(), "test_util_array_sequence()");
  error = run_test(test_util_array_no_sequence(), "test_util_array_no_sequence()");
  error = run_test(test_util_pos2str(), "test_util_pos2str()");
  error = run_test(test_util_str2pos(), "test_util_str2pos()");
  error = run_test(test_position_create(), "test_position_create()");
  error = run_test(test_randomGen_gcd(), "test_randomGen_gcd()");
  error = run_test(test_ai_getShootPosition_range(), "test_ai_getShootPosition_range()");
  error = run_test(test_ai_getShootPosition_unique(), "test_ai_getShootPosition_unique()");
  error = run_test(test_randomGen_rand(), "test_randomGen_rand()");
  error = run_test(test_ship_collision(), "test_ship_collision()");
  error = run_test(test_ship_no_collision(), "test_ship_no_collision()");
  error = run_test(test_ship_fracture(), "test_ship_fracture()");
  error = run_test(test_ship_no_fracture(), "test_ship_no_fracture()");

  printStatistic();

  return (int)error;
}
