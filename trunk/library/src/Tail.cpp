#include <iostream>
#include "Tail.h"
#include "Snake.h"


Tail::Tail(unsigned int x, unsigned int y, unsigned int index, Snake *snake) : Segment(x, y), snake(snake), index(index) {}

void Tail::move() {
        unsigned int X;
        unsigned int Y;
        if (index != 0) {
            X = snake->getBody()[index - 1]->getX();
            Y = snake->getBody()[index - 1]->getY();
        } else {
            X = snake->getHead().getX();
            Y = snake->getHead().getY();
        }
        x = X;
        y = Y;
}

unsigned int Tail::getIndex() const {
    return index;
}

Tail::~Tail() {

}
