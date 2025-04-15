#include "raylib.h"
#include "player.h"

const float PLAYER_WIDTH = 40.0f;
const float PLAYER_HEIGHT = 80.0f;
const float GRAVITY = 800.0f;

const int GRID_SPACING = 20;
const int MAJOR_GRID_SPACING = 50;
const int MAX_GRID_SIZE = (6 * MAJOR_GRID_SPACING) / GRID_SPACING;
const float SCALE_SENSITIVITY = 1.0f;

const float FUNCTION_RESOLUTION = 0.1;

static int renderGrid = 0;
static float scaleGrid = 0.0;
static int inAir = 0;

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

  // temporary floor minimum
  if (p->position.y >= 500) {
    p->position.y = 500;
    inAir = 0;
  }
  else {
    inAir = 1;
  }
}

void movePlayer(Player *p)
{
  int key = GetKeyPressed();
    do {
    switch (key) {
      case KEY_W:
        p->speed.y = (!inAir) ? -400 : p->speed.y;
        break;
      case KEY_A:
        p->speed.x = -200;
        break;
      case KEY_D:
        p->speed.x = 200;
        break;
      case KEY_J:
        p->currentGrid.origin.y += (renderGrid) * MAJOR_GRID_SPACING;
        break;
      case KEY_K:
        p->currentGrid.origin.y -= (renderGrid) * MAJOR_GRID_SPACING;
        break;
      case KEY_H:
        p->currentGrid.origin.x -= (renderGrid) * MAJOR_GRID_SPACING;
        break;
      case KEY_L:
        p->currentGrid.origin.x += (renderGrid) * MAJOR_GRID_SPACING;
        break;
      case KEY_SEMICOLON:
        p->currentGrid.size = ( p->currentGrid.size + SCALE_SENSITIVITY > MAX_GRID_SIZE) ?
          MAX_GRID_SIZE : p->currentGrid.size + SCALE_SENSITIVITY;
        break;
      case KEY_APOSTROPHE:
        p->currentGrid.size = ( p->currentGrid.size - SCALE_SENSITIVITY > MAX_GRID_SIZE) ?
          MAX_GRID_SIZE : p->currentGrid.size - SCALE_SENSITIVITY;
        break;
    }
  } while ((key = GetKeyPressed()));

  if (p->speed.x) {
    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) p->speed.x = 0;
  }
}

void updateGrid(Player *player)
{
  if (!IsMouseButtonUp(MOUSE_BUTTON_LEFT)) player->currentGrid.origin = GetMousePosition();
  else if (renderGrid);
  else {
    player->currentGrid.origin.x = player->position.x + PLAYER_WIDTH/2.0f;
    player->currentGrid.origin.y = player->position.y + PLAYER_HEIGHT;
  }

  if (player->currentGrid.size < 0) player->currentGrid.size = 0;
  else if ((scaleGrid = GetMouseWheelMove()) != 0) {
    int increment = player->currentGrid.size + (int)(SCALE_SENSITIVITY * scaleGrid);
    player->currentGrid.size = ( increment > MAX_GRID_SIZE) ? MAX_GRID_SIZE : increment;
  }
}

void blitGrid(Grid *grid)
{
  renderGrid= IsKeyDown(KEY_LEFT_SHIFT);

  if (renderGrid) {
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
}
