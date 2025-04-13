#include "raylib.h"
#include "player.h"

const float PLAYER_WIDTH = 40.0f;
const float PLAYER_HEIGHT = 80.0f;
const float GRAVITY = 500.0f;

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
