#ifndef _RANDOMGEN_H_
#define _RANDOMGEN_H_

typedef struct _randomGen RANDOMGENERATOR;

int ranndomGen_initialize(
  RANDOMGENERATOR** radnomGenerator,
  const int length
);

int randomGen_free(
  RANDOMGENERATOR** radnomGenerator
);

int randomGen_rand(
  RANDOMGENERATOR* radnomGenerator
);

int randomGen_gcd(
  const int valueX,
  const int valueY
);

#endif
