#ifndef I_DRAW_H
#define I_DRAW_H

#include "../lib.h"
#include "../common/CRect.h"

class IDraw
{
public:
    virtual void Draw(SDL_Surface* dst_surface, CRect dst_rect) = 0;
};

#endif // I_DRAW_H
