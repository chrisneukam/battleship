#include <stdlib.h>
#include "common.h"
#include "ai.h"
#include "randomGen.h"

typedef struct _positionMemory {
  POSITION* memory;
  int size;
} POSITIONMEMORY;

struct _ai {
  POSITIONMEMORY positionMemory;
  int positionMemoryPointer;
  RANDOMGENERATOR* radnomGenerator;
};

static POSITION _assemblePosition(
  const int row,
  const int column
) {
  POSITION position;

  position.row = row;
  position.column = column;

  return position;
}

static int _initializePositionMemory(
  POSITIONMEMORY* positionMemory,
  const int nRows,
  const int nColumns
) {
  int error = 0;
  int row = 0;
  int col = 0;
  int pos = 0;

  if (NULL != positionMemory) {
    if (nRows * nColumns == positionMemory->size) {
      for (row = 0; row < nRows; row++) {
        for (col = 0; col < nColumns; col++) {
          positionMemory->memory[pos++] = _assemblePosition(row, col);
        }
      }
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }
  
  return error;
}

static int _getRandomPosition(
  POSITION* position,
  RANDOMGENERATOR* radnomGenerator,
  const POSITIONMEMORY* positionMemory
) {
  int error = 0;
  int idx = 0;

  if ((NULL != position) && (NULL != radnomGenerator) && (NULL != positionMemory)) {
    idx = randomGen_rand(radnomGenerator);

    if ((idx >= 0) && idx < (positionMemory->size)) {
      *position = positionMemory->memory[idx];
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }

  return error;
}

int ai_initialize(
  AI** cpuAI
) {
  int error = 0;
  AI* cpuAI_init = NULL;

  cpuAI_init = (AI*)calloc(1, sizeof(AI));

  if (NULL != cpuAI) {
    cpuAI_init->positionMemory.memory = (POSITION*)calloc(sizeof(POSITION), NUM_POSITIONS_ON_FIELD);
    cpuAI_init->positionMemory.size = NUM_POSITIONS_ON_FIELD;
    cpuAI_init->positionMemoryPointer = 0;

    if (NULL == cpuAI_init->positionMemory.memory) {
      error = 1;
    }

    if (0 == error) {
      error = _initializePositionMemory(&cpuAI_init->positionMemory,
                                        POSITION_MAX + 1,
                                        POSITION_MAX + 1);
    }

    if (0 == error) {
      error = ranndomGen_initialize(&cpuAI_init->radnomGenerator,
                                    cpuAI_init->positionMemory.size);
    }

    if (0 == error) {
      *cpuAI = cpuAI_init;
    }
  } else {
    error = 1;
  }

  return error;
}

int ai_free(
  AI** cpuAI
) {
  int error = 0;

  if (NULL != *cpuAI) {
    if (NULL != (*cpuAI)->positionMemory.memory) {
      free((*cpuAI)->positionMemory.memory);
      (*cpuAI)->positionMemory.memory = NULL;
      (*cpuAI)->positionMemory.size = 0;
      (*cpuAI)->positionMemoryPointer = 0;

      error = randomGen_free(&(*cpuAI)->radnomGenerator);

      free(*cpuAI);
      *cpuAI = NULL;
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }

  return error;
}

int ai_getShootPosition(
  POSITION* position,
  AI* cpuAI
) {
  int error = 0;

  if ((NULL != position) && (NULL != cpuAI)) {
    error = _getRandomPosition(position,
                               cpuAI->radnomGenerator,
                               &cpuAI->positionMemory);
  } else {
    error = 1;
  }

  return error;
}
