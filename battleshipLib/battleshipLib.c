#include <stdlib.h>
#include "battleshipLib.h"
#include "ai.h"
#include "position.h"
#include "ship.h"
#include "util.h"

struct _battleshipEngine {
  FLEET* player_fleet;
  FLEET* cpu_fleet;
  AI* cpu_ai;
};

int battleshipLib_initialize(
  BSHIPENGINE** engine
) {
  int error = 0;
  BSHIPENGINE* engine_init = NULL;

  if (NULL != engine) {
    engine_init = (BSHIPENGINE*)calloc(1, sizeof(BSHIPENGINE));

    error |= fleet_initialize(&engine_init->player_fleet);
    error |= fleet_initialize(&engine_init->cpu_fleet);
    error |= ai_initialize(&engine_init->cpu_ai);

    error |= fleet_setup(engine_init->player_fleet);
    error |= fleet_setup(engine_init->cpu_fleet);

    if (0 == error) {
      *engine = engine_init;
    }
  } else {
    error = 1;
  }

  return error;
}

int battleshipLib_free(
  BSHIPENGINE** engine
) {
  int error = 0;

  if (NULL != *engine) {
    free(*engine);
    *engine = NULL;
  } else {
    error = 1;
  }

  return error;
}

int battleshipLib_shoot(
  BSHIPENGINE* engine,
  const BSHIP_TURN turn,
  BSHIP_HIT* hit,
  BSHIP_POSITION* position
) {
  int error = 0;
  int isHit = 0;
  POSITION tmp = {0};

  if ((NULL != engine) && (NULL != position)) {
    if (BSHIP_TURN_CPU == turn) {
      error |= ai_getShootPosition(&tmp,
                                   engine->cpu_ai);

      error |= shootOnShip(tmp,
                           engine->player_fleet,
                           &isHit);
    } else {
      tmp = createPosition(position->row,
                           position->column);

      error |= shootOnShip(tmp,
                           engine->cpu_fleet,
                           &isHit);
    }

    if (0 == error) {
      *hit = (1 == isHit) ? BSHIP_HIT_HIT : BSHIP_HIT_NOHIT;
      position->row = tmp.row;
      position->column = tmp.column;
    }
  } else {
    error = 1;
  }

  return error;
}

int battleship_getShipSize(
  const BSHIP_TYPE shipType
) {
  int size = 0;

  size = fleet_getShipSize((SHIPTYPE)shipType);

  return size;
}

int battleship_setShip(
  BSHIPENGINE* engine,
  const BSHIP_TYPE shipType,
  const BSHIP_POSITION* positions,
  const int positionLength
) {
  int error = 0;
  int idx;
  POSITION tmp[NUM_SHIPS] = {0};

  if ((NULL != engine) && (NULL != positions) && (NUM_SHIPS >= positionLength)) {
    for (idx = 0; idx < positionLength; idx++) {
      tmp[idx].row = positions->row;
      tmp[idx].column = positions->column;
    }

    error = fleet_setShip(engine->player_fleet,
                          (SHIPTYPE)shipType,
                          tmp,
                          positionLength);
  } else {
    error = 1;
  }

  return error;
}

int battleship_pos2str(
  char* string,
  const int length,
  const BSHIP_POSITION position
) {
  int error = 0;
  POSITION tmp = {0};

  if (NULL != string) {
    tmp = createPosition(position.row,
                         position.column);

    error = util_position2string(string,
                                 length,
                                 tmp);
  } else {
    error = 1;
  }

  return error;
}

int battleship_str2pos(
  char* string,
  const int length,
  BSHIP_POSITION* position
) {
  int error = 0;
  POSITION tmp = {0};

  if ((NULL != string) && (NULL != position)) {
    error = util_string2position(string,
                                 length,
                                 &tmp);

    if (0 == error) {
      position->row = tmp.row;
      position->column = tmp.column;
    }
  } else {
    error = 1;
  }

  return error;
}
