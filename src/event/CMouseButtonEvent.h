#ifndef C_MOUSE_BUTTON_EVENT_H
#define C_MOUSE_BUTTON_EVENT_H

#include "../lib.h"
#include "../common/CPos.h"
#include "../common/IObserver.h"

class CMouseButtonEvent
{
public:
    explicit CMouseButtonEvent();
    explicit CMouseButtonEvent(SDL_Event event);
    ~CMouseButtonEvent();

public:
    inline int                           GetType() const;
    inline int                           GetButton() const;
    inline const CPos&                   GetPos() const;
    inline void                          Set(SDL_Event event);
    inline void                          SetOwner(IObserver<CMouseButtonEvent>* owner);
    inline IObserver<CMouseButtonEvent>* GetOwner();

private:
    int                           type;
    int                           button;
    CPos                          pos;
    IObserver<CMouseButtonEvent>* owner;
};

int CMouseButtonEvent::GetType() const
{
    return type;
}

int CMouseButtonEvent::GetButton() const
{
    return button;
}

const CPos& CMouseButtonEvent::GetPos() const
{
    return pos;
}

void CMouseButtonEvent::Set(SDL_Event event)
{
    type   = event.button.type;
    button = event.button.button;
    pos    = CPos(event.button.x, event.button.y);
    owner  = 0;
}

void CMouseButtonEvent::SetOwner(IObserver<CMouseButtonEvent>* _owner)
{
    owner = _owner;
}

IObserver<CMouseButtonEvent>* CMouseButtonEvent::GetOwner()
{
    return owner;
}

#endif // C_MOUSE_BUTTON_EVENT_H
