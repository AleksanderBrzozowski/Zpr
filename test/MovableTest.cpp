//
// Created by Aleksander on 30.10.2016.
//

#include<gtest/gtest.h>
#include <Point.h>
#include <Movable.h>


class MovableTest : public ::testing::Test {
public:
    Point *lastPoint = new Point(200, -100);
    std::vector<Point *> points = {
            new Point(20, 10), new Point(20, 50), new Point(20, 20),
            new Point(-10, 20), new Point(-20, 20), new Point(-20, 10),
            new Point(-20, -100), new Point(-50, - 100), lastPoint
    };

    MovableTest() {}

    virtual ~MovableTest() {
        delete lastPoint;
    }
};

TEST_F(MovableTest, constructorOk) {
    std::vector<Point*> route{new Point(10, 10)};
    Movable (Point(10, 10), 10, route);
}

TEST_F(MovableTest, sampleRoute) {
    Movable movable(Point(20, 10), 5, points);
    while (movable.move()) ;

    EXPECT_EQ(*lastPoint, movable.getActualPoint());
}

TEST_F(MovableTest, anotherRoute) {
    Movable movable(Point(-100, 10), 9, points);
    while (movable.move()) ;

    EXPECT_EQ(*lastPoint, movable.getActualPoint());
}

