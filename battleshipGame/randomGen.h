#ifndef _RANDOMGEN_H_
#define _RANDOMGEN_H_

typedef struct _randomGen RANDOMGENERATOR;

int randomGen_rand(
  RANDOMGENERATOR* radnomGenerator
);

int ranndomGen_initialize(
  RANDOMGENERATOR** radnomGenerator,
  const int length
);

int randomGen_free(
  RANDOMGENERATOR** radnomGenerator
);

#endif
