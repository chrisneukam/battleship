#ifndef _SHIP_H_
#define _SHIP_H_

#include "position.h"

#define MAX_SHIP_SIZE 5

typedef struct _fleet FLEET;

typedef enum _shipType {
  CARRIER,
  BATTLESHIP,
  CRUISER,
  SUBMARINE,
  DESTROYER,
  NUM_SHIPS
} SHIPTYPE;

typedef enum _shipCollision {
  NO_COLLISION,
  COLLISION
} SHIPCOLLISION;

typedef enum _shipFracture {
  NO_FRACTURE,
  FRACTURE
} SHIPFRACTURE;

int fleet_initialize(
  FLEET** fleet
);

int fleet_free(
  FLEET** fleet
);

int fleet_setup(
  FLEET* fleet
);

int fleet_getShipSize(
  const SHIPTYPE shipType
);

int fleet_setShip(
  FLEET* fleet,
  const SHIPTYPE shipType,
  const POSITION* positions,
  const int positionLength
);

int fleet_collisionDetection(
  FLEET* fleet,
  SHIPCOLLISION* collisionResult
);

int fleet_fractureDetection(
  FLEET* fleet,
  SHIPFRACTURE* fractureResult
);

int shootOnShip(
  const POSITION position,
  const FLEET* fleet,
  int* isHit
);

#endif
