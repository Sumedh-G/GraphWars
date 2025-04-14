#include "raylib.h"
#include "player.h"

const float PLAYER_WIDTH = 40.0f;
const float PLAYER_HEIGHT = 80.0f;
const float GRAVITY = 500.0f;
const int GRID_SPACING = 20;
const int MAJOR_GRID_SPACING = 50;
const int MAX_GRID_SIZE = (6 * MAJOR_GRID_SPACING) / GRID_SPACING;
const float SCALE_SENSITIVITY = 1.0f;

Rectangle getPlayerBoundingBox(Player *p)
{
  Rectangle bound = { p->position.x, p->position.y, PLAYER_WIDTH, PLAYER_HEIGHT };
  return bound;
}

void drawPlayerFrame(Player *p)
{
  DrawRectangle(p->position.x, p->position.y, PLAYER_WIDTH, PLAYER_HEIGHT, RED);
}

void updatePlayer(Player *p, float dt)
{
  p->speed.y += GRAVITY * dt;
  p->position.x += p->speed.x * dt;
  p->position.y += p->speed.y * dt;
}

void movePlayer(Player *p)
{
  // TODO : Convert to switch case
  if (IsKeyDown(KEY_A)) p->speed.x = -100;
  else if (IsKeyDown(KEY_D)) p->speed.x = 100;
  else p->speed.x = 0;
}

void updateGrid(Player *player)
{
  float scale;
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) player->currentGrid.origin = GetMousePosition();
  else {
    player->currentGrid.origin.x = player->position.x + PLAYER_WIDTH/2.0f;
    player->currentGrid.origin.y = player->position.y + PLAYER_HEIGHT;
  }

  if (player->currentGrid.size < 0) { player->currentGrid.size = 0; return; }
  if ((scale = GetMouseWheelMove()) != 0) {
    int increment = player->currentGrid.size + (int)(SCALE_SENSITIVITY * scale);
    player->currentGrid.size = ( increment > MAX_GRID_SIZE) ? MAX_GRID_SIZE : increment;
  }
}

void blitGrid(Grid *grid)
{
  for (int i=-grid->size; i<=grid->size; ++i) {
    Color linecolor = (i*GRID_SPACING % MAJOR_GRID_SPACING) ? DARKGRAY : RAYWHITE;
    DrawLine(
      grid->origin.x + GRID_SPACING * i,
      grid->origin.y + GRID_SPACING * grid->size,
      grid->origin.x + GRID_SPACING * i,
      grid->origin.y - GRID_SPACING * grid->size,
      linecolor);

    DrawLine(
      grid->origin.x + GRID_SPACING * grid->size,
      grid->origin.y + GRID_SPACING * i,
      grid->origin.x - GRID_SPACING * grid->size,
      grid->origin.y + GRID_SPACING * i,
      linecolor);
  }
}

