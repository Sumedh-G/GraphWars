#include "raylib.h"
#include "entity.h"
#include "utils.h"
#include "tiles.h"

// standard for 16 bit pixel art
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCALE 2

#define TARGET_FPS 60

#define SS_BLOCKS_PATH "./data/assets/blocks/default.png"

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
    .acceleration = (Vector2) { 0, -0.1 },
    .size = (Vector2) { 16, 32 }
  };

  // Spritesheets
  Image blocktiles = LoadImage(SS_BLOCKS_PATH);
  // Screen to blit onto
  RenderTexture2D display = LoadRenderTexture(SCREEN_WIDTH / SCALE, SCREEN_HEIGHT / SCALE);

  while (!WindowShouldClose()) {

    BeginTextureMode(display);
    ClearBackground(DARKGRAY);
    RenderPhysicsEntity(&player);
    EndTextureMode();

    BeginDrawing();
    DrawTexturePro(
      display.texture,
      (Rectangle) { 0.0, 0.0, (float) SCREEN_WIDTH / SCALE, (float) SCREEN_HEIGHT / SCALE },
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
