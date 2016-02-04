#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>

#include "observer.h"

class Observable
{
public:
    Observable();

    void attachObserver(Observer* obs);
    bool isChanged();

protected:
    void setChanged();
    void notifyObservers();
    void discardChanges();

private:
    std::vector<class Observer*> observers;

    bool changed;
};

#endif // OBSERVABLE_H
