

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;

    /**
     * @brief Update the observer
     */
    virtual void update() = 0;
};

#endif // OBSERVER_H
