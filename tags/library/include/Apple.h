#ifndef OOPPROJECT_APPLE_H
#define OOPPROJECT_APPLE_H

#include "Fruit.h"

class Apple : public Fruit {
public:
    Apple(unsigned int x, unsigned int y);
    virtual ~Apple();
    std::string eaten() override ;
};


#endif //OOPPROJECT_APPLE_H
