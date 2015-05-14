#ifndef C_UI_TEXT_INPUT_FRAME_H
#define C_UI_TEXT_INPUT_FRAME_H

#include "CUIBaseFrame.h"
#include "../component/CUITitleField.h"
#include "../component/CUITextField.h"
#include "../component/CUIEditField.h"
#include "../component/CUIButton.h"

class CUITextInputFrame
    : public CUIBaseFrame
{
public:
    CUITextInputFrame(const CRect& _rect,
                      const string& title_label = "",
                      const string& message_text = "",
                      const string& edit_label = "",
                      const string& button_label = "",
                      EUIActionType button_action = EUIActionType::none);
    virtual ~CUITextInputFrame();

protected:
    virtual void   DrawComponents();

private:
    CUITitleField  title;
    CUITextField   message;
    CUIEditField   edit;
    CUIButton      button;
};

#endif // C_UI_TEXT_INPUT_FRAME_H
