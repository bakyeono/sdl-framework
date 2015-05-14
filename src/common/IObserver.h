#ifndef I_OBSERVER_H
#define I_OBSERVER_H

#include "../lib.h"

template <typename T>
class IObserver
{
public:
    virtual void OnNotified(T* object) = 0;
};

#endif // I_OBSERVER_H
