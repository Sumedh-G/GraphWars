#include "raylib.h"
#include "player.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TARGET_FPS = 60;

void drawBackground();

int main() {

  // Create a temporary dummy player
  Vector2 startPos = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
  Vector2 startVel = { 0.0f, 0.0f };
  Player player = { "test", startPos, startVel };

  // Initialise window for the game
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GraphWars");
  SetTargetFPS(TARGET_FPS);

  float dt;
  // Main loop for drawing on the screen
  while (!WindowShouldClose()) {
    // Player Mechanics
    dt = GetFrameTime();
    movePlayer(&player);
    updatePlayer(&player, dt);

    BeginDrawing();
      drawBackground();
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
