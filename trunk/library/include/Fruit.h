#ifndef OOPPROJECT_FRUIT_H
#define OOPPROJECT_FRUIT_H


#include <string>

class Fruit {
private:
    unsigned int x;
    unsigned int y;

public:
    Fruit(unsigned int x, unsigned int y);
    virtual ~Fruit();
    unsigned int getX() const;
    unsigned int getY() const;
    virtual std::string eaten() = 0;
};


#endif //OOPPROJECT_FRUIT_H
