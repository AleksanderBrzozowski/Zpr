//
// Created by Aleksander on 30.10.2016.
//

#include<gtest/gtest.h>
#include <RouteVector.h>

void constructNotOkPoints(const Point &begin, const Point &end);

TEST(RouteVectorTest, ConstructOkPoints) {
    RouteVector(Point(1, 1), Point(1, 1));
    RouteVector(Point(1, 5), Point(10, 5));
    RouteVector(Point(-5, 10), Point(10, 10));
    RouteVector(Point(-5, -10), Point(-100, -10));
}

TEST(RouteVectorTest, ConstructNotOkPoints) {
    constructNotOkPoints(Point(10, 10), Point(0, 0));
    constructNotOkPoints(Point(-5, 5), Point(-10, -15));
    constructNotOkPoints(Point(100, 100), Point(-100, -100));
}


TEST(RouteVectorTest, routeVectorEquals) {
    EXPECT_EQ(RouteVector(Point(1, 1), Point(1, 10)), RouteVector(Point(1, 1), Point(1, 15)));
}

TEST(RouteVectorTest, routeVectorNotEquals) {
    EXPECT_NE(RouteVector(Point(1, 1), Point(1, 10)), RouteVector(Point(1, 1), Point(1, -10)));
}

void constructNotOkPoints(const Point &begin, const Point &end) {
    try {
        RouteVector(begin, end);
        FAIL();
    }catch (std::invalid_argument){}
}
