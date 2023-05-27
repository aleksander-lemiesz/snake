#include <boost/test/unit_test.hpp>
#include "World.h"
#include "Apple.h"
#include "Avocado.h"
#include "Melon.h"
#include <iostream>
#include <wx/wx.h>

BOOST_AUTO_TEST_SUITE(WorldTestSuite)

    BOOST_AUTO_TEST_CASE(RandomTest) {
        int a = random(1, 100);
        bool testValue;
        for (int i = 0; i < 100; ++i) {
            testValue = (1 <= a && a <= 100);
            BOOST_CHECK_EQUAL(testValue, true);
        }
    }

    BOOST_AUTO_TEST_CASE(SampleGameTest) {
        World world(5, 5);
        world.addSnake();
        world.getSnake()->printSnake();

        world.getSnake()->turn(up);
        world.getSnake()->grow();
        world.getSnake()->printSnake();
        world.getSnake()->grow();
        world.getSnake()->printSnake();
        world.getSnake()->move();
        world.getSnake()->printSnake();

        auto apple = std::make_shared<Apple>(1, 3);
        BOOST_CHECK_EQUAL(world.shouldAddApple(), true);
        world.addFruit(apple);
        world.getSnake()->turn(left);

        BOOST_CHECK_EQUAL(world.getSnake()->getHead().canEat(), false);

        world.getSnake()->move();
        int length = world.getSnake()->length();

        BOOST_CHECK_EQUAL(world.getSnake()->getHead().canEat(), true);
        if (world.getSnake()->getHead().canEat()) {
            auto fruit = world.getSnake()->getHead().eat();
            world.getSnake()->eat(fruit);
        }

        world.getSnake()->printSnake();

        BOOST_CHECK_EQUAL(world.getSnake()->length(), length + 1);

        world.getSnake()->printSnake();

    }

    BOOST_AUTO_TEST_CASE(ShouldAddAvocadoTest) {
        World world(5, 5);
        world.addSnake();

        auto avocado = std::make_shared<Avocado>(1, 1);
        auto apple = std::make_shared<Apple>(2, 2);
        BOOST_CHECK_EQUAL(world.shouldAddAvocado(), false);
        for (int i = 0; i < 4; ++i) {
            world.getSnake()->eat(apple);
        }
        BOOST_CHECK_EQUAL(world.shouldAddAvocado(), true);
        world.addFruit(avocado);
        BOOST_CHECK_EQUAL(world.shouldAddAvocado(), false);

        world.addFruit(apple);
        BOOST_CHECK_EQUAL(world.shouldAddAvocado(), false);
    }

    BOOST_AUTO_TEST_CASE(ShouldAddAppleTest) {
        World world(5, 5);
        world.addSnake();

        auto apple = std::make_shared<Apple>(2, 2);
        BOOST_CHECK_EQUAL(world.shouldAddApple(), true);
        world.addFruit(apple);
        BOOST_CHECK_EQUAL(world.shouldAddApple(), false);

        auto avocado = std::make_shared<Avocado>(1, 1);
        world.addFruit(avocado);
        BOOST_CHECK_EQUAL(world.shouldAddApple(), false);
    }

    BOOST_AUTO_TEST_CASE(ShouldAddMelonTest) {
        World world(5, 5);
        world.addSnake();

        auto melon = std::make_shared<Melon>(1, 1);
        auto apple = std::make_shared<Apple>(2, 2);
        BOOST_CHECK_EQUAL(world.shouldAddMelon(), false);
        for (int i = 0; i < 6; ++i) {
            world.getSnake()->eat(apple);
        }
        BOOST_CHECK_EQUAL(world.shouldAddMelon(), true);
        world.addFruit(melon);
        BOOST_CHECK_EQUAL(world.shouldAddMelon(), false);

        world.addFruit(apple);
        BOOST_CHECK_EQUAL(world.shouldAddMelon(), false);
    }

    BOOST_AUTO_TEST_CASE(RandomiseTest) {
        World world(5, 5);
        world.addSnake();
        auto apple = std::make_shared<Apple>(1, 1);
        world.addFruit(apple);
        world.getSnake()->turn(up);
        world.getSnake()->move();
        for (int i = 0; i < 3; ++i) {
            world.getSnake()->grow();
        }
        for (int i = 0; i < 1000; ++i) {
            wxPoint point = world.randomisePoint();

            BOOST_CHECK(!(world.getSnake()->getHead().getX() == point.x
            && world.getSnake()->getHead().getY() == point.y));
            for (int s = 0; s < world.getSnake()->length(); ++s) {

                BOOST_CHECK(!(world.getSnake()->getBody()[s]->getX() == point.x
                && world.getSnake()->getBody()[s]->getY() == point.y));
            }
            for (int f = 0; f < world.getFruits().size(); ++f) {

                BOOST_CHECK(!(world.getFruits()[f]->getX() == point.x
                && world.getFruits()[f]->getY() == point.y));
            }
        }

    }

BOOST_AUTO_TEST_SUITE_END()