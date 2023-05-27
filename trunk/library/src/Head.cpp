#include <World.h>
#include "Head.h"

direction Head::getDirection() const {
    return headDirection;
}

void Head::turn(direction turnDirection) {
    headDirection = turnDirection;
}

void Head::move() {
    switch (headDirection) {
        case up : ++y;
            break;
        case down : --y;
            break;
        case left : --x;
            break;
        case right : ++x;
            break;
        case none :
        case exitGame :
            break;

    }
}

Head::Head(unsigned int x, unsigned int y, World *world) : Segment(x, y), world(world) {}

bool Head::canEat() const {
    unsigned int X;
    unsigned int Y;
    if (!world->getFruits().empty()) {
        for (int i = 0; i < world->getFruits().size(); ++i) {
            Y = world->getFruits()[i]->getY();
            X = world->getFruits()[i]->getX();
            if (x == X && y == Y) {
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<Fruit> Head::eat() const {
    std::shared_ptr<Fruit> fruit;
    for (int i = 0; i < world->getFruits().size(); ++i) {
        unsigned int Y = world->getFruits()[i]->getY();
        unsigned int X = world->getFruits()[i]->getX();
        if (x == X && y == Y) {
            fruit = world->getFruits()[i];
            world->eraseFruit(i);
        }
    }
    return fruit;
}

bool Head::isOutsideWorld() const {
    return (x < 0 || x >= world->getSize().getWidth()) || y < 0 || y >= world->getSize().getHeight();
}

Head::~Head() {

}



