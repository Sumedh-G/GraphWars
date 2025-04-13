#include "raylib.h"
#include "player.h"

const float PLAYER_WIDTH = 40.0f;
const float PLAYER_HEIGHT = 80.0f;

Rectangle getPlayerBoundingBox(Player *p)
{
  Rectangle bound = { p->position.x, p->position.y, PLAYER_WIDTH, PLAYER_HEIGHT };
  return bound;
}

void drawPlayerFrame(Player *p)
{
  DrawRectangle((int)(p->position.x), (int)(p->position.y), (int)PLAYER_WIDTH, (int)PLAYER_HEIGHT, RED);
}
