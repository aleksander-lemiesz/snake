#ifndef OOPPROJECT_WORLD_H
#define OOPPROJECT_WORLD_H

#include <vector>
#include <memory>
#include "Snake.h"
#include "Fruit.h"
#include <wx/wx.h>

class OutOfFruits : public SnakeException {
public:
    explicit OutOfFruits(const std::string &message);
};

class World;
class Observer {
protected:
    direction input = none;
    int highscore = 0;
public:
    direction getInput() const;
    int getHighscore() const;
    virtual bool observe(World *world) = 0;
};

class Size {
private:
    unsigned int width;
    unsigned int height;

public:
    Size(unsigned int width, unsigned int height);
    virtual ~Size();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
};

class World {
private:
    Size size;
    std::vector<std::shared_ptr<Snake>> snakes;
    std::vector<std::shared_ptr<Fruit>> fruits;

public:
    World(unsigned int width, unsigned int height);
    virtual ~World();
    const Size &getSize() const;
    const std::vector<std::shared_ptr<Fruit>> &getFruits();
    const std::shared_ptr<Fruit> &operator[](unsigned int i);
    void addSnake();
    void addFruit(std::shared_ptr<Fruit> fruit);
    void eraseFruit(int index);
    void play(Observer &observer);
    bool shouldAddApple();
    bool shouldAddAvocado();
    bool shouldAddMelon();
    std::shared_ptr<Snake> getSnake() const;
    wxPoint randomisePoint();
};

int random(int min, int max);


#endif //OOPPROJECT_WORLD_H
