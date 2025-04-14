#include "raylib.h"
#include "grid.h"

const int GRID_SPACING = 50;

void blitGrid(Grid *grid)
{
  for (int i=-grid->size; i<=grid->size; ++i) {
    DrawLine(
      grid->origin.x + GRID_SPACING * i,
      grid->origin.y + GRID_SPACING * grid->size,
      grid->origin.x + GRID_SPACING * i,
      grid->origin.y - GRID_SPACING * grid->size,
      RAYWHITE);

    DrawLine(
      grid->origin.x + GRID_SPACING * grid->size,
      grid->origin.y + GRID_SPACING * i,
      grid->origin.x - GRID_SPACING * grid->size,
      grid->origin.y + GRID_SPACING * i,
      RAYWHITE);
  }
}

