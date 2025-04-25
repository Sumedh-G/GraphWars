
#include <raylib.h>

typedef struct GridTile {
  int position[2];
  char name[8];
  char variant[4];
} GridTile;

typedef struct Decor {
  Vector2 position;
  char name[8];
  char variant[4];
} Decor;
