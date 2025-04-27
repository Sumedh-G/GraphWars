#include "raylib.h"
#include "utils.h"

#define TILESIZE 16

Image GetTileSprite(Block* tile, Image *spritesheet)
{
  return ImageFromImage(*spritesheet, (Rectangle) { tile->spritePos[0]* TILESIZE, tile->spritePos[1]* TILESIZE, TILESIZE, TILESIZE });
}

Image GetDecorSprite(Decor* tile, Image *spritesheet)
{
  return ImageFromImage(*spritesheet, (Rectangle) { tile->spritePos[0], tile->spritePos[1], tile->spriteSize[0], tile->spriteSize[1] });
}
