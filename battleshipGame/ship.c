#include <stdlib.h>
#include "common.h"
#include "ship.h"

typedef enum _status {
  UNSET,
  SET,
  SUNK
} STATUS;

typedef enum _shipType {
  CARRIER,
  BATTLESHIP,
  CRUISER,
  SUBMARINE,
  DESTROYER,
  NUM_SHIPS
} SHIPTYPE;

const int _shipLength[NUM_SHIPS] = {
  5,
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

static int initialize_ship(
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

static int free_ship(
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

static int setPosition(
  POSITION* position,
  const int row,
  const int column
) {
  int error = 0;

  if (NULL != position) {
    position->row = row;
    position->column = column;
  } else {
    error = 1;
  }

  return error;
}

int initialize_fleet(
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
        initialize_ship(shipID,
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

int free_fleet(
  FLEET** fleet
) {
  int error = 0;
  SHIPTYPE shipID = CARRIER;

  if (NULL != *fleet) {
    for (shipID = CARRIER; shipID < (*fleet)->numShips; shipID++) {
      free_ship(&(*fleet)->ships[shipID]);
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

int setup_fleet(
  FLEET* fleet
) {
  int error = 0;

  if (NULL != fleet) {
    setPosition(&fleet->ships[0].positions[0], 0, 1);
    setPosition(&fleet->ships[0].positions[1], 1, 1);
    setPosition(&fleet->ships[0].positions[2], 2, 1);
    setPosition(&fleet->ships[0].positions[3], 3, 1);
    setPosition(&fleet->ships[0].positions[4], 4, 1);
    fleet->ships[0].status = SET;

    setPosition(&fleet->ships[1].positions[0], 3, 3);
    setPosition(&fleet->ships[1].positions[1], 3, 4);
    setPosition(&fleet->ships[1].positions[2], 3, 5);
    setPosition(&fleet->ships[1].positions[3], 3, 6);
    fleet->ships[1].status = SET;

    setPosition(&fleet->ships[2].positions[0], 6, 5);
    setPosition(&fleet->ships[2].positions[1], 7, 5);
    setPosition(&fleet->ships[2].positions[2], 8, 5);
    fleet->ships[2].status = SET;

    setPosition(&fleet->ships[3].positions[0], 7, 0);
    setPosition(&fleet->ships[3].positions[1], 7, 1);
    setPosition(&fleet->ships[3].positions[2], 7, 2);
    fleet->ships[3].status = SET;

    setPosition(&fleet->ships[4].positions[0], 8, 8);
    setPosition(&fleet->ships[4].positions[1], 7, 8);
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
