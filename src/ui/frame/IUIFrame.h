#ifndef I_UI_FRAME
#define I_UI_FRAME

#include "../../lib.h"
#include "../../common/IObserver.h"
#include "../../event/CMouseButtonEvent.h"
#include "../../event/CVideoResizeEvent.h"

class IUIFrame
    : public IObserver<CMouseButtonEvent>,
      public IObserver<CVideoResizeEvent>
{
public:
    virtual Uint32  GetAccessClock() const = 0;
    virtual bool    HasPos(const CPos& pos) = 0;
    virtual bool    IsOccupyingFocus() const = 0;
    virtual void    Focus() = 0;
    virtual void    Unfocus() = 0;
    virtual bool    IsEnabled() const = 0;
    virtual bool    IsUpdated() const = 0;
    virtual void    Draw() = 0;
};

#endif // I_UI_FRAME
