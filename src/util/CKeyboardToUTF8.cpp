#include "CKeyboardToUTF8.h"

//한국어 2벌식 조합 입력기 설명
//제작 박연오
//
//-- 변수 설명
//string str           -- 입력된 문장
//int    jaso_a        -- 현재 글자의 초성
//int    jaso_b        -- 현재 글자의 중성
//int    jaso_c        -- 현재 글자의 종성
//int    combine_level -- 현재 글자의 조합 단계를 나타냄
//                     -- 0:초기상태    1:초성      2:초+중성    3:중성수정
//                     -- 4:초+중+종성  5:종성수정  6:중성만 입력된 비정상적 상태
//
//-- combine_level과 키 입력에 따른 처리
//case (combine_level == 0) :
//자음 입력(ㄱ) : str = \0   | combine = ㄱ | combine_level = 1
//모음 입력(ㅗ) : str = \0   | combine = ㅗ | combine_level = 6
//기타 입력(1 ) : str = 1    | combine = \0 | combine_level = 0
//backspace     : str = \0   | combine = \0 | combine_level = 0
//
//case (combine_level == 1) :
//자음 입력(ㄴ) : str = ㄱ   | combine = ㄴ | combine_level = 1
//모음 입력(ㅗ) : str = \0   | combine = 고 | combine_level = 2
//기타 입력(1)  : str = ㄱ1  | combine = \0 | combine_level = 0
//backspace     : str = \0   | combine = \0 | combine_level = 0
//
//case (combine_level == 2) :
//자음 입력(ㄹ) : str = \0   | combine = 골 | combine_level = 4
//자음 입력(ㅃ) : str = 고   | combine = ㅃ | combine_level = 1
//모음 입력(ㅜ) : str = 고   | combine = ㅜ | combine_level = 6
//모음 입력(ㅏ) : str = \0   | combine = 과 | combine_level = 3
//기타 입력(1)  : str = 가1  | combine = \0 | combine_level = 0
//backspace     : str = \0   | combine = ㄱ | combine_level = 1
//
//case (combine_level == 3) :
//자음 입력(ㄹ) : str = \0   | combine = 괄 | combine_level = 4
//자음 입력(ㅃ) : str = 과   | combine = ㅃ | combine_level = 1
//모음 입력(ㅓ) : str = 과   | combine = ㅓ | combine_level = 6
//기타 입력(1)  : str = 과1  | combine = \0 | combine_level = 0
//backspace     : str = \0   | combine = 고 | combine_level = 2
//
//case (combine_level == 4) :
//자음 입력(ㄷ) : str = 괄   | combine = ㄷ | combine_level = 1
//자음 입력(ㅁ) : str = \0   | combine = 괆 | combine_level = 5
//자음 입력(ㅃ) : str = 괄   | combine = ㅃ | combine_level = 1
//모음 입력(ㅓ) : str = 과   | combine = 러 | combine_level = 2
//기타 입력(1)  : str = 괄1  | combine = \0 | combine_level = 0
//backspace     : str = \0   | combine = 과 | combine_level = 3 or 2
//
//case (combine_level == 5) :
//자음 입력(ㄷ) : str = 괆   | combine = ㄷ | combine_level = 1
//모음 입력(ㅓ) : str = 괄   | combine = 머 | combine_level = 2
//기타 입력(1)  : str = 괆1  | combine = \0 | combine_level = 0
//backspace     : str = \0   | combine = 괄 | combine_level = 4
//
//case (combine_level == 6) :
//자음 입력(ㄱ) : str = ㅏ   | combine = ㄱ | combine_level = 1
//모음 입력(ㅓ) : str = ㅏ   | combine = ㅓ | combine_level = 6
//기타 입력(1)  : str = ㅏ1  | combine = \0 | combine_level = 0
//backspace     : str = \0   | combine = \0 | combine_level = 0

