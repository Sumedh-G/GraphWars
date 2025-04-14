#pragma once
#include "raylib.h"

typedef struct Grid {
  Vector2 origin;
  int size;
} Grid;

void blitGrid(Grid *grid);
