#include <boost/test/unit_test.hpp>
#include <Head.h>
#include <World.h>
#include <Apple.h>

BOOST_AUTO_TEST_SUITE(HeadTestSuite)

    BOOST_AUTO_TEST_CASE(TurnAndMoveTest) {
        World world(50, 50);
        Head head(10, 10, &world);
        BOOST_CHECK_EQUAL(head.getDirection(), none);
        head.turn(up);
        BOOST_CHECK_EQUAL(head.getDirection(), up);
        BOOST_CHECK_EQUAL(head.getX(), 10);
        BOOST_CHECK_EQUAL(head.getY(), 10);
        head.move();
        BOOST_CHECK_EQUAL(head.getX(), 10);
        BOOST_CHECK_EQUAL(head.getY(), 11);
        head.turn(right);
        head.move();
        BOOST_CHECK_EQUAL(head.getX(), 11);
        BOOST_CHECK_EQUAL(head.getY(), 11);
        head.turn(down);
        head.move();
        BOOST_CHECK_EQUAL(head.getX(), 11);
        BOOST_CHECK_EQUAL(head.getY(), 10);
        head.turn(left);
        head.move();
        BOOST_CHECK_EQUAL(head.getX(), 10);
        BOOST_CHECK_EQUAL(head.getY(), 10);
    }

    BOOST_AUTO_TEST_CASE(CanEatTest) {
        World world(50, 50);
        Head head(10, 10, &world);
        auto apple = std::make_shared<Apple>(11, 10);
        world.addFruit(apple);
        head.turn(right);
        BOOST_CHECK_EQUAL(head.canEat(), false);
        head.move();
        BOOST_CHECK_EQUAL(head.canEat(), true);
    }

    BOOST_AUTO_TEST_CASE(EatTest) {
        World world(50, 50);
        Head head(10, 10, &world);
        auto apple = std::make_shared<Apple>(11, 10);
        world.addFruit(apple);
        head.turn(right);
        head.move();
        BOOST_CHECK_EQUAL(head.eat(), apple);
    }

BOOST_AUTO_TEST_SUITE_END()