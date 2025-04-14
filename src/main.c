#include "raylib.h"
#include "player.h"
#include <stddef.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TARGET_FPS = 60;

void drawBackground();

int main() {

  // temporary player
  Vector2 startPos = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
  Player player = { "Main", startPos, {0.0f, 0.0f }, { startPos, 5 }};

  // Initialise window for the game
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GraphWars");
  SetTargetFPS(TARGET_FPS);

  float dt;
  // Main loop for drawing on the screen
  while (!WindowShouldClose()) {
    // Player Mechanics
    dt = GetFrameTime();
    movePlayer(&player);
    // updatePlayer(&player, dt);
    updateGrid(&player);

    BeginDrawing();
      drawBackground();
      blitGrid(&player.currentGrid);
      drawPlayerFrame(&player);
    EndDrawing();
  }

  // Clean exit
  CloseWindow();

  return 0;
}

void drawBackground()
{
  // make the background black (temporary)
  ClearBackground(BLACK);
}
