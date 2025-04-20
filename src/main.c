#include "raylib.h"
#include "entity.h"

// standard for 16 bit pixel art
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TARGET_FPS = 60;

void handleInput(int movement[2])
{
  // Set flag
  if (IsKeyDown(KEY_A)) movement[0] = 1;
  if (IsKeyDown(KEY_D)) movement[1] = 1;

  // Reset flag
  if (IsKeyUp(KEY_A)) movement[0] = 0;
  if (IsKeyUp(KEY_D)) movement[1] = 0;
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GraphWars");
  SetTargetFPS(TARGET_FPS);

  // Clock
  float dt;

  // Input Movement
  int movementx[2] = {0, 0};
  Vector2 inputMovement = {0, 0};

  PhysicsEntity player = {
    .type = "player",
    .position = (Vector2) { 100, 200 },
    .velocity = (Vector2) { 0, 0 },
    .acceleration = (Vector2) { 0, 0 },
    .size = (Vector2) { 50, 100 }
  };

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(BLACK);
    RenderPhysicsEntity(&player);
    EndDrawing();

    handleInput(movementx);
    inputMovement.x = movementx[1] - movementx[0];

    dt = GetFrameTime() * TARGET_FPS;
    UpdatePhysicsEntity(&player, &inputMovement, dt);
  }

  CloseWindow();
  return 0;
}
