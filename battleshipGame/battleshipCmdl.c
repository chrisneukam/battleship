#include <stdio.h>
#include "common.h"
#include "ship.h"
#include "ai.h"

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

static int playGame(
  FLEET* player_fleet,
  FLEET* cpu_fleet,
  AI* cpu_ai
) {
  int error = 0;
  int isHit = 0;
  int exit = 0;
  POSITION position;

  while (0 == exit) {
    printf("\n===============================================================================\n\n");
    printf("Player, it's your turn.\n");

    position.row = 1;
    position.column = 1;

    shootOnShip(position,
                player_fleet,
                &isHit);

    printf(">> You shoot in %d %d and: ", position.row, position.column);
    if (0 != isHit) {
      printf("Yeah! Nice hit!\n\n");
      showHit();
    } else {
      printf("Miss\n");
    }

    ai_getShootPosition(&position,
                        cpu_ai);

    shootOnShip(position,
                player_fleet,
                &isHit);

    printf(">> CPU shoot in %d %d and ", position.row, position.column);
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
  FLEET* player_fleet = NULL;
  FLEET* cpu_fleet = NULL;
  AI* cpu_ai = NULL;

  showSplash();

  fleet_initialize(&player_fleet);
  fleet_initialize(&cpu_fleet);
  ai_initialize(&cpu_ai);

  fleet_setup(player_fleet);
  fleet_setup(cpu_fleet);

  playGame(player_fleet,
           cpu_fleet,
           cpu_ai);

  fleet_free(&player_fleet);
  fleet_free(&cpu_fleet);
  ai_free(&cpu_ai);

  return error;
}
