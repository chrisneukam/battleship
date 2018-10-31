#ifndef _SHIP_H_
#define _SHIP_H_

typedef struct _fleet FLEET;

int initialize_fleet(
  FLEET** fleet
);

int free_fleet(
  FLEET** fleet
);

int setup_fleet(
  FLEET* fleet
);

int shootOnShip(
  const POSITION position,
  const FLEET* fleet,
  int* isHit
);

#endif
