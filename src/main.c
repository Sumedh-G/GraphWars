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

  /*
    * Think of the screen as a image
    * We load this image onto the GPU as a texture, and draw
    * elements of the game onto it.
    *
    * This texture is then scaled up and blitted to the screen once per frame,
    * making it incredibly efficient since only 1 image is loaded into memory
    * regardless of the number of entities to be drawn onto the screen.
    *
    * Each entity needs to be loaded onto the gpu only once during its creation,
    * and post-processing effects using shaders also become easy to do. loading images
    * also becomes vastly simpler
    *
    * physics for bodies can be offloaded to computations done upon their bounding boxes.
    *
    * TODO:
    *
    * 1) after creating a screen texture, create a function that renders onto the screen
    *   using game variables
    *
    * 2) allow for post-processing by using data offloaded to the GPU
    *
    * 3) Bring back final screen and blit it once per frame
  */

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
    RenderPhysicsEntity(&player);       // blit this onto a screen rather than directly
    EndDrawing();

    handleInput(movementx);
    inputMovement.x = movementx[1] - movementx[0];

    dt = GetFrameTime() * TARGET_FPS;
    UpdatePhysicsEntity(&player, &inputMovement, dt);
  }

  CloseWindow();
  return 0;
}
