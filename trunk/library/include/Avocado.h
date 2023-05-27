#ifndef OOPPROJECT_AVOCADO_H
#define OOPPROJECT_AVOCADO_H

#include "Fruit.h"

class Avocado : public Fruit {
public:
    Avocado(unsigned int x, unsigned int y);
    virtual ~Avocado();
    std::string eaten() override ;
};


#endif //OOPPROJECT_AVOCADO_H
