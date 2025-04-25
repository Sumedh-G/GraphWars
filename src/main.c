#include "raylib.h"
#include "entity.h"

// standard for 16 bit pixel art
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TARGET_FPS 60

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
    .position = (Vector2) { 50, 10 },
    .velocity = (Vector2) { 0, 0 },
    .acceleration = (Vector2) { 0, 0 },
    .size = (Vector2) { 16, 32 }
  };

  RenderTexture2D display = LoadRenderTexture(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

  while (!WindowShouldClose()) {

    BeginTextureMode(display);
    ClearBackground(GRAY);
    RenderPhysicsEntity(&player);
    EndTextureMode();

    BeginDrawing();
    DrawTexturePro(
      display.texture,
      (Rectangle) { 0.0, 0.0, SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0 },
      (Rectangle) { 0.0, 0.0, SCREEN_WIDTH, SCREEN_HEIGHT },
      (Vector2) { 0, 0 },
      0.0,
      WHITE
    );
    EndDrawing();

    handleInput(movementx);
    inputMovement.x = 5 * (movementx[1] - movementx[0]);

    dt = GetFrameTime() * TARGET_FPS;
    UpdatePhysicsEntity(&player, &inputMovement, dt);
  }

  UnloadRenderTexture(display);

  CloseWindow();
  return 0;
}
