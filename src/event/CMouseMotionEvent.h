#ifndef C_MOUSE_MOTION_EVENT_H
#define C_MOUSE_MOTION_EVENT_H

#include "../lib.h"
#include "../common/CPos.h"

class CMouseMotionEvent
{
public:
    explicit CMouseMotionEvent();
    explicit CMouseMotionEvent(SDL_Event event);
    ~CMouseMotionEvent();

public:
    inline const CPos&   GetPos() const;
    inline void          Set(SDL_Event event);

private:
    CPos          pos;
};

const CPos& CMouseMotionEvent::GetPos() const
{
    return pos;
}

void CMouseMotionEvent::Set(SDL_Event event)
{
    pos = CPos(event.button.x, event.button.y);
}

#endif // C_MOUSE_MOTION_EVENT_H
