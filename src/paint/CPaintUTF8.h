#ifndef C_PAINT_UTF8_H
#define C_PAINT_UTF8_H

#include "../lib.h"
#include "./CPaint.h"
#include "./CFont.h"
#include "../util/CUTF8Util.h"

using namespace std;

class CPaintUTF8
    : public CPaint
{
public:
    explicit CPaintUTF8();
    explicit CPaintUTF8(const CRect& _rect,
                        const CFont& _font, const CColor& _color,
                        const string& _str = "");
    virtual ~CPaintUTF8();

public:
    virtual void          SetRect(const CRect& _rect);
    virtual const CFont&  GetFont() const;
    virtual void          SetFont(const CFont& _font);
    virtual const CColor& GetColor() const;
    virtual void          SetColor(const CColor& _color);
    virtual const string& GetString() const;
    virtual void          SetString(const string& _str);
    virtual void          Draw(SDL_Surface* dst_surface, CRect dst_rect);

private:
    CFont   font;
    CColor  color;
    string  str;
    int     ch_limit;
};

#endif // C_PAINT_UTF8_H
