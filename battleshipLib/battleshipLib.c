#include <stdlib.h>
#include "battleshipLib.h"
#include "ai.h"
#include "common.h"
#include "position.h"
#include "ship.h"

struct _battleshipEngine {
  FLEET* player_fleet;
  FLEET* cpu_fleet;
  AI* cpu_ai;
};

int battleshipLib_initialize(
  BATTLESHIPENGINE** engine
) {
  int error = 0;
  BATTLESHIPENGINE* engine_init = NULL;

  if (NULL != engine) {
    engine_init = (BATTLESHIPENGINE*)calloc(1, sizeof(BATTLESHIPENGINE));

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
  BATTLESHIPENGINE** engine
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
  BATTLESHIPENGINE* engine,
  const BATTLESHIP_TURN turn,
  BATTLESHIP_HIT* hit,
  int* row,
  int* column
) {
  int error = 0;
  int isHit = 0;
  POSITION position = {0};

  if ((NULL != engine) && (NULL != row) && (NULL != column)) {
    if (BATTLESHIP_TURN_CPU == turn) {
      error |= ai_getShootPosition(&position,
                                   engine->cpu_ai);

      error |= shootOnShip(position,
                           engine->player_fleet,
                           &isHit);
    } else {
      position = createPosition(*row,
                                *column);

      error |= shootOnShip(position,
                           engine->cpu_fleet,
                           &isHit);
    }

    if (0 == error) {
      *hit = (1 == isHit) ? BATTLESHIP_HIT_HIT : BATTLESHIP_HIT_NOHIT;
      *row = position.row;
      *column = position.column;
    }
  } else {
    error = 1;
  }

  return error;
}
