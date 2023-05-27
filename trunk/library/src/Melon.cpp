#include "Melon.h"

Melon::Melon(unsigned int x, unsigned int y) : Fruit(x, y) {

}

std::string Melon::eaten() {
    return "Melon";
}

Melon::~Melon() {

}
