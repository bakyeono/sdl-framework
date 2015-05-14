#ifndef C_VIDEO_RESIZE_EVENT_H
#define C_VIDEO_RESIZE_EVENT_H

#include "../lib.h"

class CVideoResizeEvent
{
public:
    explicit CVideoResizeEvent();
    explicit CVideoResizeEvent(SDL_Event event);
    ~CVideoResizeEvent();

public:
    inline int    GetWidth() const;
    inline int    GetHeight() const;
    inline void   Set(SDL_Event event);

private:
    int    width;
    int    height;
};

int CVideoResizeEvent::GetWidth() const
{
    return width;
}

int CVideoResizeEvent::GetHeight() const
{
    return height;
}

void CVideoResizeEvent::Set(SDL_Event event)
{
    width  = event.resize.w;
    height = event.resize.h;
}

#endif // C_VIDEO_RESIZE_EVENT_H
