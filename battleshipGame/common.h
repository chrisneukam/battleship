#ifndef _COMMON_H_
#define _COMMON_H

#define POSITION_MIN 0
#define POSITION_MAX 7
#define NUM_POSITIONS_ON_FIELD ((POSITION_MAX + 1) * (POSITION_MAX + 1))

typedef struct _position {
  int column;
  int row;
} POSITION;

#endif
