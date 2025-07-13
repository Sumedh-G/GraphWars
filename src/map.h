#pragma once
#include "raylib.h"

#define TILESIZE 16

// TODO: Change this to allow for autotiling
#define TILESET_CAPACITY 16

typedef struct Tile_Struct Tile;
typedef struct TileSet_Struct TileSet;
typedef struct TileMap_Struct TileMap;
typedef struct Map_Struct Map;

typedef struct {
  unsigned int width;
  unsigned int height;
} Frame;

struct Tile_Struct {
  unsigned char cframe :4;    // Active frame index, What frame should be blitted?
  unsigned char lframe :4;    // Index of the last valid frame
  Frame frame_size;           // Size of 1 tile frame
  Texture2D spritesheet;      // Single sprite containing all frames
};

struct TileSet_Struct {
  unsigned char ctype       :4;
  unsigned char is_solid    :1;
  unsigned char is_visible  :1;
  unsigned char state       :2;
  Tile types[TILESET_CAPACITY];
};

/*
 * A tilemap can use upto 32 tilesets, for now to save memory
 * but supports upto 256 tiles
 */
struct TileMap_Struct {
  unsigned char ntypes :5;
  TileSet tilesets[32];
  Vector2 tile_size;
};


struct Map_Struct {
  // todo
};

void InitTile(Tile* tile, const char* filepath, Frame frame_size);
void DestroyTile(Tile* tile);

void InitTileSet(TileSet* tileset, const char* directorypath, Frame frame_size, bool is_solid, bool is_visible);
void DestroyTileSet(TileSet* tileset);
