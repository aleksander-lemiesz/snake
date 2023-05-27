#ifndef OOPPROJECT_HEAD_H
#define OOPPROJECT_HEAD_H


#include "Segment.h"
#include "Fruit.h"

class World;

class Head : public Segment {
private:
    direction headDirection = none;
    World* world;
public:
    Head(unsigned int x, unsigned int y, World *world);
    virtual ~Head();
    bool canEat() const;
    void move() override;
    void turn(direction turnDirection);
    direction getDirection() const;
    std::shared_ptr<Fruit> eat() const;
    bool isOutsideWorld() const;
};


#endif //OOPPROJECT_HEAD_H
