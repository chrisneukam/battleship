#include <stdio.h>
#include "ship.h"

static void showSplash(void
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

static void showHit(void
) {
  printf("                    .#####....####....####...##...##.\n");
  printf("                    .##..##..##..##..##..##..###.###.\n");
  printf("                    .#####...##..##..##..##..##.#.##.\n");
  printf("                    .##..##..##..##..##..##..##...##.\n");
  printf("                    .#####....####....####...##...##.\n\n");
}

static int playGame(
          FLEET* player_fleet,
          FLEET* cpu_fleet
) {
  int error = 0;
  int isHit = 0;
  int exit = 0;
  int row = 0;
  int column = 0;

  while (0 == exit) {
    printf("\n===============================================================================\n\n");
    printf("Player, it's your turn.\n");

    row = 1;
    column = 1;

    shootOnShip(row,
                column,
                player_fleet,
                &isHit);

    printf(">> You shoot in %d %d and: ", row, column);
    if (0 != isHit) {
      printf("Yeah! Nice hit!\n\n");
      showHit();
    } else {
      printf("Miss\n");
    }

    row = 1;
    column = 8;

    shootOnShip(row,
                column,
                player_fleet,
                &isHit);

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

int main(int argc, char* argv[]
) {
  int error = 0;
  FLEET* player_fleet = NULL;
  FLEET* cpu_fleet = NULL;

  showSplash();

  initialize_fleet(&player_fleet);
  initialize_fleet(&cpu_fleet);

  setup_fleet(player_fleet);
  setup_fleet(cpu_fleet);

  playGame(player_fleet,
           cpu_fleet);

  free_fleet(&player_fleet);
  free_fleet(&cpu_fleet);

  return error;
}
