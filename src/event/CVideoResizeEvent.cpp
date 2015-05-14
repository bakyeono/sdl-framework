#include "./CVideoResizeEvent.h"

CVideoResizeEvent::CVideoResizeEvent()
{
}

CVideoResizeEvent::CVideoResizeEvent(SDL_Event event)
    : width(event.resize.w),
      height(event.resize.h)
{
}

CVideoResizeEvent::~CVideoResizeEvent()
{
}
