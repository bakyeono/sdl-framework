#ifndef C_SUBJECT_H
#define C_SUBJECT_H

#include "../lib.h"
#include "./IObserver.h"

using namespace std;

template <typename T>
class CSubject
{
public:
    explicit CSubject();
    virtual ~CSubject();

public:
    void RegisterObserver(IObserver<T>* observer);
    void RemoveObserver(IObserver<T>* observer);
    void NotifyObservers(T* object);

private:
    list<IObserver<T>*> observer_list;
};

template <typename T>
CSubject<T>::CSubject()
{
}

template <typename T>
CSubject<T>::~CSubject()
{
}

template <typename T>
void CSubject<T>::RegisterObserver(IObserver<T>* observer)
{
    observer_list.push_back(observer);
}

template <typename T>
void CSubject<T>::RemoveObserver(IObserver<T>* observer)
{
}

template <typename T>
void CSubject<T>::NotifyObservers(T* object)
{
    for (auto it = observer_list.begin(); it != observer_list.end(); ++it)
    {
        (*it)->OnNotified(object);
    }
}

#endif // C_SUBJECT_H
