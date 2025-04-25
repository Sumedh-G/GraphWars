#pragma once
#include <raylib.h>

typedef struct Block {
  int worldPos[2];
  int spritePos[2];
} Block;

typedef struct Decor {
  int worldPos[2];
  int spritePos[2];
  int spriteSize[2];
} Decor;
