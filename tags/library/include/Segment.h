#ifndef OOPPROJECT_SEGMENT_H
#define OOPPROJECT_SEGMENT_H

enum direction {
    up,
    down,
    left,
    right,
    none,
    exitGame
};

class Segment {
protected:
    unsigned int x;
    unsigned int y;
public:
    Segment(unsigned int x, unsigned int y);
    virtual ~Segment();
    unsigned int getX() const;
    unsigned int getY() const;

    virtual void move() = 0;
};


#endif //OOPPROJECT_SEGMENT_H
