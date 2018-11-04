#include <stdlib.h>
#include "position.h"

POSITION createPosition(
  const int row,
  const int column
) {
  POSITION position;

  position.row = row;
  position.column = column;

  return position;
}
