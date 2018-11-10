#include <stdlib.h>
#include "testFramework.h"
#include "unittests.h"
#include "ai.h"
#include "common.h"
#include "position.h"
#include "randomGen.h"
#include "ship.h"
#include "util.h"

int test_util_sort(
  void
) {
  TESTRESULT result = OK;
  int data[] = {2, 6, 0, 99, 6, 3, 8, 46, 5, 1};
  int length = sizeof(data) / sizeof(data[0]);
  int idx = 0;

  if (0 == util_sort(data, length)) {

    /* TEST: the elements in data shall be in ascending order */
    for (idx = 1; idx < length; idx++) {
      if (data[idx] < data[idx - 1]) {
        result = FAIL;
      }
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_util_array_equal(
  void
) {
  TESTRESULT result = OK;
  int data[] = {0, 0, 0, 0};
  int length = sizeof(data) / sizeof(data[0]);
  int allEqual = 0;

  if (0 == util_array_equal(data, length, &allEqual)) {
    if (1 != allEqual) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_util_array_no_equal(
  void
) {
  TESTRESULT result = OK;
  int data[] = {2, 6, 0, 99};
  int length = sizeof(data) / sizeof(data[0]);
  int allEqual = 1;

  if (0 == util_array_equal(data, length, &allEqual)) {
    if (0 != allEqual) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_util_array_sequence(
  void
) {
  TESTRESULT result = OK;
  int data[] = {0, 1, 2, 3};
  int length = sizeof(data) / sizeof(data[0]);
  int sequencial = 0;

  if (0 == util_array_sequence(data, length, &sequencial)) {
    if (1 != sequencial) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_util_array_no_sequence(
  void
) {
  TESTRESULT result = OK;
  int data[] = {6, 3, 4, 2};
  int length = sizeof(data) / sizeof(data[0]);
  int sequencial = 1;

  if (0 == util_array_sequence(data, length, &sequencial)) {
    if (0 != sequencial) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_position_create(
  void
) {
  TESTRESULT result = OK;
  POSITION position = {0};

  /* TEST: the returned position SHALL have the coordinates row = 5 and collumn = 3 */
  position = createPosition(5, 3);
  if (5 != position.row || 3 != position.column) {
    result = FAIL;
  }

  return result;
}

int test_randomGen_gcd(
  void
) {
  TESTRESULT result = OK;
  int gcd = 0;

  /* TEST: the grates common divisior of 81 and 153 IS 9 */
  gcd = randomGen_gcd(81, 153);
  if (9 != gcd) {
    result = FAIL;
  }

  return (int)result;
}

int test_randomGen_rand(
  void
) {
  TESTRESULT result = OK;
  RANDOMGENERATOR* randomGen = NULL;
  const int length = 11;
  int memory[11] = {0};
  int run_ref = 0;
  int run_cmp = 0;
  int cnt = 0;

  if (0 == ranndomGen_initialize(&randomGen,
                                 length)) {
    for (run_ref = 0; run_ref < length; run_ref++) {
      memory[run_ref] = randomGen_rand(randomGen);
    }

    /* TEST: each value returned by X rus of the random generator shall be unique */
    for (run_ref = 0; run_ref < length; run_ref++) {
      for (run_cmp = run_ref; run_cmp < length; run_cmp++) {
        if ((memory[run_ref] == memory[run_cmp]) && (run_ref != run_cmp)) {
          cnt++;
        }
      }
    }
    if (cnt > 0) {
      result = FAIL;
    }

    if (0 != randomGen_free(&randomGen)) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_ai_getShootPosition_range(
  void
) {
  TESTRESULT result = OK;
  POSITION position = {0};
  AI* cpu_ai = NULL;
  int run = 0;

  if (0 == ai_initialize(&cpu_ai)) {
    for (run = 0; run < NUM_POSITIONS_ON_FIELD; run++) {
      if (0 != ai_getShootPosition(&position,
                                   cpu_ai)) {
        result = FAIL;
        break;
      }

      /* TEST: row shall be in the allowed range */
      if (position.row < POSITION_MIN || position.row > POSITION_MAX) {
        result = FAIL;
        break;
      }

      /* TEST: column shall be in the allowed range */
      if (position.column < POSITION_MIN || position.column > POSITION_MAX) {
        result = FAIL;
        break;
      }
    }

    if (0 != ai_free(&cpu_ai)) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_ai_getShootPosition_unique(
  void
) {
  TESTRESULT result = OK;
  POSITION position[NUM_POSITIONS_ON_FIELD] = {0};
  AI* cpu_ai = NULL;
  int run_ref = 0;
  int run_cmp = 0;
  int cnt = 0;

  if (0 == ai_initialize(&cpu_ai)) {
    for (run_ref = 0; run_ref < NUM_POSITIONS_ON_FIELD; run_ref++) {
      if (0 != ai_getShootPosition(&position[run_ref],
                                   cpu_ai)) {
        result = FAIL;
        break;
      }
    }

    if (OK == result) {
      /* TEST: each position returned by NUM_POSITIONS_ON_FIELD rus of the shooting shall be unique */
      for (run_ref = 0; run_ref < NUM_POSITIONS_ON_FIELD; run_ref++) {
        for (run_cmp = run_ref; run_cmp < NUM_POSITIONS_ON_FIELD; run_cmp++) {
          if ((position[run_ref].row == position[run_cmp].row) &&
              (position[run_ref].column == position[run_cmp].column) && 
              (run_ref != run_cmp)) {
            cnt++;
          }
        }

        if (cnt > 0) {
          break;
        } else {
          cnt = 0;
        }
      }
      if (cnt > 0) {
        result = FAIL;
      }
    }

    if (0 != ai_free(&cpu_ai)) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_ship_collision(
  void
) {
  TESTRESULT result = OK;
  FLEET* fleet = NULL;
  POSITION positions[MAX_SHIP_SIZE] = {0};
  SHIPCOLLISION collision = NO_COLLISION;
  int pos = 0;

  if (0 == fleet_initialize(&fleet)) {
    for (pos = 0; pos < MAX_SHIP_SIZE; pos++) {
      positions[pos] = createPosition(pos, 0);
    }

    if (0 != fleet_setShip(fleet,
                           SUBMARINE,
                           positions,
                           fleet_getShipSize(SUBMARINE))) {
      result = FAIL;
    }

    if (0 != fleet_setShip(fleet,
                           DESTROYER,
                           positions,
                           fleet_getShipSize(DESTROYER))) {
      result = FAIL;
    }

    if (0 != fleet_collisionDetection(fleet,
                                      &collision)) {
      result = FAIL;
    }

    /* TEST: here a collision SHALL be detected as the given ships collide */
    if (COLLISION != collision) {
      result = FAIL;
    }

    if (0 != fleet_free(&fleet)) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_ship_no_collision(
  void
  ) {
  TESTRESULT result = OK;
  FLEET* fleet = NULL;
  POSITION positionsA[MAX_SHIP_SIZE] = {0};
  POSITION positionsB[MAX_SHIP_SIZE] = {0};
  SHIPCOLLISION collision = COLLISION;
  int pos = 0;

  if (0 == fleet_initialize(&fleet)) {
    for (pos = 0; pos < MAX_SHIP_SIZE; pos++) {
      positionsA[pos] = createPosition(pos, 0);
      positionsB[pos] = createPosition(pos, 1);
    }

    if (0 != fleet_setShip(fleet,
                           SUBMARINE,
                           positionsA,
                           fleet_getShipSize(SUBMARINE))) {
      result = FAIL;
    }

    if (0 != fleet_setShip(fleet,
                           DESTROYER,
                           positionsB,
                           fleet_getShipSize(DESTROYER))) {
      result = FAIL;
    }

    if (0 != fleet_collisionDetection(fleet,
                                      &collision)) {
      result = FAIL;
    }

    /* TEST: here a collision SHALL NOT be detected as the given ships are not colliding */
    if (NO_COLLISION != collision) {
      result = FAIL;
    }

    if (0 != fleet_free(&fleet)) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_ship_fracture(
  void
) {
  TESTRESULT result = OK;
  FLEET* fleet = NULL;
  POSITION positions[MAX_SHIP_SIZE] = {0};
  SHIPFRACTURE fracture = NO_FRACTURE;
  int pos = 0;

  if (0 == fleet_initialize(&fleet)) {
    for (pos = 0; pos < MAX_SHIP_SIZE; pos++) {
      positions[pos] = createPosition(pos, pos);
    }

    if (0 != fleet_setShip(fleet,
                           SUBMARINE,
                           positions,
                           fleet_getShipSize(SUBMARINE))) {
      result = FAIL;
    }

    if (0 != fleet_fractureDetection(fleet,
                                     &fracture)) {
      result = FAIL;
    }

    /* TEST: here a collision SHALL NOT be detected as the given ships are not colliding */
    if (FRACTURE != fracture) {
      result = FAIL;
    }

    if (0 != fleet_free(&fleet)) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}

int test_ship_no_fracture(
  void
) {
  TESTRESULT result = OK;
  FLEET* fleet = NULL;
  POSITION positions[MAX_SHIP_SIZE] = {0};
  SHIPFRACTURE fracture = FRACTURE;
  int posShuffle[MAX_SHIP_SIZE] = {0, 2, 1, 4, 3};
  int pos = 0;

  if (0 == fleet_initialize(&fleet)) {
    for (pos = 0; pos < MAX_SHIP_SIZE; pos++) {
      positions[pos] = createPosition(posShuffle[pos], 0);
    }

    if (0 != fleet_setShip(fleet,
                           CARRIER,
                           positions,
                           fleet_getShipSize(CARRIER))) {
      result = FAIL;
    }

    if (0 != fleet_fractureDetection(fleet,
                                     &fracture)) {
      result = FAIL;
    }

    /* TEST: here a collision SHALL NOT be detected as the given ships are not colliding */
    if (NO_FRACTURE != fracture) {
      result = FAIL;
    }

    if (0 != fleet_free(&fleet)) {
      result = FAIL;
    }
  } else {
    result = FAIL;
  }

  return (int)result;
}
