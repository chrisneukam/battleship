#include <stdio.h>
#include <stdlib.h>
#include "battleshipLib.h"

static void showSplash(
  void
) {
  printf("   __                __    __    ___                   __                    \n");
  printf("  /\\ \\              /\\ \\__/\\ \\__/\\_ \\                 /\\ \\      __           \n");
  printf("  \\ \\ \\____     __  \\ \\ ,_\\ \\ ,_\\//\\ \\      __    ____\\ \\ \\___ /\\_\\  _____   \n");
  printf("   \\ \\ '__`\\  /'__`\\ \\ \\ \\/\\ \\ \\/ \\ \\ \\   /'__`\\ /',__\\\\ \\  _ `\\/\\ \\/\\ '__`\\ \n");
  printf("    \\ \\ \\L\\ \\/\\ \\L\\.\\_\\ \\ \\_\\ \\ \\_ \\_\\ \\_/\\  __//\\__, `\\\\ \\ \\ \\ \\ \\ \\ \\ \\L\\ \\\n");
  printf("     \\ \\_,__/\\ \\__/.\\_\\\\ \\__\\\\ \\__\\/\\____\\ \\____\\/\\____/ \\ \\_\\ \\_\\ \\_\\ \\ ,__/\n");
  printf("      \\/___/  \\/__/\\/_/ \\/__/ \\/__/\\/____/\\/____/\\/___/   \\/_/\\/_/\\/_/\\ \\ \\/ \n");
  printf("                                                                       \\ \\_\\ \n");
  printf("                                                                 v1.0.0 \\/_/ \n\n");
}

static void showHit(
  void
) {
  printf("                    .#####....####....####...##...##.\n");
  printf("                    .##..##..##..##..##..##..###.###.\n");
  printf("                    .#####...##..##..##..##..##.#.##.\n");
  printf("                    .##..##..##..##..##..##..##...##.\n");
  printf("                    .#####....####....####...##...##.\n\n");
}

static int getUserInput(
  BSHIP_POSITION* position
) {
  int error = 0;
  char buffer[BSHIP_STRINGLENGTH] = {'\0'};

  fgets(buffer, BSHIP_STRINGLENGTH, stdin);

  /* flush the input buffer in stdin until the next \n: */
  while ((getchar()) != '\n');

  error = battleship_str2pos(buffer,
                             BSHIP_STRINGLENGTH,
                             position);

  return error;
}

static int setupGame(
  BSHIPENGINE* battleshipEngine
) {
  int error = 1;
  int ship = 0;
  int shipLength = 0;
  int idx = 0;
  BSHIP_POSITION positions[BSHIP_NUM_SHIPS] = {0};

  for (ship = 0; ship < BSHIP_NUM_SHIPS; ship++) {
    shipLength = battleship_getShipSize((BSHIP_TYPE)ship);

    for (idx = 0; idx < shipLength; idx++) {
      printf("Enter position %d of %d of ship number %d: ", idx + 1, shipLength, ship + 1);
      error |= getUserInput(&positions[idx]);
    }

    battleship_setShip(battleshipEngine,
                       (BSHIP_TYPE)ship,
                       positions,
                       shipLength);
  }

  return error;
}

static int playGame(
  BSHIPENGINE* battleshipEngine
) {
  int error = 0;
  int exit = 0;
  char string[BSHIP_STRINGLENGTH] = {'\0'};
  BSHIP_POSITION position = {0};
  BSHIP_HIT isHit = BSHIP_HIT_NOHIT;

  while (0 == exit) {
    printf("\n===============================================================================\n\n");
    printf("Player, it's your turn. Enter position: ");

    getUserInput(&position);

    battleshipLib_shoot(battleshipEngine,
                        BSHIP_TURN_PLAYER,
                        &isHit,
                        &position);

    battleship_pos2str(string,
                       BSHIP_STRINGLENGTH,
                       position);

    printf(">> You shoot in %s and: ", string);
    if (0 != isHit) {
      printf("Yeah! Nice hit!\n\n");
      showHit();
    } else {
      printf("Miss\n");
    }

    battleshipLib_shoot(battleshipEngine,
                        BSHIP_TURN_CPU,
                        &isHit,
                        &position);

    battleship_pos2str(string,
                       BSHIP_STRINGLENGTH,
                       position);

    printf(">> CPU shoot in %s and ", string);
    if (0 != isHit) {
      printf("hit your ship!\n\n");
      showHit();
    } else {
      printf("miss.\n");
    }

    exit = 1;
  }

  return error;
}

int main(
  int argc,
  char* argv[]
) {
  int error = 0;
  BSHIPENGINE* battleshipEngine = NULL;

  showSplash();

  error |= battleshipLib_initialize(&battleshipEngine);

  if (0 == error) {
    error |= setupGame(battleshipEngine);
  }

  if (0 == error) {
    error |= playGame(battleshipEngine);
  }

  error |= battleshipLib_free(&battleshipEngine);

  return error;
}