CKeyboardToUTF8::CKeyboardToUTF8(EInputMode _input_mode,
                                 bool _is_input_mode_changeable,
                                 bool _is_number_only,
                                 bool _is_number_allowed,
                                 int _cols,
                                 const string& _str)
    :
    str(_str),
    input_mode(_input_mode),
    is_input_mode_changeable(_is_input_mode_changeable),
    is_number_only(_is_number_only),
    is_number_allowed(_is_number_allowed),
    cols(_cols),
    k2p_jaso_a(0),
    k2p_jaso_b(0),
    k2p_jaso_c(0),
    k2p_jaso_t(0),
    k2p_combine_level(0)
{
    CutOverString();
}

CKeyboardToUTF8::~CKeyboardToUTF8()
{
}

void CKeyboardToUTF8::ProcessKey(int keycode) {
    if      (keycode == SDLK_TAB)    ChangeInputMode();
    else if (keycode == SDLK_ESCAPE) ;
    else if (keycode == SDLK_RETURN) ;
    else
    {
        if      (is_number_only) NumberScanKey(keycode);
        else if (input_mode == EInputMode::korean_2pair) K2PScanKey(keycode);
        else if (input_mode == EInputMode::english_qwerty) EQScanKey(keycode);
        else ;
    }
}

const string& CKeyboardToUTF8::GetString() const {
    return str;
}

void CKeyboardToUTF8::SetString(const string& _str) {
    str = _str;
    CutOverString();
    k2p_combine_level = 0;
    k2p_ch_jaso = "";
}

