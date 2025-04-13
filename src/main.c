#include <raylib.h>
#include "constants.h"

extern const int SCREEN_WIDTH, SCREEN_HEIGHT;
extern const int TARGET_FPS;

void drawBackground();

int main() {

  // Initialise window for the game
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GraphWars");
  SetTargetFPS(TARGET_FPS);

  // Main loop for drawing on the screen
  while (!WindowShouldClose()) {
    BeginDrawing();
      drawBackground();
    EndDrawing();
  }

  // Clean exit
  CloseWindow();

  return 0;
}

void drawBackground()
{
  // make the background white (temporary)
  ClearBackground(RAYWHITE);
}
