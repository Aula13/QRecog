#ifndef OBSERVER_H
#define OBSERVER_H

class Observable;

class Observer
{
public:
    Observer();
    virtual void update(Observable* obs) = 0;
};

#endif // OBSERVER_H