void CKeyboardToUTF8::K2PScanKey(int keycode)
{
    switch (keycode)
    {
    case SDLK_SPACE:
        k2p_ch_jaso   = " ";
        K2PCombine(2);
        break;
    case SDLK_a:
        k2p_jaso_t    = 6;
        k2p_ch_jaso   = "ㅁ";
        K2PCombine(0);
        break;
    case SDLK_c:
        k2p_jaso_t    = 14;
        k2p_ch_jaso   = "ㅊ";
        K2PCombine(0);
        break;
    case SDLK_d:
        k2p_jaso_t    = 11;
        k2p_ch_jaso   = "ㅇ";
        K2PCombine(0);
        break;
    case SDLK_e:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            k2p_jaso_t    = 4;
            k2p_ch_jaso   = "ㄸ";
        }
        else
        {
            k2p_jaso_t    = 3;
            k2p_ch_jaso   = "ㄷ";
        }
        K2PCombine(0);
        break;
    case SDLK_f:
        k2p_jaso_t    = 5;
        k2p_ch_jaso   = "ㄹ";
        K2PCombine(0);
        break;
    case SDLK_g:
        k2p_jaso_t    = 18;
        k2p_ch_jaso   = "ㅎ";
        K2PCombine(0);
        break;
    case SDLK_q:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            k2p_jaso_t    = 8;
            k2p_ch_jaso   = "ㅃ";
        }
        else
        {
            k2p_jaso_t    = 7;
            k2p_ch_jaso   = "ㅂ";
        }
        K2PCombine(0);
        break;
    case SDLK_r:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            k2p_jaso_t    = 1;
            k2p_ch_jaso   = "ㄲ";
        }
        else
        {
            k2p_jaso_t    = 0;
            k2p_ch_jaso   = "ㄱ";
        }
        K2PCombine(0);
        break;
    case SDLK_s:
        k2p_jaso_t    = 2;
        k2p_ch_jaso   = "ㄴ";
        K2PCombine(0);
        break;
    case SDLK_t:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            k2p_jaso_t    = 10;
            k2p_ch_jaso   = "ㅆ";
        }
        else
        {
            k2p_jaso_t    = 9;
            k2p_ch_jaso   = "ㅅ";
        }
        K2PCombine(0);
        break;
    case SDLK_v:
        k2p_jaso_t    = 17;
        k2p_ch_jaso   = "ㅍ";
        K2PCombine(0);
        break;
    case SDLK_w:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            k2p_jaso_t    = 13;
            k2p_ch_jaso   = "ㅉ";
        }
        else
        {
            k2p_jaso_t    = 12;
            k2p_ch_jaso   = "ㅈ";
        }
        K2PCombine(0);
        break;
    case SDLK_x:
        k2p_jaso_t    = 16;
        k2p_ch_jaso   = "ㅌ";
        K2PCombine(0);
        break;
    case SDLK_z:
        k2p_jaso_t    = 15;
        k2p_ch_jaso   = "ㅋ";
        K2PCombine(0);
        break;

    case SDLK_b:
        k2p_jaso_t    = 17;
        k2p_ch_jaso   = "ㅠ";
        K2PCombine(1);
        break;
    case SDLK_h:
        k2p_jaso_t    = 8;
        k2p_ch_jaso   = "ㅗ";
        K2PCombine(1);
        break;
    case SDLK_i:
        k2p_jaso_t    = 2;
        k2p_ch_jaso   = "ㅑ";
        K2PCombine(1);
        break;
    case SDLK_j:
        k2p_jaso_t    = 4;
        k2p_ch_jaso   = "ㅓ";
        K2PCombine(1);
        break;
    case SDLK_k:
        k2p_jaso_t    = 0;
        k2p_ch_jaso   = "ㅏ";
        K2PCombine(1);
        break;
    case SDLK_l:
        k2p_jaso_t    = 20;
        k2p_ch_jaso   = "ㅣ";
        K2PCombine(1);
        break;
    case SDLK_m:
        k2p_jaso_t    = 18;
        k2p_ch_jaso   = "ㅡ";
        K2PCombine(1);
        break;
    case SDLK_n:
        k2p_jaso_t    = 13;
        k2p_ch_jaso   = "ㅜ";
        K2PCombine(1);
        break;
    case SDLK_o:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            k2p_jaso_t    = 3;
            k2p_ch_jaso   = "ㅒ";
        }
        else
        {
            k2p_jaso_t    = 1;
            k2p_ch_jaso   = "ㅐ";
        }
        K2PCombine(1);
        break;
    case SDLK_p:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            k2p_jaso_t    = 7;
            k2p_ch_jaso   = "ㅖ";
        }
        else
        {
            k2p_jaso_t    = 5;
            k2p_ch_jaso   = "ㅔ";
        }
        K2PCombine(1);
        break;
    case SDLK_u:
        k2p_jaso_t    = 6;
        k2p_ch_jaso   = "ㅕ";
        K2PCombine(1);
        break;
    case SDLK_y:
        k2p_jaso_t    = 12;
        k2p_ch_jaso   = "ㅛ";
        K2PCombine(1);
        break;
    case SDLK_BACKSPACE:
        K2PCombine(3);
        break;
    default:
        break;
    }
    if (is_number_allowed) {
        switch (keycode) {
        case SDLK_0:
            k2p_ch_jaso = "0";
            K2PCombine(2);
            break;
        case SDLK_1:
            k2p_ch_jaso = "1";
            K2PCombine(2);
            break;
        case SDLK_2:
            k2p_ch_jaso = "2";
            K2PCombine(2);
            break;
        case SDLK_3:
            k2p_ch_jaso = "3";
            K2PCombine(2);
            break;
        case SDLK_4:
            k2p_ch_jaso = "4";
            K2PCombine(2);
            break;
        case SDLK_5:
            k2p_ch_jaso = "5";
            K2PCombine(2);
            break;
        case SDLK_6:
            k2p_ch_jaso = "6";
            K2PCombine(2);
            break;
        case SDLK_7:
            k2p_ch_jaso = "7";
            K2PCombine(2);
            break;
        case SDLK_8:
            k2p_ch_jaso = "8";
            K2PCombine(2);
            break;
        case SDLK_9:
            k2p_ch_jaso = "9";
            K2PCombine(2);
            break;
        default:
            break;
        }
    }
    CutOverString();
}

