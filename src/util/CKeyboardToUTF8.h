#ifndef C_KEYBOARD_TO_UTF8_H
#define C_KEYBOARD_TO_UTF8_H

#include "../lib.h"
#include "./EInputMode.h"
#include "./CUTF8Util.h"

using namespace std;

class CKeyboardToUTF8
{
public:
    explicit CKeyboardToUTF8(EInputMode _input_mode = EInputMode::korean_2pair,
                             bool _is_input_mode_changeable = true,
                             bool _is_number_only = false,
                             bool _is_number_allowed = true,
                             int _cols = -1,
                             const string& _str = "");
    ~CKeyboardToUTF8();

public:
    void           ProcessKey(int keycode);
    const string&  GetString() const;
    void           SetString(const string& str);

private:
    void           K2PScanKey(int keycode);
    void           EQScanKey(int keycode);
    void           NumberScanKey(int keycode);
    void           ChangeInputMode();
    void           Backspace();
    void           CutOverString();
    int            K2PJasoConvAC(int a);
    int            K2PJasoConvCA(int c);
    bool           K2PIsCPlaceable(int a);
    int            K2PCombineCA(int c, int t);
    int            K2PCombineBB(int b, int t);
    string         K2PCombineABC(const int a, const int b, const int c);
    void           K2PDivideCA(int c, int& _c, int& _t);
    void           K2PCombine(const int input_type);

private:
    string        str;
    EInputMode    input_mode;
    bool          is_input_mode_changeable;
    bool          is_number_only;
    bool          is_number_allowed;
    int           cols;
    Uint8*        key_state;
    string        k2p_ch_jaso;
    int           k2p_jaso_a;
    int           k2p_jaso_b;
    int           k2p_jaso_c;
    int           k2p_jaso_t;
    int           k2p_combine_level;
};

#endif // C_KEYBOARD_TO_UTF8_H
