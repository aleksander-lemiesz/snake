#include <boost/test/unit_test.hpp>
#include "Snake.h"
#include "World.h"
#include "Head.h"


BOOST_AUTO_TEST_SUITE(SnakeTestSuite)

    BOOST_AUTO_TEST_CASE(GrowAndMoveTest) {
        World world(50, 50);
        Head head(10, 10, &world);
        Snake snake(head);
        snake.turn(up);
        snake.grow();
        snake.printSnake();
        BOOST_CHECK_EQUAL(snake.getBody()[0]->getX(), 10);
        BOOST_CHECK_EQUAL(snake.getBody()[0]->getY(), 9);
        snake.move();

        BOOST_CHECK_EQUAL(snake.getHead().getX(), 10);
        BOOST_CHECK_EQUAL(snake.getHead().getY(), 11);
        BOOST_CHECK_EQUAL(snake.getBody()[0]->getX(), 10);
        BOOST_CHECK_EQUAL(snake.getBody()[0]->getY(), 10);
        snake.printSnake();

        snake.turn(right);
        snake.grow();
        BOOST_CHECK_EQUAL(snake.getBody()[1]->getX(), 10);
        BOOST_CHECK_EQUAL(snake.getBody()[1]->getY(), 9);
        BOOST_CHECK_EQUAL(snake.getHead().getX(), 10);
        BOOST_CHECK_EQUAL(snake.getHead().getY(), 11);
        BOOST_CHECK_EQUAL(snake.getBody()[0]->getX(), 10);
        BOOST_CHECK_EQUAL(snake.getBody()[0]->getY(), 10);
        snake.printSnake();
    }

    BOOST_AUTO_TEST_CASE(isDeadCollisionTest) {
        World world(50, 50);
        Head head(10, 10, &world);
        Snake snake(head);
        snake.turn(up);
        snake.grow();
        BOOST_CHECK_EQUAL(snake.getBody()[0]->getX(), 10);
        BOOST_CHECK_EQUAL(snake.getBody()[0]->getY(), 9);
        snake.move();

        snake.turn(right);
        snake.grow();
        BOOST_CHECK_EQUAL(snake.getBody()[1]->getX(), 10);
        BOOST_CHECK_EQUAL(snake.getBody()[1]->getY(), 9);
        snake.move();

        snake.turn(down);
        snake.grow();
        snake.move();

        snake.turn(left);
        snake.grow();
        BOOST_CHECK_EQUAL(snake.isDead(), false);
        snake.move();
        BOOST_CHECK_EQUAL(snake.isDead(), true);
    }

    BOOST_AUTO_TEST_CASE(isDeadOutTest) {
        World world(1, 1);
        Head head(0, 0, &world);
        Snake snake(head);
        BOOST_CHECK_EQUAL(snake.isDead(), false);

        snake.turn(up);
        snake.move();
        BOOST_CHECK_EQUAL(snake.isDead(), true);

        snake.turn(down);
        snake.move();
        snake.move();
        BOOST_CHECK_EQUAL(snake.isDead(), true);

        snake.turn(up);
        snake.move();
        BOOST_CHECK_EQUAL(snake.isDead(), false);

        snake.turn(left);
        snake.move();
        BOOST_CHECK_EQUAL(snake.isDead(), true);

        snake.turn(right);
        snake.move();
        snake.move();
        BOOST_CHECK_EQUAL(snake.isDead(), true);
    }

BOOST_AUTO_TEST_SUITE_END()