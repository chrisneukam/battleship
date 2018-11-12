#ifndef _POSITION_H_
#define _POSITION_H_

#define POSITION_MIN 0
#define POSITION_MAX 7
#define NUM_POSITIONS_ON_FIELD ((POSITION_MAX + 1) * (POSITION_MAX + 1))

typedef struct _position {
  int column;
  int row;
} POSITION;

POSITION createPosition(
  const int row,
  const int column
);

#endif
