#ifndef C_UTIL_UTF8_H
#define C_UTIL_UTF8_H

#include "../lib.h"

using namespace std;

class CUTF8Util
{
private:
    explicit CUTF8Util();
    ~CUTF8Util();

public:
    inline static bool   IsASCIICode(Uint8 u8_0);
    inline static int    UTF16(const string& str);
    inline static int    UTF16(Uint8 u8_0, Uint8 u8_1, Uint8 u8_2);
    inline static int    FontCode(Uint8 u8_0, Uint8 u8_1, Uint8 u8_2);
    inline static int    MonoLength(const string& str);
    inline static int    FindNextLinePoint(const string& str, int from, int cols);
    inline static string CutByMonoLength(const string& str, int mono_length);

private:
    static const int font_code_base_ascii;
    static const int font_code_base_hiragana;
    static const int font_code_base_katakana;
    static const int font_code_base_hangul_jamo;
    static const int font_code_base_hangul;
    static const int font_code_base_arrow_char;
};

bool CUTF8Util::IsASCIICode(Uint8 u8_0)
{
    if (u8_0 < 0x80) return true;
    else            return false;
}

int CUTF8Util::UTF16(const string& str)
{
    return UTF16((Uint8)str.c_str()[0], (Uint8)str.c_str()[1], (Uint8)str.c_str()[2]);
}

int CUTF8Util::UTF16(Uint8 u8_0, Uint8 u8_1, Uint8 u8_2)
{
    Uint8 u16_0 = u8_2 - 0xE0;
    Uint8 u16_1 = u8_1 / 4 - 32;
    Uint8 u16_2 = (u8_1 % 4 * 4) + (u8_0 / 16 - 8);
    Uint8 u16_3 = u8_0 % 16;
    int   u16   = u16_0 * 0x1000 + u16_1 * 0x100 + u16_2 * 0x10 + u16_3;
    return u16;
}

int CUTF8Util::FontCode(Uint8 u8_0, Uint8 u8_1, Uint8 u8_2)
{
    int code = UTF16(u8_0, u8_1, u8_2);
    if (0xAC00 <= code && code <= 0xD7A3) return code - 0xAC00 + font_code_base_hangul;
    if (0x3131 <= code && code <= 0x3163) return code - 0x3131 + font_code_base_hangul_jamo;
    if (0x3041 <= code && code <= 0x3093) return code - 0x3041 + font_code_base_hiragana;
    if (0x30A1 <= code && code <= 0x30F6) return code - 0x30A1 + font_code_base_katakana;
    if (0x2190 <= code && code <= 0x2199) return code - 0x2190 + font_code_base_arrow_char;
    return 0;
}

int CUTF8Util::MonoLength(const string& str)
{
    int mono_length = 0;
    for (size_t index = 0; index < str.size(); ++index)
    {
        if (IsASCIICode((Uint8)str[index]))
        {
            ++mono_length;
        }
        else
        {
            mono_length += 2;
            index += 2;
        }
    }
    return mono_length;
}

int CUTF8Util::FindNextLinePoint(const string& str, int from, int cols)
{
    int    mono_length = 0;
    size_t index = from;
    for (; ; )
    {
        if (cols <= mono_length || str.size() <= index)
        {
            return index;
        }
        if (IsASCIICode((Uint8)str[index]))
        {
            if ((Uint8)str[index] == '\n')
            {
                return index + 1;
            }
            mono_length += 1;
            index += 1;
        }
        else
        {
            mono_length += 2;
            index += 3;
        }
    }
    return index;
}

string CUTF8Util::CutByMonoLength(const string& str, int mono_length)
{
    int limit_point = FindNextLinePoint(str, 0, mono_length);
    return str.substr(0, limit_point);
}

#endif // C_UTIL_UTF8_H
