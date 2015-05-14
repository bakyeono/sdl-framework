#include "./CMouseMotionEvent.h"

CMouseMotionEvent::CMouseMotionEvent()
{
}

CMouseMotionEvent::CMouseMotionEvent(SDL_Event event)
    : pos(CPos(event.button.x, event.button.y))
{
}

CMouseMotionEvent::~CMouseMotionEvent()
{
}
