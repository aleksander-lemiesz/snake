#include "Avocado.h"

Avocado::Avocado(unsigned int x, unsigned int y) : Fruit(x, y) {

}

std::string Avocado::eaten() {
    return "Avocado";
}

Avocado::~Avocado() {

}
