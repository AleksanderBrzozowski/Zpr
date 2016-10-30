//
// Created by Aleksander on 30.10.2016.
//

#include <gtest/gtest.h>
#include <Route.h>

class RouteTest : public ::testing::Test {
public:
    std::vector<Point*> points;
    Route* route;

    RouteTest() {
        route = new Route(points);
    }

    virtual ~RouteTest() {
        delete route;
    }
};

TEST_F(RouteTest, whenNoMorePointsReturnTrue) {
    EXPECT_TRUE(route->isEnd());
}


TEST_F(RouteTest, whenMorePointsReturnFalse) {
    points.push_back(new Point(1, 1));
    EXPECT_FALSE(route->isEnd());
}

TEST_F(RouteTest, whenPresentPointReturnVector) {
    Point *pointToGo = new Point(1, 2);
    points.push_back(pointToGo);

    Point startPoint(1, 10);

    RouteVector expected(startPoint, *pointToGo);
    EXPECT_EQ(expected, route->getVector(startPoint));
}


TEST_F(RouteTest, whenNoPresentPointThrowExc) {
    Point startPoint(1, 10);
    try {
        route->getVector(startPoint);
        FAIL();
    } catch (std::runtime_error) {}
}


TEST_F(RouteTest, getDistancePresentPoints) {
    Point *pointToGo = new Point(5, 10);
    points.push_back(pointToGo);

    Point startPoint(10, 10);

    EXPECT_EQ(5, route->getDistance(startPoint));
}


TEST_F(RouteTest, getDistanceNoPresentPoints) {
    Point startPoint(1, 5);
    try {
        route->getDistance(startPoint);
        FAIL();
    } catch (std::runtime_error) {}
}

TEST_F(RouteTest, nextPointPresentPoints) {
    Point *secondPoint = new Point(5, 10);
    points.push_back(new Point(1, 10));
    points.push_back(secondPoint);

    route->nextPoint();
    EXPECT_EQ(secondPoint, points[0]);
}


TEST_F(RouteTest, nextPointNoPresentPoints) {
    try {
        route->nextPoint();
        FAIL();
    } catch (std::runtime_error) {}
}


TEST(RouteTestConstructor, ConstructorOkPoints) {
    std::vector<Point*> points = {new Point(0, 1), new Point(10, 1), new Point(10, 10), new Point(100, 10)};
    new Route(points);
}

TEST(RouteTestConstructor, ConstructorNotOkPoints) {
    std::vector<Point*> points = {new Point(0, 1), new Point(10, 5), new Point(5, 10), new Point(100, 10)};
    try {
        new Route(points);
        FAIL();
    } catch (std::invalid_argument) {}
}
