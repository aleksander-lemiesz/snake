#include "Apple.h"

Apple::Apple(unsigned int x, unsigned int y) : Fruit(x, y) {

}

std::string Apple::eaten() {
    return "Apple";
}

Apple::~Apple() {

}
