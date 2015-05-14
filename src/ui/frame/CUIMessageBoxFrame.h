#ifndef C_UI_MESSAGE_BOX_FRAME_H
#define C_UI_MESSAGE_BOX_FRAME_H

#include "CUIBaseFrame.h"
#include "../component/CUITitleField.h"
#include "../component/CUITextField.h"
#include "../component/CUIButton.h"
#include "../action/EUIActionType.h"

class CUIMessageBoxFrame
    : public CUIBaseFrame
{
public:
    CUIMessageBoxFrame(const CRect& _rect,
                       const string& title_label = "",
                       const string& message_text = "",
                       const string& button1_label = "",
                       EUIActionType button1_action = EUIActionType::none,
                       const string& button2_label = "",
                       EUIActionType button2_action = EUIActionType::none,
                       const string& button3_label = "",
                       EUIActionType button3_action = EUIActionType::none,
                       const string& button4_label = "",
                       EUIActionType button4_action = EUIActionType::none);
    virtual ~CUIMessageBoxFrame();

protected:
    virtual void   DrawComponents();

private:
    CUITitleField  title;
    CUITextField   message;
    CUIButton      button1;
    CUIButton      button2;
    CUIButton      button3;
    CUIButton      button4;
};

#endif // C_UI_MESSAGE_BOX_FRAME_H
