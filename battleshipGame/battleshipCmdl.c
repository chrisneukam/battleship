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

static int covertInputToPosition(
  char* string,
  const int length,
  int* row,
  int* column
) {
  int error = 0;

  if ((NULL != string) && (NULL != row) && (NULL != column) && (length >= 2)) {
    if ((string[0] >= 'a') && (string[0] <= 'z')) {
      *row = (int)(string[0] - 'a');
    } else if ((string[0] >= 'A') && (string[0] <= 'Z')) {
      *row = (int)(string[0] - 'A');
    } else {
      error = 1;
    }

    if ((string[1] >= '1') && (string[1] <= '9')) {
      *column = (int)(string[1] - '1');
    }
  } else {
    error = 1;
  }
  
  return error;
}

static int userInput(
  int *row,
  int *column
) {
  int error = 0;
  char buffer[3] = {'\0'};

  fgets(buffer, 3, stdin);

  error = covertInputToPosition(buffer,
                                2,
                                row,
                                column);

  return error;
}

static int playGame(
  BATTLESHIPENGINE* battleshipEngine
) {
  int error = 0;
  int exit = 0;
  int row = 0;
  int column = 0;
  BATTLESHIP_HIT isHit = BATTLESHIP_HIT_NOHIT;

  while (0 == exit) {
    printf("\n===============================================================================\n\n");
    printf("Player, it's your turn.\n");

    userInput(&row,
              &column);

    battleshipLib_shoot(battleshipEngine,
                        BATTLESHIP_TURN_PLAYER,
                        &isHit,
                        &row,
                        &column);

    printf(">> You shoot in %d %d and: ", row, column);
    if (0 != isHit) {
      printf("Yeah! Nice hit!\n\n");
      showHit();
    } else {
      printf("Miss\n");
    }

    battleshipLib_shoot(battleshipEngine,
                        BATTLESHIP_TURN_CPU,
                        &isHit,
                        &row,
                        &column);

    printf(">> CPU shoot in %d %d and ", row, column);
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
  BATTLESHIPENGINE* battleshipEngine = NULL;

  showSplash();

  error |= battleshipLib_initialize(&battleshipEngine);

  if (0 == error) {
    playGame(battleshipEngine);
  }

  error |= battleshipLib_free(&battleshipEngine);

  return error;
}
