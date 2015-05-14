#ifndef C_FONT_H
#define C_FONT_H

#include "../lib.h"
#include "../common/CRect.h"
#include "../common/CColor.h"
#include "./CImageArray.h"
#include "./EImageId.h"

class CFont
{
public:
    explicit CFont(EImageId image_id);
    ~CFont(void);

public:
    void Draw(int code, const CColor& color,
              SDL_Surface* dst_surface, CRect dst_rect);
    inline EImageId         GetImageId() const;
    inline void             SetImageId(EImageId _image_id);
    inline const CFont&     operator = (const CFont& src);

public:
    inline static int       GetTileWidth();
    inline static int       GetTileHeight();
    inline static int       GetFontWidth();
    inline static int       GetFontHeight();
    inline static int       GetCols();
    inline static int       GetRows();
    inline static int       GetDistFull();
    inline static int       GetDistHalf();
    inline static int       GetDistLine();
    inline static int       GetSize();

private:
    static const int tile_width;     // 개별 타일의 가로 크기
    static const int tile_height;    // 개별 타일의 세로 크기
    static const int font_width;     // 개별 타일의 가로 크기
    static const int font_height;    // 개별 타일의 세로 크기
    static const int cols;           // 타일셋의 열 수
    static const int rows;           // 타일셋의 행 수
    static const int dist_full;      // 타일배치간격(가로)
    static const int dist_half;      // 타일배치간격(가로)
    static const int dist_line;      // 타일배치간격(세로)
    static const int size;           // 타일의 총 개수

private:
    EImageId         image_id;
};

EImageId CFont::GetImageId() const
{
    return image_id;
}

void CFont::SetImageId(EImageId _image_id)
{
    image_id = _image_id;
}

const CFont& CFont::operator = (const CFont& src)
{
    image_id = src.image_id;
    return *this;
}

int CFont::GetTileWidth()
{
    return tile_width;
}

int CFont::GetTileHeight()
{
    return tile_height;
}

int CFont::GetFontWidth()
{
    return font_width;
}

int CFont::GetFontHeight()
{
    return font_height;
}

int CFont::GetCols()
{
    return cols;
}

int CFont::GetRows()
{
    return rows;
}

int CFont::GetDistFull()
{
    return dist_full;
}

int CFont::GetDistHalf()
{
    return dist_half;
}

int CFont::GetDistLine()
{
    return dist_line;
}

int CFont::GetSize()
{
    return size;
}

#endif // C_FONT_H
