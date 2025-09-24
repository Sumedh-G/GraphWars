#include "map.h"
#include "raylib.h"
#include "utils.h"

int main() {
  SetTraceLogCallback(CustomLog);

  InitWindow(640, 480, "GraphWars");

  TileSet tileset;
  InitTileSet(&tileset, "/home/crownedhog/projects/GraphWars/data/tiles/debug",
              (Frame){.width = 16, .height = 16}, true, true);

  WriteLog(LOG_DEBUG, "Loaded image %ux%u pixels.",
           (tileset.types[0]).frame_size.width,
           (tileset.types[0]).frame_size.height);

  DestroyTileSet(&tileset);

  CloseWindow();
  return 0;
}
