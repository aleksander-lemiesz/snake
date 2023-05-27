#include <iostream>
#include "Fruit.h"
#include "Snake.h"
#include "Tail.h"

int Snake::getSpeed() const {
    return speed;
}

void Snake::accelerate(int a) {
    speed += a;
}

int Snake::length() const {
    return body.size();
}

void Snake::grow() {
    direction d = none;
    unsigned int index = 0;
    unsigned int x;
    unsigned int y;
    unsigned int X;
    unsigned int Y;
    if (length() > 0) {
        index = body[length() - 1]->getIndex() + 1;
        x = body[length() - 1]->getX();
        y = body[length() - 1]->getY();
        if (length() >= 2) {
            X = body[length() - 2]->getX();
            Y = body[length() - 2]->getY();
        } else {
            X = head.getX();
            Y = head.getY();
        }
        if (x - X == 1)
            d = left;
        if (x - X == -1)
            d = right;
        if (y - Y == 1)
            d = down;
        if (y - Y == -1)
            d = up;
    } else {
        d = head.getDirection();
        x = head.getX();
        y = head.getY();
    }
    switch (d) {
        case up : --y; break;
        case down : ++y; break;
        case left : ++x; break;
        case right : --x; break;
        default  :      break;
    }
    auto tail = std::make_shared<Tail>(x, y, index, this);
    body.push_back(tail);
}

void Snake::move() {
    if (head.getDirection() != none) {
        if (!body.empty()) {
            for (int i = 0; i < length(); ++i) {
                body[length() - 1 - i]->move();
            }
        }
        head.move();
    }
}

const std::vector<std::shared_ptr<Tail>> &Snake::getBody() const {
    return body;
}

const Head &Snake::getHead() const {
    return head;
}

bool Snake::isDead() {
    for (int i = 0; i < length(); ++i) {
        if (head.getY() == body[i]->getY() && head.getX() == body[i]->getX()) {
            return true;
        }
    }
    return head.isOutsideWorld();
}

Snake::Snake(const Head &head) : head(head) {}

void Snake::eat(std::shared_ptr<Fruit> fruit) {
    std::string type = fruit->eaten();
    if (type == "Apple") {
        score++;
        accelerate(1);
        grow();
    } else if (type == "Avocado") {
        score += 5;
        accelerate(10);
    } else if (type == "Melon") {
        accelerate(-5);
    }
}

void Snake::turn(direction turnDirection) {
    head.turn(turnDirection);
}

int Snake::getScore() const {
    return score;
}

void Snake::printSnake() {
    std::cout << "head[" << getHead().getX() <<
              ", " << getHead().getY() << "]" << std::endl;

    for (int i = 0; i < length(); ++i) {
        std::cout << "s(" << i << ")[" << body[i]->getX() <<
                  ", " << body[i]->getY() << "]" << std::endl;
    }
    std::cout << std::endl;
}

const std::shared_ptr<Tail> &Snake::operator[](unsigned int i) const {
    try {
        return body.at(i);
    } catch (std::out_of_range &e) {
        throw OutOfBody("Reaching out of snake's body");
    }
}

Snake::~Snake() {
    body.clear();
}

SnakeException::SnakeException(const std::string &message) : logic_error(message) {

}

std::string SnakeException::message() const {
    return what();
}

OutOfBody::OutOfBody(const std::string &message) : SnakeException(message) {

}
