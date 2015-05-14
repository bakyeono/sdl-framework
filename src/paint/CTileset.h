#ifndef C_TILESET_H
#define C_TILESET_H

#include "../lib.h"
#include "./IDraw.h"
#include "./CImageArray.h"

class CTileset
{
public:
    explicit CTileset(EImageId _image_id,
                      int _tile_width,  int _tile_height,
                      int _cols,        int _rows,
                      int _dist_cols,   int _dist_cols_ex,
                      int _dist_rows,   int _dist_height,
                      int _x_mod,       int _y_mod);
    ~CTileset(void);

public:
    inline void      DrawTile(int tile_id, SDL_Surface* dst_surface, CRect dst_rect);
    inline void      DrawTile(int tile_y, int tile_x,
                              SDL_Surface* dst_surface, CRect dst_rect);
    inline EImageId  GetImageId() const;
    inline int       GetTileWidth() const;
    inline int       GetTileHeight() const;
    inline int       GetCols() const;
    inline int       GetRows() const;
    inline int       GetDistCols() const;
    inline int       GetDistColsEx() const;
    inline int       GetDistRows() const;
    inline int       GetDistHeight() const;
    inline int       GetXMod() const;
    inline int       GetYMod() const;
    inline int       GetSize() const;
    inline CRect     GetTileRect(int tile_id) const;
    inline CRect     GetTileRect(int tile_y, int tile_x) const;

private:
    const EImageId  image_id;
    const int       tile_width;     // 개별 타일의 가로 크기
    const int       tile_height;    // 개별 타일의 세로 크기
    const int       cols;           // 타일셋의 열 수
    const int       rows;           // 타일셋의 행 수
    const int       dist_cols;      // 타일배치간격(가로)
    const int       dist_cols_ex;   // 홀수y축타일배치간격(가로)
    const int       dist_rows;      // 타일배치간격(세로)
    const int       dist_height;    // 타일배치간격(높이)
    const int       x_mod;          // x축 재배치 값
    const int       y_mod;          // y축 재배치 값
    const int       size;           // 타일의 총 개수
};

EImageId CTileset::GetImageId() const
{
    return image_id;
}

int CTileset::GetTileWidth() const
{
    return tile_width;
}

int CTileset::GetTileHeight() const
{
    return tile_height;
}

int CTileset::GetCols() const
{
    return cols;
}

int CTileset::GetRows() const
{
    return rows;
}

int CTileset::GetDistCols() const
{
    return dist_cols;
}

int CTileset::GetDistColsEx() const
{
    return dist_cols_ex;
}

int CTileset::GetDistRows() const
{
    return dist_rows;
}

int CTileset::GetDistHeight() const
{
    return dist_height;
}

int CTileset::GetXMod() const
{
    return x_mod;
}

int CTileset::GetYMod() const
{
    return y_mod;
}

int CTileset::GetSize() const
{
    return size;
}

CRect CTileset::GetTileRect(int tile_id) const
{
#ifdef YEONO_DEBUG
    if (size < tile_id)
        cerr << "[경고] 타일셋 범위를 초과한 타일 호출 : " << tile_id << endl;
#endif // YEONO_DEBUG
    int x = tile_id % cols;
    int y = tile_id / cols;
    return CRect(tile_width, tile_height, x * tile_width, y * tile_height);
}

CRect CTileset::GetTileRect(int tile_y, int tile_x) const
{
#ifdef YEONO_DEBUG
    if (rows < tile_y || cols < tile_x)
        cerr << "[경고] 타일셋 범위를 초과한 타일 호출 : (세로" << tile_y << ", 가로" << tile_x << ")"<< endl;
#endif // YEONO_DEBUG
    return CRect(tile_width, tile_height, tile_x * tile_width, tile_y * tile_height);

}

void CTileset::DrawTile(int tile_id, SDL_Surface* dst_surface, CRect dst_rect)
{
    CImageArray::Instance().GetImage(image_id).Draw(GetTileRect(tile_id),
            dst_surface, dst_rect);
}

void CTileset::DrawTile(int tile_y, int tile_x, SDL_Surface* dst_surface, CRect dst_rect)
{
    CImageArray::Instance().GetImage(image_id).Draw(GetTileRect(tile_y, tile_x),
            dst_surface, dst_rect);
}

#endif // C_TILESET_H
