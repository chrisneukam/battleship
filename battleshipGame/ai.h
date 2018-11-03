#ifndef _AI_H_
#define _AI_H_

typedef struct _ai AI;

int initialize_ai(
  AI** cpuAI
);

int free_ai(
  AI** cpuAI
);

int ai_getShootPosition(
  POSITION* position,
  AI* cpuAI
);

#endif
