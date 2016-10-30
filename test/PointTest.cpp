//
// Created by Aleksander on 30.10.2016.
//

#include <gtest/gtest.h>
#include <Point.h>


TEST(PointTest, pointEquals) {
    EXPECT_EQ(Point(5, 5), Point(5, 5));
}


TEST(PointTest, pointNotEquals) {
    EXPECT_NE(Point(-10, -10), Point(10, 10));
}
