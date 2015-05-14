#include "./CUIManager.h"

CUIManager::CUIManager()
    : is_to_refresh(true)
{
    frame_array.reserve(40);
}

CUIManager::~CUIManager()
{
}

CUIManager& CUIManager::Instance()
{
    static CUIManager instance;
    return instance;
}

void CUIManager::RegisterFrame(IUIFrame* frame)
{
    frame_array.push_back(frame);
}

void CUIManager::RemoveFrame(IUIFrame* frame)
{
}

void CUIManager::Run()
{
    while (!CExitCtrl::IsExitCalled())
    {
        UpdateEvent();
        SortFrames();
        Refresh();
    }
}

void CUIManager::SortFrames()
{
    sort(frame_array.begin(), frame_array.end(), CUIFrameSortOption());
    for_each(frame_array.begin(), frame_array.end(),
             mem_fun(&IUIFrame::Unfocus));
    frame_array[frame_array.size()-1]->Focus();
}

void CUIManager::Refresh()
{
    if (!is_to_refresh) return;
    CScreenCtrl::Instance().ClearBackground(CColorPreset::ui_background.GetScreenColor());
    for_each(frame_array.begin(), frame_array.end(),
             mem_fun(&IUIFrame::Draw));
    CScreenCtrl::Instance().Refresh();
    is_to_refresh = false;
}

void CUIManager::UpdateEvent()
{
    CSystemEventManager::Instance().Update();
}

void CUIManager::ReserveRefresh()
{
    is_to_refresh = true;
}
