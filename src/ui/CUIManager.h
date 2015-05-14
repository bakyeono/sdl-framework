#ifndef C_UI_MANAGER_H
#define C_UI_MANAGER_H

#include "../lib.h"
#include "../event/CSystemEventManager.h"
#include "../ctrl/CExitCtrl.h"
#include "../common/CColorPreset.h"
#include "./frame/CUIFrameSortOption.h"
#include "./frame/IUIFrame.h"

class CUIManager
{
private:
    CUIManager();
    ~CUIManager();

public:
    static CUIManager& Instance();

public:
    void RegisterFrame(IUIFrame* frame);
    void RemoveFrame(IUIFrame* frame);
    void Run();
    void ReserveRefresh();

private:
    void SortFrames();
    void Refresh();
    void UpdateEvent();
    void UnfocusFrame(IUIFrame* frame);

private:
    vector<IUIFrame*> frame_array;
    bool is_to_refresh;
};

#endif // C_UI_MANAGER_H
