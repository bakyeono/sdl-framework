#ifndef C_POS_H
#define C_POS_H

#include "../lib.h"

class CPos
{
public:
    inline explicit CPos();
    inline explicit CPos(int _x, int _y);
    inline ~CPos();

public:
    inline int  GetX() const;
    inline void SetX(int _x);
    inline int  GetY() const;
    inline void SetY(int _y);
    inline CPos operator + (const CPos& val) const;
    inline CPos operator - (const CPos& val) const;
    inline bool operator == (const CPos& rhs) const;
    inline bool operator < (const CPos& rhs) const;

private:
    int x;
    int y;
};

CPos::CPos()
    : x(0), y(0)
{
}

CPos::CPos(int _x, int _y)
    : x(_x), y(_y)
{
}

CPos::~CPos()
{
}

int CPos::GetX() const
{
    return x;
}

void CPos::SetX(int _x)
{
    x = _x;
}

int CPos::GetY() const
{
    return y;
}

void CPos::SetY(int _y)
{
    y = _y;
}

CPos CPos::operator + (const CPos& val) const
{
    CPos calculated_pos(*this);
    calculated_pos.x += val.x;
    calculated_pos.y += val.y;
    return calculated_pos;
}

CPos CPos::operator - (const CPos& val) const
{
    CPos calculated_pos(*this);
    calculated_pos.x -= val.x;
    calculated_pos.y -= val.y;
    return calculated_pos;
}

bool CPos::operator == (const CPos& rhs) const
{
    if ((x == rhs.x) && (y == rhs.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CPos::operator < (const CPos& rhs) const
{
    if (x < rhs.x)
    {
        return true;
    }
    else if (x == rhs.x)
    {
        return (y < rhs.y);
    }
    else
    {
        return false;
    }
}

#endif // C_POS_H
