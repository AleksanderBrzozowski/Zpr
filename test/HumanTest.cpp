//
// Created by Aleksander on 12.12.2016.
//

#include<gtest/gtest.h>
#include <memory>
#include <Point.h>
#include <MovableFactory.h>

class HumanTest : public ::testing::Test {
public:
    std::vector<std::shared_ptr<Point const>> points = {
            std::shared_ptr<Point const>(new Point(20, 10)),
            std::shared_ptr<Point const>(new Point(10, 10)),
            std::shared_ptr<Point const>(new Point(10, 50)),
            std::shared_ptr<Point const>(new Point(100, 50)),
            std::shared_ptr<Point const>(new Point(-10, 50))
    };
    MovableFactory factory;
    std::shared_ptr<Movable2> human;

    HumanTest() : human(factory.createHuman(*points[0], 5, points)) {}
};


TEST_F(HumanTest, constructorOk) {}


TEST_F(HumanTest, sampleRoute) {
   // ASSERT_EQ(human->getActualPoint(), *points[0]);
}
