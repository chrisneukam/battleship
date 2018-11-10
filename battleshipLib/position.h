#ifndef _POSITION_H_
#define _POSITION_H_

typedef struct _position {
  int column;
  int row;
} POSITION;

POSITION createPosition(
  const int row,
  const int column
);

#endif
