#ifndef E_IMAGE_ID_H
#define E_IMAGE_ID_H

#include "../lib.h"

enum class EImageId
    : int
{
    none                 = -1,
    font_formal          = 0,
    font_casual          = 1,
    tileset_terrain      = 2,
    tileset_terrain_fog  = 3,
    tileset_wall         = 4,
    tileset_wall_fog     = 5,
    tileset_tree         = 6,
    tileset_tree_fog     = 7,
    tileset_world        = 8,
    tileset_creature     = 9,
    tileset_grid         = 10,
    illust_0             = 11,
    illust_1             = 12,
};

#endif // E_IMAGE_ID_H
