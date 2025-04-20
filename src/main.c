#include "raylib.h"

// standard for 16 bit pixel art
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TARGET_FPS = 60;

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GraphWars");
  SetTargetFPS(TARGET_FPS);

  while (!WindowShouldClose()) {
    BeginDrawing();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