void CKeyboardToUTF8::EQScanKey(int keycode)
{
    switch (keycode)
    {
    case SDLK_SPACE:
        str += " ";
        break;
    case SDLK_a:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "A";
        }
        else
        {
            str += "a";
        }
        break;
    case SDLK_b:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "B";
        }
        else
        {
            str += "b";
        }
        break;
    case SDLK_c:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "C";
        }
        else
        {
            str += "c";
        }
        break;
    case SDLK_d:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "D";
        }
        else
        {
            str += "d";
        }
        break;
    case SDLK_e:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "E";
        }
        else
        {
            str += "e";
        }
        break;
    case SDLK_f:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "F";
        }
        else
        {
            str += "f";
        }
        break;
    case SDLK_g:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "G";
        }
        else
        {
            str += "g";
        }
        break;
    case SDLK_h:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "H";
        }
        else
        {
            str += "h";
        }
        break;
    case SDLK_i:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "I";
        }
        else
        {
            str += "i";
        }
        break;
    case SDLK_j:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "J";
        }
        else
        {
            str += "j";
        }
        break;
    case SDLK_k:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "K";
        }
        else
        {
            str += "k";
        }
        break;
    case SDLK_l:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "L";
        }
        else
        {
            str += "l";
        }
        break;
    case SDLK_m:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "M";
        }
        else
        {
            str += "m";
        }
        break;
    case SDLK_n:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "N";
        }
        else
        {
            str += "n";
        }
        break;
    case SDLK_o:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "O";
        }
        else
        {
            str += "o";
        }
        break;
    case SDLK_p:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "P";
        }
        else
        {
            str += "p";
        }
        break;
    case SDLK_q:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "Q";
        }
        else
        {
            str += "q";
        }
        break;
    case SDLK_r:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "R";
        }
        else
        {
            str += "r";
        }
        break;
    case SDLK_s:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "S";
        }
        else
        {
            str += "s";
        }
        break;
    case SDLK_t:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "T";
        }
        else
        {
            str += "t";
        }
        break;
    case SDLK_u:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "U";
        }
        else
        {
            str += "u";
        }
        break;
    case SDLK_v:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "V";
        }
        else
        {
            str += "v";
        }
        break;
    case SDLK_w:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "W";
        }
        else
        {
            str += "w";
        }
        break;
    case SDLK_x:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "X";
        }
        else
        {
            str += "x";
        }
        break;
    case SDLK_y:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "Y";
        }
        else
        {
            str += "y";
        }
        break;
    case SDLK_z:
        key_state = SDL_GetKeyState(NULL);
        if (key_state[SDLK_LSHIFT] || key_state[SDLK_RSHIFT])
        {
            str += "Z";
        }
        else
        {
            str += "z";
        }
        break;
    case SDLK_BACKSPACE:
        Backspace();
        break;
    default:
        break;
    }
    if (is_number_allowed)
    {
        switch(keycode) {
        case SDLK_0:
            str += "0";
            break;
        case SDLK_1:
            str += "1";
            break;
        case SDLK_2:
            str += "2";
            break;
        case SDLK_3:
            str += "3";
            break;
        case SDLK_4:
            str += "4";
            break;
        case SDLK_5:
            str += "5";
            break;
        case SDLK_6:
            str += "6";
            break;
        case SDLK_7:
            str += "7";
            break;
        case SDLK_8:
            str += "8";
            break;
        case SDLK_9:
            str += "9";
            break;
        default:
            break;
        }
    }
    CutOverString();
}

