#ifndef _SHIP_H_
#define _SHIP_H_

typedef struct _fleet FLEET;

int fleet_initialize(
  FLEET** fleet
);

int fleet_free(
  FLEET** fleet
);

int fleet_setup(
  FLEET* fleet
);

int shootOnShip(
  const POSITION position,
  const FLEET* fleet,
  int* isHit
);

#endif
