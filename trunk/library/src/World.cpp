#include <sstream>
#include <thread>
#include <random>
#include "World.h"
#include "Apple.h"
#include "Avocado.h"
#include "Melon.h"
#include <wx/wx.h>

Size::Size(unsigned int width, unsigned int height) : width(width), height(height) {}

unsigned int Size::getWidth() const {
    return width;
}

unsigned int Size::getHeight() const {
    return height;
}

Size::~Size() {

}

World::World(unsigned int width, unsigned int height) : size(width,height) {}

const std::vector<std::shared_ptr<Fruit>> &World::getFruits() {
    return fruits;
}

const Size &World::getSize() const {
    return size;
}

void World::addSnake() {
    Head head(size.getWidth()/2, size.getHeight()/2, this);
    auto snake = std::make_shared<Snake>(head);
    snakes.push_back(snake);
}

void World::addFruit(std::shared_ptr<Fruit> fruit) {
    fruits.push_back(fruit);
}

void World::eraseFruit(int index) {
    fruits.erase(fruits.begin() + index);
}

void World::play(Observer &observer) {
    addSnake();
    getSnake()->turn(up);
    int startingLength = 4;
    for (int i = 0; i < startingLength - 1; ++i) {
        getSnake()->grow();
    }
    getSnake()->turn(none);

    while (!getSnake()->isDead()) {

        /// Get user input via handler
        if (observer.getInput() == exitGame) {
            break;
        } else {
            getSnake()->turn(observer.getInput());
        }

        if (getSnake()->getHead().canEat()) {
            auto fruit = getSnake()->getHead().eat();
            getSnake()->eat(fruit);
            //std::cout << "Eating" << std::endl << std::endl;
        }
        getSnake()->move();
        //getSnake()->printSnake();

        /// Adding new fruits if necessary
        if (shouldAddApple()) {
            wxPoint point = randomisePoint();
            //std::cout << "Apple[" << point.x << "," << point.y << "]" << std::endl;
            auto APPLE = std::make_shared<Apple>(point.x, point.y);
            addFruit(APPLE);
        }
        if (shouldAddAvocado()) {
            wxPoint point = randomisePoint();
            auto AVOCADO = std::make_shared<Avocado>(point.x, point.y);
            addFruit(AVOCADO);
        }
        if (shouldAddMelon()) {
            wxPoint point = randomisePoint();
            auto MELON = std::make_shared<Melon>(point.x, point.y);
            addFruit(MELON);
        }

        if (observer.observe(this)) {
            break;
        }

    }
    /// Ending the game
    std::stringstream sout;
    sout << "Game over. Your score is " << getSnake()->getScore() << std::endl
    << "Highscore is " << observer.getHighscore();
    wxString finalMessage = sout.str();
    wxLogMessage(finalMessage);
}

bool World::shouldAddApple() {
    bool isThereApple = false;
    for (int i = 0; i < fruits.size(); ++i) {
        if (fruits[i]->eaten() == "Apple") {
            isThereApple = true;
        }
    }
    return !isThereApple;
}

bool World::shouldAddAvocado() {
    bool noAvocado = true;
    for (int i = 0; i < fruits.size(); ++i) {
        if (fruits[i]->eaten() == "Avocado") {
            noAvocado = false;
        }
    }
    return getSnake()->getScore() > 0 && noAvocado && getSnake()->getScore() % 4 == 0;
}

bool World::shouldAddMelon() {
    bool noMelon = true;
    for (int i = 0; i < fruits.size(); ++i) {
        if (fruits[i]->eaten() == "Melon") {
            noMelon = false;
        }
    }
    return getSnake()->getScore() > 0 && noMelon && getSnake()->getScore() % 6 == 0;
}

std::shared_ptr<Snake> World::getSnake() const {
    return snakes.at(0);
}

wxPoint World::randomisePoint() {
    bool isPointEmpty = false;
    unsigned int X = 0;
    unsigned int Y = 0;
    while (!isPointEmpty) {
        X = random(0, size.getWidth() - 1);
        Y = random(0, size.getHeight() - 1);
        bool isOnHead = false;
        if (getSnake()->getHead().getX() == X && getSnake()->getHead().getY() == Y)
            isOnHead = true;
        bool isOnTail = false;
        for (int i = 0; i < getSnake()->length(); ++i) {
            if (getSnake()->getBody()[i]->getX() == X && getSnake()->getBody()[i]->getY() == Y)
                isOnTail = true;
        }
        bool isOnFruit = false;
        for (int i = 0; i < fruits.size(); ++i) {
            if (fruits[i]->getX() == X && fruits[i]->getY() == Y)
                isOnFruit = true;
        }
        if (!isOnFruit && !isOnHead && !isOnTail)
            isPointEmpty = true;
    }
    wxPoint point(X, Y);
    return point;
}

const std::shared_ptr<Fruit> &World::operator[](unsigned int i) {
    try {
        return fruits.at(i);
    } catch (std::out_of_range &e) {
        throw OutOfFruits("Reaching out of world's fruits");
    }
}

World::~World() {
    fruits.clear();
    snakes.clear();
}

int random(int min, int max) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    return gen() % (max + 1) + min;
}

direction Observer::getInput() const {
    return input;
}

int Observer::getHighscore() const {
    return highscore;
}

OutOfFruits::OutOfFruits(const std::string &message) : SnakeException(message) {

}