void CKeyboardToUTF8::NumberScanKey(int keycode) {
    switch (keycode)
    {
    case SDLK_0:
        str += "0";
        break;
    case SDLK_1:
        str += "1";
        break;
    case SDLK_2:
        str += "2";
        break;
    case SDLK_3:
        str += "3";
        break;
    case SDLK_4:
        str += "4";
        break;
    case SDLK_5:
        str += "5";
        break;
    case SDLK_6:
        str += "6";
        break;
    case SDLK_7:
        str += "7";
        break;
    case SDLK_8:
        str += "8";
        break;
    case SDLK_9:
        str += "9";
        break;
    case SDLK_BACKSPACE:
        Backspace();
        break;
    default:
        break;
    }
    CutOverString();
}

void CKeyboardToUTF8::ChangeInputMode()
{
    if (!is_input_mode_changeable) return;
    if (input_mode == EInputMode::korean_2pair)
    {
        if (k2p_combine_level)
        {
            k2p_combine_level = 0;
        }
        input_mode = EInputMode::english_qwerty;
    }
    else
    {
        input_mode = EInputMode::korean_2pair;
    }
}

void CKeyboardToUTF8::Backspace()
{
    int at = str.length();
    if (at <= 0)
    {
        return;
    }
    else if (at <= 2)
    {
        str.erase(at-1, 1);
    }
    else
    {
        if (0xE0 <= (unsigned char)str[at-3] && (unsigned char)str[at-3] <= 0xEF)
        {
            str.erase(at-3, 3);
        }
        else
        {
            str.erase(at-1, 1);
        }
    }
}

void CKeyboardToUTF8::CutOverString() {
    if (cols == -1) return;
    str = CUTF8Util::CutByMonoLength(str, cols);
}

