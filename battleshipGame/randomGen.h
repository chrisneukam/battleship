#ifndef _RANDOMGEN_H_
#define _RANDOMGEN_H_

typedef struct _randomGen RANDOMGENERATOR;

int randomGen_rand(
  RANDOMGENERATOR* radnomGenerator
);

int initialize_ranndomGen(
  RANDOMGENERATOR** radnomGenerator,
  const int length
);

int free_randomGen(
  RANDOMGENERATOR** radnomGenerator
);

#endif
