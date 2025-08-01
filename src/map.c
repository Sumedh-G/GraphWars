#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

#include "raylib.h"
#include "utils.h"
#include "map.h"

void InitTile(Tile *tile, const char *filepath, Frame frame_size)
{
    if (tile == NULL || filepath == NULL) {
        WriteLog(LOG_ERROR, "Cannot initialize tile from NULL pointer. Recieved tile: %p and path: \"%s\"", tile, filepath);
        return;
    }
    if (!FileExists(filepath)) {
        WriteLog(LOG_ERROR, "No such file \"%s\".", filepath);
        return;
    }

    tile->frame_size = frame_size;
    tile->spritesheet = LoadTexture(filepath);
    tile->cframe = 0;
    tile->lframe = ((tile->spritesheet).width / frame_size.width) - 1;

    return;
}

void DestroyTile(Tile *tile)
{
    if (tile == NULL) {
        WriteLog(LOG_WARNING, "Tried to destroy NULL tile.");
        return;
    }

    UnloadTexture(tile->spritesheet);
    return;
}


void InitTileSet(TileSet* tileset, const char* directorypath, Frame frame_size, bool is_solid, bool is_visible)
{
    if (!tileset || !directorypath) {
        WriteLog(LOG_ERROR, "Cannot initialize NULL tileset. Recieved tileset: %p, directorypath: \"%s\".", tileset, directorypath);
        return;
    }
    if (!DirectoryExists(directorypath)) {
        WriteLog(LOG_ERROR, "No such directory \"%s\".", directorypath);
        return;
    }

    tileset->ctype = 0;
    tileset->state = 0;
    tileset->is_solid = is_solid;
    tileset->is_visible = is_visible;

    FilePathList tile_sprites = LoadDirectoryFiles(directorypath);
    int file_index = 0;
    while (FileExists(tile_sprites.paths[file_index])) {

        if (file_index >= TILESET_CAPACITY) {
            WriteLog(LOG_WARNING, "Too many tiles in directory, cannot load more than %u tiles per tileset.", TILESET_CAPACITY);
            break;
        }

        InitTile(tileset->types + file_index, tile_sprites.paths[file_index], frame_size);
        file_index++;
    }

    return;
}

void DestroyTileSet(TileSet* tileset)
{
    if (!tileset) {
        WriteLog(LOG_WARNING, "Tried to destroy NULL tileset.") ;
    }

    for (int i=0; i < TILESET_CAPACITY; ++i) {
        DestroyTile(tileset->types + i);
    }

    return;
}