void CKeyboardToUTF8::K2PCombine(const int input_type)
{
    // input_type : 0 - 자음 입력
    //              1 - 모음 입력
    //              2 - 기타 입력 (숫자 등)
    //              3 - backspace
    if (input_type == 0 && k2p_combine_level == 0)
    {
        k2p_jaso_a        = k2p_jaso_t;
        str               += k2p_ch_jaso;
        k2p_combine_level = 1;
    }
    else if (input_type == 0 && k2p_combine_level == 1)
    {
        k2p_jaso_a        = k2p_jaso_t;
        str               += k2p_ch_jaso;
        k2p_combine_level = 1;
    }
    else if (input_type == 0 && k2p_combine_level == 2)
    {
        if (K2PIsCPlaceable(k2p_jaso_t))
        {
            k2p_jaso_c        = K2PJasoConvAC(k2p_jaso_t);
            Backspace();
            str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, k2p_jaso_c);
            k2p_combine_level = 4;
        }
        else
        {
            k2p_jaso_a        = k2p_jaso_t;
            str               += k2p_ch_jaso;
            k2p_combine_level = 1;
        }
    }
    else if (input_type == 0 && k2p_combine_level == 3)
    {
        if (K2PIsCPlaceable(k2p_jaso_t))
        {
            k2p_jaso_c        = K2PJasoConvAC(k2p_jaso_t);
            Backspace();
            str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, k2p_jaso_c);
            k2p_combine_level = 4;
        }
        else
        {
            k2p_jaso_a        = k2p_jaso_t;
            str               += k2p_ch_jaso;
            k2p_combine_level = 1;
        }
    }
    else if (input_type == 0 && k2p_combine_level == 4)
    {
        int temp = K2PCombineCA(k2p_jaso_c, k2p_jaso_t);
        if (temp == -1)
        {
            k2p_jaso_a        = k2p_jaso_t;
            str               += k2p_ch_jaso;
            k2p_combine_level = 1;
        }
        else
        {
            k2p_jaso_c        = temp;
            Backspace();
            str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, k2p_jaso_c);
            k2p_combine_level = 5;
        }
    }
    else if (input_type == 0 && k2p_combine_level == 5)
    {
        k2p_jaso_a        = k2p_jaso_t;
        str               += k2p_ch_jaso;
        k2p_combine_level = 1;
    }
    else if (input_type == 0 && k2p_combine_level == 6)
    {
        k2p_jaso_a        = k2p_jaso_t;
        str               += k2p_ch_jaso;
        k2p_combine_level = 1;
    }
    else if (input_type == 1 && k2p_combine_level == 0)
    {
        k2p_jaso_b        = k2p_jaso_t;
        str               += k2p_ch_jaso;
        k2p_combine_level = 6;
    }
    else if (input_type == 1 && k2p_combine_level == 1)
    {
        k2p_jaso_b        = k2p_jaso_t;
        Backspace();
        str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, 0);
        k2p_combine_level = 2;
    }
    else if (input_type == 1 && k2p_combine_level == 2)
    {
        int temp = K2PCombineBB(k2p_jaso_b, k2p_jaso_t);
        if (temp == -1)
        {
            k2p_jaso_b        = k2p_jaso_t;
            str               += k2p_ch_jaso;
            k2p_combine_level = 6;
        }
        else
        {
            k2p_jaso_b        = temp;
            Backspace();
            str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, 0);
            k2p_combine_level = 3;
        }
    }
    else if (input_type == 1 && k2p_combine_level == 3)
    {
        k2p_jaso_b        = k2p_jaso_t;
        str               += k2p_ch_jaso;
        k2p_combine_level = 6;
    }
    else if (input_type == 1 && k2p_combine_level == 4)
    {
        Backspace();
        str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, 0);
        k2p_jaso_a        = K2PJasoConvCA(k2p_jaso_c);
        k2p_jaso_b        = k2p_jaso_t;
        str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, 0);
        k2p_combine_level = 2;
    }
    else if (input_type == 1 && k2p_combine_level == 5)
    {
        int temp;
        K2PDivideCA(k2p_jaso_c, k2p_jaso_c, temp);
        Backspace();
        str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, k2p_jaso_c);
        k2p_jaso_a        = temp;
        k2p_jaso_b        = k2p_jaso_t;
        str               += K2PCombineABC(k2p_jaso_a, k2p_jaso_b, 0);
        k2p_combine_level = 2;
    }
    else if (input_type == 1 && k2p_combine_level == 6)
    {
        k2p_jaso_b        = k2p_jaso_t;
        str               += k2p_ch_jaso;
        k2p_combine_level = 6;
    }
    else if (input_type == 2 && k2p_combine_level == 0)
    {
        str               += k2p_ch_jaso;
        k2p_combine_level = 0;
    }
    else if (input_type == 2 && k2p_combine_level != 0)
    {
        str               += k2p_ch_jaso;
        k2p_combine_level = 0;
    }
    else if (input_type == 3 && k2p_combine_level == 0)
    {
        Backspace();
    }
    else if (input_type == 3 && k2p_combine_level != 0)
    {
        Backspace();
        k2p_combine_level = 0;
    }
    else
    {
        ;
    }
}

string CKeyboardToUTF8::K2PCombineABC(const int a, const int b, const int c)
{
    int k2p_ch_combining = 0xAC00 + 21*28*a + 28*b + c;
    unsigned char x0, x1, x2, x3;
    unsigned char x80, x81, x82;
    x0 = k2p_ch_combining / 0x1000;
    x1 = k2p_ch_combining / 0x100 % 0x10;
    x2 = k2p_ch_combining / 0x10 % 0x10;
    x3 = k2p_ch_combining % 0x10;
    x80 = 0xE0 + x0;
    x81 = 0x80 + x1*4 + x2/4;
    x82 = 0x80 + x2%4*16 + x3;
    string utf8;
    utf8.push_back(x80);
    utf8.push_back(x81);
    utf8.push_back(x82);
    return utf8;
}

