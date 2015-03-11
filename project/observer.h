#ifndef OBSERVER_H
#define OBSERVER_H

class Observable;

class Observer
{
public:
    Observer();
    void update(Observable* obs);
};

#endif // OBSERVER_H
