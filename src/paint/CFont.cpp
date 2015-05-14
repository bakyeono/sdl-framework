#include "./CFont.h"

const int CFont::tile_width  = 18;
const int CFont::tile_height = 18;
const int CFont::font_width  = 16;
const int CFont::font_height = 16;
const int CFont::cols        = 32;
const int CFont::rows        = 361;
const int CFont::dist_full   = 16;
const int CFont::dist_half   = 8;
const int CFont::dist_line   = 20;
const int CFont::size        = cols * rows;

CFont::CFont(EImageId _image_id)
    : image_id(_image_id)
{
}

CFont::~CFont()
{
}

void CFont::Draw(int code, const CColor& color,
                 SDL_Surface* dst_surface, CRect dst_rect)
{
    const int code_x       = code % cols;
    const int code_y       = code / cols;
    const int src_offset   = (code_y * cols * tile_width * tile_height) + (code_x * tile_width);
    const int dst_offset_w = dst_surface->w;
    const int dst_offset   = dst_rect.GetPosY() * dst_offset_w + dst_rect.GetPosX();
    Uint32    screen_color = color.GetScreenColor();
    Uint8*    src_pixels   = (Uint8*)CImageArray::Instance().GetImage(image_id).GetSurface()->pixels;
    Uint16*   t16_pixels   = (Uint16*)dst_surface->pixels;
    Uint32*   t32_pixels   = (Uint32*)dst_surface->pixels;

    // 대상 서페이스의 BPP에 따라 픽셀 배열 포인터를 변경해야 함.
    // 16 x 16 루프를 돌며 한 픽셀씩 찍음.
    // color에 src_pixels에서 참조한 마스크를 적용함.
    if (dst_surface->format->BitsPerPixel == 16)
    {
        for (int y = 0; y < font_height; ++y)
        {
            for (int x = 0; x < font_width; ++x)
            {
                if (src_pixels[(y * cols * tile_width + x) + src_offset])
                {
                    t16_pixels[(y * dst_offset_w + x) + dst_offset] =
                        screen_color * src_pixels[(y * cols * tile_width + x) + src_offset];
                }
            }
        }
    }
    else if (dst_surface->format->BitsPerPixel == 32)
    {
        for (int y = 0; y < font_height; ++y)
        {
            for (int x = 0; x < font_width; ++x)
            {
                if (src_pixels[(y * cols * tile_width + x) + src_offset])
                {
                    t32_pixels[(y * dst_offset_w + x) + dst_offset] =
                        screen_color * src_pixels[(y * cols * tile_width + x) + src_offset];
                }
            }
        }
    }
}