int CKeyboardToUTF8::K2PJasoConvAC(int a)
{
    if      (a ==  0) return  1;
    else if (a ==  1) return  2;
    else if (a ==  2) return  4;
    else if (a ==  3) return  7;
    else if (a ==  5) return  8;
    else if (a ==  6) return 16;
    else if (a ==  7) return 17;
    else if (a ==  9) return 19;
    else if (a == 10) return 20;
    else if (a == 11) return 21;
    else if (a == 12) return 22;
    else if (a == 14) return 23;
    else if (a == 15) return 24;
    else if (a == 16) return 25;
    else if (a == 17) return 26;
    else if (a == 18) return 27;
    else              return  0;
}

int CKeyboardToUTF8::K2PJasoConvCA(int c)
{
    if      (c ==  1) return  0;
    else if (c ==  2) return  1;
    else if (c ==  4) return  2;
    else if (c ==  7) return  3;
    else if (c ==  8) return  5;
    else if (c == 16) return  6;
    else if (c == 17) return  7;
    else if (c == 19) return  9;
    else if (c == 20) return 10;
    else if (c == 21) return 11;
    else if (c == 22) return 12;
    else if (c == 23) return 14;
    else if (c == 24) return 15;
    else if (c == 25) return 16;
    else if (c == 26) return 17;
    else if (c == 27) return 18;
    else              return  0;
}

bool CKeyboardToUTF8::K2PIsCPlaceable(int a)
{
    if      (a ==  1) return false;
    else if (a ==  4) return false;
    else if (a ==  8) return false;
    else if (a == 13) return false;
    else              return true;
}

int CKeyboardToUTF8::K2PCombineCA(int c, int t)
{
    if      (c ==  1 && t ==  9) return  3;  // ㄳ
    else if (c ==  4 && t == 12) return  5;  // ㄵ
    else if (c ==  4 && t == 18) return  6;  // ㄶ
    else if (c ==  8 && t ==  0) return  9;  // ㄺ
    else if (c ==  8 && t ==  6) return 10;  // ㄻ
    else if (c ==  8 && t ==  7) return 11;  // ㄼ
    else if (c ==  8 && t ==  9) return 12;  // ㄽ
    else if (c ==  8 && t == 16) return 13;  // ㄾ
    else if (c ==  8 && t == 17) return 14;  // ㄿ
    else if (c ==  8 && t == 18) return 15;  // ㅀ
    else if (c == 17 && t ==  9) return 18;  // ㅄ
    else                         return -1;
}

int CKeyboardToUTF8::K2PCombineBB(int b, int t)
{
    if      (b ==  8 && t ==  0) return  9;  // ㅘ
    else if (b ==  8 && t ==  1) return 10;  // ㅙ
    else if (b ==  8 && t == 20) return 11;  // ㅚ
    else if (b == 13 && t ==  4) return 14;  // ㅝ
    else if (b == 13 && t ==  5) return 15;  // ㅞ
    else if (b == 13 && t == 20) return 16;  // ㅟ
    else if (b == 18 && t == 20) return 19;  // ㅢ
    else                         return -1;
}

void CKeyboardToUTF8::K2PDivideCA(int c, int& _c, int& _t)
{
    if      (c ==  3)
    {
        _c =  1;
        _t =  9;
    }
    else if (c ==  5)
    {
        _c =  4;
        _t = 12;
    }
    else if (c ==  6)
    {
        _c =  4;
        _t = 18;
    }
    else if (c ==  9)
    {
        _c =  8;
        _t =  0;
    }
    else if (c == 10)
    {
        _c =  8;
        _t =  6;
    }
    else if (c == 11)
    {
        _c =  8;
        _t =  7;
    }
    else if (c == 12)
    {
        _c =  8;
        _t =  9;
    }
    else if (c == 13)
    {
        _c =  8;
        _t = 16;
    }
    else if (c == 14)
    {
        _c =  8;
        _t = 17;
    }
    else if (c == 15)
    {
        _c =  8;
        _t = 18;
    }
    else if (c == 18)
    {
        _c = 17;
        _t =  9;
    }
    else
    {
        ;
    }
}
