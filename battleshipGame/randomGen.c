#include <stdlib.h>
#include <time.h>
#include "randomGen.h"

struct _randomGen {
  int idx;
  int offset;
  int length;
};

static int greatestCommonDivisor(
  int m,
  int n
) {
  if (0 == n) {
    return m;
  } else {
    return greatestCommonDivisor(n, m % n);
  }
}

int initialize_ranndomGen(
  RANDOMGENERATOR** radnomGenerator,
  const int length
) {
  int error = 0;
  int offsetOk = 0;
  int gcd = 0;
  RANDOMGENERATOR* radnomGenerator_init = NULL;

  radnomGenerator_init = (RANDOMGENERATOR*)calloc(1, sizeof(RANDOMGENERATOR));

  if (NULL != radnomGenerator_init) {
    /* initialize random seed: */
    srand((unsigned int)time(NULL));

    radnomGenerator_init->length = length;

    /* generate secret number in the range [0 length): */
    radnomGenerator_init->idx = rand() % (radnomGenerator_init->length - 1);

    while (0 == offsetOk) {
      offsetOk = 1;

      /* generate secret number between length/4 and length*3/4: */
      radnomGenerator_init->offset = rand() % (radnomGenerator_init->length >> 2) + ((3 * radnomGenerator_init->length) >> 2);

      gcd = greatestCommonDivisor(radnomGenerator_init->length,
                                  radnomGenerator_init->offset);

      /* offset is valid if the greatest common divisor equals 1! */
      if (1 != gcd) {
        offsetOk = 0;
      }
    }

    *radnomGenerator = radnomGenerator_init;
  } else {
    error = 1;
  }

  return error;
}

int free_randomGen(
  RANDOMGENERATOR** radnomGenerator
) {
  int error = 0;

  if (NULL != *radnomGenerator) {
    free(*radnomGenerator);
    *radnomGenerator = NULL;
  } else {
    error = 1;
  }

  return error;
}

int randomGen_rand(
  RANDOMGENERATOR* radnomGenerator
) {
  radnomGenerator->idx = (radnomGenerator->idx + radnomGenerator->offset) % radnomGenerator->length;

  return radnomGenerator->idx;
}
