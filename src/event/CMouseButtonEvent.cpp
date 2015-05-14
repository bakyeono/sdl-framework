#include "./CMouseButtonEvent.h"

CMouseButtonEvent::CMouseButtonEvent()
{
}

CMouseButtonEvent::CMouseButtonEvent(SDL_Event event)
    : type(event.button.type),
      button(event.button.type),
      pos(CPos(event.button.x, event.button.y)),
      owner(0)
{
}

CMouseButtonEvent::~CMouseButtonEvent()
{
}
