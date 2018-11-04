#ifndef _AI_H_
#define _AI_H_

typedef struct _ai AI;

int ai_initialize(
  AI** cpuAI
);

int ai_free(
  AI** cpuAI
);

int ai_getShootPosition(
  POSITION* position,
  AI* cpuAI
);

#endif
