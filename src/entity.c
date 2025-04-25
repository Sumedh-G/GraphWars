#include "raylib.h"
#include "entity.h"

#define TERMINAL_VELOCITY 5

void UpdatePhysicsEntity(PhysicsEntity* entity, Vector2* inputMovement, float dt)
{
  Vector2 frameMovement = { inputMovement->x + entity->velocity.x, inputMovement->y + entity->velocity.y};
  // movement in x direction
  entity->position.x += frameMovement.x * dt;
  entity->velocity.x += entity->acceleration.x * dt;

  // movement in y direction
  entity->position.y += frameMovement.y * dt;
  entity->velocity.y = (entity->velocity.y < TERMINAL_VELOCITY) ? entity->velocity.y + entity->acceleration.y * dt : TERMINAL_VELOCITY;
}

void RenderPhysicsEntity(PhysicsEntity* entity)
{
  DrawRectangleV(entity->position, entity->size, RED);
}
