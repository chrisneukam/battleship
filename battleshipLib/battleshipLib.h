#ifndef _BATTLESHIPLIB_H_
#define _BATTLESHIPLIB_H_

#define BSHIP_STRINGLENGTH 3

typedef struct _battleshipEngine BSHIPENGINE;

typedef struct _battleshipPosition {
  int row;
  int column;
} BSHIP_POSITION;

typedef enum _battleshipTurn {
  BSHIP_TURN_PLAYER,
  BSHIP_TURN_CPU
} BSHIP_TURN;

typedef enum _battleshipHit {
  BSHIP_HIT_NOHIT,
  BSHIP_HIT_HIT
} BSHIP_HIT;

int battleshipLib_initialize(
  BSHIPENGINE** engine
);

int battleshipLib_free(
  BSHIPENGINE** engine
);

int battleshipLib_shoot(
  BSHIPENGINE* engine,
  const BSHIP_TURN turn,
  BSHIP_HIT* hit,
  BSHIP_POSITION* position
);

int battleship_pos2str(
  char* string,
  const int length,
  const BSHIP_POSITION position
);

int battleship_str2pos(
  char* string,
  const int length,
  BSHIP_POSITION* position
);

#endif
