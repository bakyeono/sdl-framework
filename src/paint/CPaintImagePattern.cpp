#include "./CPaintImagePattern.h"

CPaintImagePattern::CPaintImagePattern()
{
}

CPaintImagePattern::CPaintImagePattern(const CRect& _rect, EImageId _image_id)
    : CPaintImage(_rect, _image_id)
{
}

CPaintImagePattern::~CPaintImagePattern()
{
}

void CPaintImagePattern::Draw(SDL_Surface* dst_surface, CRect dst_rect)
{
}
