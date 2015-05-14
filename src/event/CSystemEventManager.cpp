#include "./CSystemEventManager.h"

CSystemEventManager::CSystemEventManager()
{
    frame_info_array.reserve(40);
}

CSystemEventManager::~CSystemEventManager()
{
}

void CSystemEventManager::Update()
{
    SDL_WaitEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        CExitCtrl::CallExit();
        break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        mouse_button_event.Set(event);
        FindMouseButtonEventOwner();
        mouse_button_event_subject.NotifyObservers(&mouse_button_event);
        break;

    case SDL_MOUSEMOTION:
        mouse_motion_event.Set(event);
        mouse_motion_event_subject.NotifyObservers(&mouse_motion_event);
        break;

    case SDL_KEYDOWN:
    case SDL_KEYUP:
        keyboard_event.Set(event);
        keyboard_event_subject.NotifyObservers(&keyboard_event);
        break;

    case SDL_VIDEORESIZE:
        CScreenCtrl::Instance().Resize(event.resize.w, event.resize.h);
        video_resize_event.Set(event);
        video_resize_event_subject.NotifyObservers(&video_resize_event);
        break;

    default:
        break;
    }
}

void CSystemEventManager::FindMouseButtonEventOwner()
{
    sort(frame_info_array.begin(), frame_info_array.end(), CUIFrameSortOption());
    for (auto it = frame_info_array.rbegin(); it != frame_info_array.rend(); ++it)
    {
        if ((*it)->IsOccupyingFocus())
        {
            mouse_button_event.SetOwner(*it);
            break;
        }
        else if ((*it)->HasPos(mouse_button_event.GetPos()))
        {
            mouse_button_event.SetOwner(*it);
            break;
        }
    }
}
