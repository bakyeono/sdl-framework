#include "./CKeyboardEvent.h"

CKeyboardEvent::CKeyboardEvent()
{
}

CKeyboardEvent::CKeyboardEvent(SDL_Event event)
    : type(event.key.type),
      keycode(event.key.keysym.sym)
{
}

CKeyboardEvent::~CKeyboardEvent()
{
}
