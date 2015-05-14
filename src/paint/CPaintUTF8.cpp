#include "./CPaintUTF8.h"

CPaintUTF8::CPaintUTF8()
    : font(CFont(EImageId::font_formal))
{
}

CPaintUTF8::CPaintUTF8(const CRect& _rect,
                       const CFont& _font, const CColor& _color,
                       const string& _str)
    : CPaint(_rect),
      font(_font),
      color(_color),
      str(_str),
      ch_limit(GetRect().GetWidth() / CFont::GetDistHalf())
{
}

CPaintUTF8::~CPaintUTF8()
{
}

void CPaintUTF8::SetRect(const CRect& _rect)
{
    CPaint::SetRect(_rect);
    ch_limit = GetRect().GetWidth() / CFont::GetDistHalf();
}

const CFont& CPaintUTF8::GetFont() const
{
    return font;
}

void CPaintUTF8::SetFont(const CFont& _font)
{
    font = _font;
}

const CColor& CPaintUTF8::GetColor() const
{
    return color;
}

void CPaintUTF8::SetColor(const CColor& _color)
{
    color = _color;
}

const string& CPaintUTF8::GetString() const
{
    return str;
}

void CPaintUTF8::SetString(const string& _str)
{
    str = _str;
}

void CPaintUTF8::Draw(SDL_Surface* dst_surface, CRect dst_rect)
{
    CRect offset(GetRect().CalcOffset(dst_rect));
    CPos  offset_base(offset.GetPos());
    int   ch = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (ch >= ch_limit)
            break;
        if (CUTF8Util::IsASCIICode((Uint8)str[i]))
        {
            font.Draw((Uint8)str[i], color, dst_surface, offset);
            offset.SetPosX(offset.GetPosX() + font.GetDistHalf());
            ++ch;
        }
        else
        {
            font.Draw(CUTF8Util::FontCode((Uint8)str[i], (Uint8)str[i++], (Uint8)str[i++]), color, dst_surface, offset);
            offset.SetPosX(offset.GetPosX() + font.GetDistFull());
            ch += 2;
        }
    }
}
