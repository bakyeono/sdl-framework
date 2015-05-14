#ifndef C_RAND_H
#define C_RAND_H

#include "../lib.h"

using namespace std;

class CRand
{
private:
    CRand();
    ~CRand();

public:
    static inline unsigned long int Roll();
    static inline unsigned long int Roll(int die, int add = 0);

private:
    inline void Init();

private:
    unsigned long int rand_state[16];
    unsigned long int rand_index;
};

void CRand::Init()
{
    srand(time(NULL));
    for(int i = 0; i<16; ++i)
    {
        rand_state[i] = rand();
    }
    rand_index = 0;
}

unsigned long int CRand::Roll()
{
    static CRand instance;
    unsigned long int a, b, c, d;
    a  = instance.rand_state[instance.rand_index];
    c  = instance.rand_state[(instance.rand_index+13)&15];
    b  = a^c^(a<<16)^(c<<15);
    c  = instance.rand_state[(instance.rand_index+9)&15];
    c ^= (c>>11);
    a  = instance.rand_state[instance.rand_index] = b^c;
    d  = a^((a<<5)&0xDA442D20UL);
    instance.rand_index = (instance.rand_index + 15)&15;
    a  = instance.rand_state[instance.rand_index];
    instance.rand_state[instance.rand_index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
    return instance.rand_state[instance.rand_index];
}

unsigned long int CRand::Roll(int die, int add)
{
    return Roll() % die + add;
}

#endif // C_RAND_H
