#pragma once
#include "raylib.h"

typedef struct Entity {
  char type[16];
  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;
  Vector2 size;
} PhysicsEntity;


void UpdatePhysicsEntity(PhysicsEntity* entity, Vector2* inputMovement, float dt);
void RenderPhysicsEntity(PhysicsEntity* entity);
