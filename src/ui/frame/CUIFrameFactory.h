#ifndef C_UI_FRAME_FACTORY_H
#define C_UI_FRAME_FACTORY_H

#include "EUIFrameType.h"
#include "CUIBaseFrame.h"
#include "CUIMessageBoxFrame.h"
#include "CUITextInputFrame.h"

class CUIFrameFactory
{
public:
    static CUIBaseFrame* Create(EUIFrameType frame_type, CPos pos);

private:
    CUIFrameFactory();
    ~CUIFrameFactory();
};

#endif // C_UI_FRAME_FACTORY_H
