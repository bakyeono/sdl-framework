#ifndef C_PAINT_H
#define C_PAINT_H

#include "../lib.h"
#include "../common/CRect.h"
#include "./IDraw.h"

class CPaint
    : public IDraw
{
public:
    explicit CPaint();
    explicit CPaint(const CRect& _rect);
    virtual ~CPaint();

public:
    virtual CRect   GetRect() const;
    virtual void    SetRect(const CRect& _rect);
    virtual void    Draw(SDL_Surface* dst_surface, CRect dst_rect) = 0;

private:
    CRect           rect;
};

#endif // C_PAINT_H
