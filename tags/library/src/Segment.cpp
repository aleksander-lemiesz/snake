#include "Segment.h"

unsigned int Segment::getX() const {
    return x;
}

unsigned int Segment::getY() const {
    return y;
}

Segment::Segment(unsigned int x, unsigned int y) : x(x), y(y) {}

Segment::~Segment() {

}




