#ifndef C_SYSTEM_EVENT_MANAGER_H
#define C_SYSTEM_EVENT_MANAGER_H

#include "../lib.h"
#include "../common/CSubject.h"
#include "../common/CPos.h"
#include "../ctrl/CExitCtrl.h"
#include "./CMouseButtonEvent.h"
#include "./CMouseMotionEvent.h"
#include "./CKeyboardEvent.h"
#include "./CQuitEvent.h"
#include "./CVideoResizeEvent.h"
#include "../ui/frame/IUIFrame.h"
#include "../ui/frame/CUIFrameSortOption.h"
#include "../ctrl/CScreenCtrl.h"

class CSystemEventManager
{
private:
    explicit CSystemEventManager();
    ~CSystemEventManager();

public:
    inline static CSystemEventManager& Instance();
    void Update();
    inline void RegisterQuitEventObserver(IObserver<CQuitEvent>* observer);
    inline void RemoveQuitEventObserver(IObserver<CQuitEvent>* observer);
    inline void RegisterMouseButtonEventObserver(IObserver<CMouseButtonEvent>* observer);
    inline void RemoveMouseButtonEventObserver(IObserver<CMouseButtonEvent>* observer);
    inline void RegisterMouseMotionEventObserver(IObserver<CMouseMotionEvent>* observer);
    inline void RemoveMouseMotionEventObserver(IObserver<CMouseMotionEvent>* observer);
    inline void RegisterKeyboardEventObserver(IObserver<CKeyboardEvent>* observer);
    inline void RemoveKeyboardEventObserver(IObserver<CKeyboardEvent>* observer);
    inline void RegisterVideoResizeEventObserver(IObserver<CVideoResizeEvent>* observer);
    inline void RemoveVideoResizeEventObserver(IObserver<CVideoResizeEvent>* observer);
    inline void RegisterEventOwnerInfo(IUIFrame* frame);
    inline void RemoveEventOwnerInfo(IUIFrame* frame);

private:
    void FindMouseButtonEventOwner();

private:
    SDL_Event                        event;
    CSubject<CQuitEvent>             quit_event_subject;
    CSubject<CMouseButtonEvent>      mouse_button_event_subject_for_frames;
    CSubject<CMouseButtonEvent>      mouse_button_event_subject;
    CSubject<CMouseMotionEvent>      mouse_motion_event_subject;
    CSubject<CKeyboardEvent>         keyboard_event_subject;
    CSubject<CVideoResizeEvent>      video_resize_event_subject;
    CQuitEvent                       quit_button_event;
    CMouseButtonEvent                mouse_button_event;
    CMouseMotionEvent                mouse_motion_event;
    CKeyboardEvent                   keyboard_event;
    CVideoResizeEvent                video_resize_event;
    vector<IUIFrame*>  frame_info_array;
};

CSystemEventManager& CSystemEventManager::Instance()
{
    static CSystemEventManager instance;
    return instance;
}

void CSystemEventManager::RegisterQuitEventObserver(IObserver<CQuitEvent>* observer)
{
    quit_event_subject.RegisterObserver(observer);
}

void CSystemEventManager::RemoveQuitEventObserver(IObserver<CQuitEvent>* observer)
{
    quit_event_subject.RemoveObserver(observer);
}

void CSystemEventManager::RegisterMouseButtonEventObserver(IObserver<CMouseButtonEvent>* observer)
{
    mouse_button_event_subject.RegisterObserver(observer);
}

void CSystemEventManager::RemoveMouseButtonEventObserver(IObserver<CMouseButtonEvent>* observer)
{
    mouse_button_event_subject.RemoveObserver(observer);
}

void CSystemEventManager::RegisterMouseMotionEventObserver(IObserver<CMouseMotionEvent>* observer)
{
    mouse_motion_event_subject.RegisterObserver(observer);
}

void CSystemEventManager::RemoveMouseMotionEventObserver(IObserver<CMouseMotionEvent>* observer)
{
    mouse_motion_event_subject.RemoveObserver(observer);
}

void CSystemEventManager::RegisterKeyboardEventObserver(IObserver<CKeyboardEvent>* observer)
{
    keyboard_event_subject.RegisterObserver(observer);
}

void CSystemEventManager::RemoveKeyboardEventObserver(IObserver<CKeyboardEvent>* observer)
{
    keyboard_event_subject.RemoveObserver(observer);
}

void CSystemEventManager::RegisterEventOwnerInfo(IUIFrame* frame)
{
    frame_info_array.push_back(frame);
}

void CSystemEventManager::RemoveEventOwnerInfo(IUIFrame* frame)
{
}

void CSystemEventManager::RegisterVideoResizeEventObserver(IObserver<CVideoResizeEvent>* observer)
{
    video_resize_event_subject.RegisterObserver(observer);
}

void CSystemEventManager::RemoveVideoResizeEventObserver(IObserver<CVideoResizeEvent>* observer)
{
    video_resize_event_subject.RemoveObserver(observer);
}

#endif // C_SDL_EVENT_MANAGER_H
