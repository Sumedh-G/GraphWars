#pragma once
#include "raylib.h"
#include "grid.h"

typedef struct Player {
  const char name[20];
  Vector2 position;
  Vector2 speed;
  Grid currentGrid;
} Player;

Rectangle getPlayerBoundingBox(Player *p);
void drawPlayerFrame(Player *p);
void updatePlayer(Player *p, float dt);
void movePlayer(Player *p);

void updateGrid(Player *player);
