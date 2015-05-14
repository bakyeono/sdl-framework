#include "./CTileset.h"

CTileset::CTileset(EImageId _image_id,
                   int _tile_width,  int _tile_height,
                   int _cols,        int _rows,
                   int _dist_cols,   int _dist_cols_ex,
                   int _dist_rows,   int _dist_height,
                   int _x_mod,       int _y_mod)
    : image_id(_image_id),
      tile_width(_tile_width),
      tile_height(_tile_height),
      cols(_cols),
      rows(_rows),
      dist_cols(_dist_cols),
      dist_cols_ex(_dist_cols_ex),
      dist_rows(_dist_rows),
      dist_height(_dist_height),
      x_mod(_x_mod),
      y_mod(_y_mod),
      size(cols * rows)
{
}

CTileset::~CTileset()
{
}
