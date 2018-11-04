#ifndef _SHIP_H_
#define _SHIP_H_

#include "position.h"

typedef struct _fleet FLEET;

typedef enum _shipType {
  CARRIER,
  BATTLESHIP,
  CRUISER,
  SUBMARINE,
  DESTROYER,
  NUM_SHIPS
} SHIPTYPE;

int fleet_initialize(
  FLEET** fleet
);

int fleet_free(
  FLEET** fleet
);

int fleet_setup(
  FLEET* fleet
);

int fleet_setShip(
  FLEET* fleet,
  const SHIPTYPE shipType,
  const POSITION* positions,
  const int positionLength
);

int shootOnShip(
  const POSITION position,
  const FLEET* fleet,
  int* isHit
);

#endif
