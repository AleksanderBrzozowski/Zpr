//
// Created by Aleksander on 30.10.2016.
//

#include<gtest/gtest.h>
#include <RouteVector.h>

void checkRouteVector(const RouteVector &routeVector, int x, int y);


TEST(RouteVectorTest, 0_0_RouteVector){
    RouteVector routeVector(Point(1, 1), Point(1, 1));
    checkRouteVector(routeVector, 0, 0);
}

TEST(RouteVectorTest, 1_0_RouteVector){
    RouteVector routeVector(Point(-100, 5), Point(1, 5));
    checkRouteVector(routeVector, 1, 0);
}

TEST(RouteVectorTest, 0_1_RouteVector){
    RouteVector routeVector(Point(-5, 100), Point(-5, 200));
    checkRouteVector(routeVector, 0, 1);
}

TEST(RouteVectorTest, minus1_0_RouteVector){
    RouteVector routeVector(Point(-5, 0), Point(-100, 0));
    checkRouteVector(routeVector, -1, 0);
}

TEST(RouteVectorTest, 0_minus1_RouteVector){
    RouteVector routeVector(Point(100, -5), Point(100, -500));
    checkRouteVector(routeVector, 0, -1);
}

TEST(RouteVectorTest, ConstructNotOkPoints) {
    ASSERT_THROW(RouteVector(Point(10, 10), Point(0, 0)), std::invalid_argument);
    ASSERT_THROW(RouteVector(Point(100, 100), Point(-100, -100)), std::invalid_argument);
    ASSERT_THROW(RouteVector(Point(-5, 5), Point(-10, -15)), std::invalid_argument);
}


TEST(RouteVectorTest, routeVectorEquals) {
    EXPECT_EQ(RouteVector(Point(1, 1), Point(1, 10)), RouteVector(Point(1, 1), Point(1, 15)));
}

TEST(RouteVectorTest, routeVectorNotEquals) {
    EXPECT_NE(RouteVector(Point(1, 1), Point(1, 10)), RouteVector(Point(1, 1), Point(1, -10)));
}

void checkRouteVector(const RouteVector &routeVector, int x, int y) {
    ASSERT_EQ(x, routeVector.getX());
    ASSERT_EQ(y, routeVector.getY());
    ASSERT_EQ(RouteVector(x, y), routeVector);
}
