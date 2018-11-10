#include <stdlib.h>
#include "common.h"
#include "position.h"
#include "ship.h"
#include "util.h"

typedef enum _status {
  UNSET,
  SET,
  SUNK
} STATUS;

const int _shipLength[NUM_SHIPS] = {
  MAX_SHIP_SIZE,
  4,
  3,
  3,
  2
};

typedef struct _ship {
  SHIPTYPE type;
  POSITION* positions;
  int length;
  STATUS status;
} SHIP;

struct _fleet {
  SHIP* ships;
  int numShips;
};

static int ship_initialize(
  const SHIPTYPE shipType,
  const int shipLength,
  SHIP* ship
) {
  int error = 0;

  if (NULL != ship) {
    ship->positions = (POSITION*)calloc(shipLength, sizeof(POSITION));

    if (NULL != ship->positions) {
      ship->type = shipType;
      ship->length = shipLength;
      ship->status = UNSET;
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }

  return error;
}

static int ship_free(
  SHIP* ship
) {
  int error = 0;

  if (NULL != ship) {
    free(ship->positions);

    ship->type = CARRIER;
    ship->length = 0;
    ship->positions = NULL;
    ship->status = UNSET;
  } else {
    error = 1;
  }

  return error;
}

int fleet_initialize(
  FLEET** fleet
) {
  int error = 0;
  SHIPTYPE shipID = CARRIER;
  FLEET* fleet_init = NULL;

  fleet_init = (FLEET*)calloc(1, sizeof(FLEET));

  if (NULL != fleet_init) {
    fleet_init->ships = (SHIP*)calloc(NUM_SHIPS, sizeof(SHIP));

    if (NULL != fleet_init->ships) {
      fleet_init->numShips = NUM_SHIPS;

      for (shipID = CARRIER; shipID < NUM_SHIPS; shipID++) {
        ship_initialize(shipID,
                        _shipLength[shipID],
                        &fleet_init->ships[shipID]);
      }

      *fleet = fleet_init;
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }

  return error;
}

int fleet_free(
  FLEET** fleet
) {
  int error = 0;
  SHIPTYPE shipID = CARRIER;

  if (NULL != *fleet) {
    for (shipID = CARRIER; shipID < (*fleet)->numShips; shipID++) {
      ship_free(&(*fleet)->ships[shipID]);
    }

    free((*fleet)->ships);
    (*fleet)->ships = NULL;
    (*fleet)->numShips = 0;

    free(*fleet);
    *fleet = NULL;
  } else {
    error = 1;
  }

  return error;
}

int fleet_getShipSize(
  const SHIPTYPE shipType
) {
  int size = 0;

  if (shipType < NUM_SHIPS) {
    size = _shipLength[shipType];
  }

  return size;
}

int fleet_setShip(
  FLEET* fleet,
  const SHIPTYPE shipType,
  const POSITION* positions,
  const int positionLength
) {
  int error = 0;
  int idx = 0;

  if (NULL != fleet && NULL != positions) {
    if (_shipLength[shipType] != positionLength) {
      error = 1;
    }

    if (0 == error) {
      for (idx = 0; idx < positionLength; idx++) {
        fleet->ships[shipType].positions[idx] = positions[idx];
      }

      fleet->ships[shipType].status = SET;
    }
  } else {
    error = 1;
  }

  return error;
}

int fleet_collisionDetection(
  FLEET* fleet,
  SHIPCOLLISION* collisionResult
) {
  int error = 0;
  int ship_ref = 0;
  int ship_cmp = 0;
  int pos_ref = 0;
  int pos_cmp = 0;

  if ((NULL != fleet) && (NULL != collisionResult)) {
    *collisionResult = NO_COLLISION;

    for (ship_ref = 0; ship_ref < fleet->numShips; ship_ref++) {
      for (ship_cmp = ship_ref; ship_cmp < fleet->numShips; ship_cmp++) {
        if ((SET == fleet->ships[ship_ref].status) && (SET == fleet->ships[ship_cmp].status) && (ship_ref != ship_cmp)) {
          for (pos_ref = 0; pos_ref < fleet->ships[ship_ref].length; pos_ref++) {
            for (pos_cmp = 0; pos_cmp < fleet->ships[ship_cmp].length; pos_cmp++) {
              if ((fleet->ships[ship_ref].positions[pos_ref].row == fleet->ships[ship_cmp].positions[pos_cmp].row) &&
                  (fleet->ships[ship_ref].positions[pos_ref].column == fleet->ships[ship_cmp].positions[pos_cmp].column)) {
                *collisionResult = COLLISION;
              }
            }
          }
        }
      }
    }
  } else {
    error = 1;
  }

  return error;
}

int fleet_fractureDetection(
  FLEET* fleet,
  SHIPFRACTURE* fractureResult
) {
  int error = 0;
  int ship = 0;
  int pos = 0;
  int rows[MAX_SHIP_SIZE] = {0};
  int cols[MAX_SHIP_SIZE] = {0};

  if ((NULL != fleet) && (NULL != fractureResult)) {
    *fractureResult = NO_FRACTURE;

    for (ship = 0; ship < fleet->numShips; ship++) {
      if (SET == fleet->ships[ship].status) {
        for (pos = 1; pos < fleet->ships[ship].length; pos++) {
          rows[pos] = fleet->ships[ship].positions[pos].row;
          cols[pos] = fleet->ships[ship].positions[pos].column;          
        }

        /* sort rows and cols */
        /* if all rows are equal, cols shall be ascending or decending */
        /* if all cols are equal, rows shall be ascending or decending */

        if (0 == error) {
          error = util_sort(rows, fleet->ships[ship].length);
        }

        if (0 == error) {
          error = util_sort(cols, fleet->ships[ship].length);
        }
        


      }
    }
  } else {
    error = 1;
  }

  return error;
}

int fleet_setup(
  FLEET* fleet
) {
  int error = 0;

  if (NULL != fleet) {
    fleet->ships[0].positions[0] = createPosition(0, 1);
    fleet->ships[0].positions[1] = createPosition(1, 1);
    fleet->ships[0].positions[2] = createPosition(2, 1);
    fleet->ships[0].positions[3] = createPosition(3, 1);
    fleet->ships[0].positions[4] = createPosition(4, 1);
    fleet->ships[0].status = SET;

    fleet->ships[1].positions[0] = createPosition(3, 3);
    fleet->ships[1].positions[1] = createPosition(3, 4);
    fleet->ships[1].positions[2] = createPosition(3, 5);
    fleet->ships[1].positions[3] = createPosition(3, 6);
    fleet->ships[1].status = SET;

    fleet->ships[2].positions[0] = createPosition(6, 5);
    fleet->ships[2].positions[1] = createPosition(7, 5);
    fleet->ships[2].positions[2] = createPosition(8, 5);
    fleet->ships[2].status = SET;

    fleet->ships[3].positions[0] = createPosition(7, 0);
    fleet->ships[3].positions[1] = createPosition(7, 1);
    fleet->ships[3].positions[2] = createPosition(7, 2);
    fleet->ships[3].status = SET;

    fleet->ships[4].positions[0] = createPosition(8, 8);
    fleet->ships[4].positions[1] = createPosition(7, 8);
    fleet->ships[4].status = SET;
  } else {
    error = 1;
  }

  return error;
}

int shootOnShip(
  const POSITION position,
  const FLEET* fleet,
  int* isHit
) {
  int error = 0;
  int shipID = 0;
  int posID = 0;

  if (NULL != isHit && NULL != fleet) {
    *isHit = 0;

    for (shipID = 0; shipID < fleet->numShips; shipID++) {
      for (posID = 0; posID < fleet->ships[shipID].length; posID++) {
        if ((position.row == fleet->ships[shipID].positions[posID].row) && (position.column == fleet->ships[shipID].positions[posID].column)) {
          *isHit = 1;
        }
      }
    }

  } else {
    error = 1;
  }

  return error;
}
