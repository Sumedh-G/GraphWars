#pragma once
#include "raylib.h"

typedef struct Player {
  const char name[20];
  Vector2 position;
} Player;

Rectangle getPlayerBoundingBox(Player *p);
void drawPlayerFrame(Player *p);
