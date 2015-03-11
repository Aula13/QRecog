#include "observable.h"

Observable::Observable()
{
}

void Observable::attachObserver(Observer *obs)
{
    observers.push_back(obs);
}

void Observable::setChanged() {
    changed=true;
}

bool Observable::isChanged()
{
    return changed;
}

void Observable::discardChanges()
{
    changed=false;
}

void Observable::notifyObservers()
{
    for (unsigned int i = 0; i < observers.size(); i++)
        observers[i]->update(this);
    changed=false;
}

