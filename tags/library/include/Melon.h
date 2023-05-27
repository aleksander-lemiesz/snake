#ifndef OOPPROJECT_MELON_H
#define OOPPROJECT_MELON_H

#include "Fruit.h"

class Melon : public Fruit{
public:
    Melon(unsigned int x, unsigned int y);
    virtual ~Melon();
    std::string eaten() override ;
};


#endif //OOPPROJECT_MELON_H
