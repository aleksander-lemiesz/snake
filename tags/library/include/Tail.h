#ifndef OOPPROJECT_TAIL_H
#define OOPPROJECT_TAIL_H


#include "Segment.h"
class Snake;

class Tail : public Segment {
private:
    Snake* snake;
    unsigned int index = 0;

public:
    Tail(unsigned int x, unsigned int y, unsigned int index, Snake *snake);
    virtual ~Tail();
    void move() override;
    unsigned int getIndex() const;
};


#endif //OOPPROJECT_TAIL_H
