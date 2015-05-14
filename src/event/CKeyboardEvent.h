#ifndef C_KEYBOARD_EVENT_H
#define C_KEYBOARD_EVENT_H

#include "../lib.h"

class CKeyboardEvent
{
public:
    explicit CKeyboardEvent();
    explicit CKeyboardEvent(SDL_Event event);
    ~CKeyboardEvent();

public:
    inline int    GetType() const;
    inline int    GetKeycode() const;
    inline void   Set(SDL_Event event);

private:
    int    type;
    int    keycode;
};

int CKeyboardEvent::GetType() const
{
    return type;
}

int CKeyboardEvent::GetKeycode() const
{
    return keycode;
}

void CKeyboardEvent::Set(SDL_Event event)
{
    type    = event.key.type;
    keycode = event.key.keysym.sym;
}

#endif // C_KEYBOARD_EVENT_H
