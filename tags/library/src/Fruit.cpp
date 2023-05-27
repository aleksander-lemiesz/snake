#include "Fruit.h"

unsigned int Fruit::getX() const {
    return x;
}

unsigned int Fruit::getY() const {
    return y;
}

Fruit::Fruit(unsigned int x, unsigned int y) : x(x), y(y) {}

Fruit::~Fruit() {

}
