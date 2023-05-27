#ifndef OOPPROJECT_SNAKE_H
#define OOPPROJECT_SNAKE_H

#include <memory>
#include <vector>
#include <string>
#include "Head.h"
#include "Tail.h"

class SnakeException : public std::logic_error {
public:
    explicit SnakeException(const std::string &message);
    virtual std::string message() const;
};

class OutOfBody : public SnakeException {
public:
    explicit OutOfBody(const std::string &message);
};

class Segment;

class Snake {
private:
    Head head;
    int speed = 1;
    int score = 0;
    std::vector<std::shared_ptr<Tail>> body;

public:
    Snake(const Head &head);
    virtual ~Snake();
    void turn(direction turnDirection);
    void move();
    void grow();
    int length() const ;
    void accelerate(int a);
    bool isDead();
    int getSpeed() const;
    const std::vector<std::shared_ptr<Tail>> &getBody() const;
    const std::shared_ptr<Tail> &operator[](unsigned int i) const ;
    const Head &getHead() const;
    void eat(std::shared_ptr<Fruit> fruit);
    int getScore() const;
    void printSnake();
};

#endif //OOPPROJECT_SNAKE_H
