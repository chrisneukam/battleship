#ifndef _BATTLESHIPLIB_H_
#define _BATTLESHIPLIB_H_

typedef struct _battleshipEngine BATTLESHIPENGINE;

typedef enum _battleshipTurn {
  BATTLESHIP_TURN_PLAYER,
  BATTLESHIP_TURN_CPU
} BATTLESHIP_TURN;

typedef enum _battleshipHit {
  BATTLESHIP_HIT_NOHIT,
  BATTLESHIP_HIT_HIT
} BATTLESHIP_HIT;

int battleshipLib_initialize(
  BATTLESHIPENGINE** engine
);

int battleshipLib_free(
  BATTLESHIPENGINE** engine
);

int battleshipLib_shoot(
  BATTLESHIPENGINE* engine,
  const BATTLESHIP_TURN turn,
  BATTLESHIP_HIT* hit,
  int* row,
  int* column
);

#endif
