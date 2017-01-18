//
// Created by aleksander on 06.01.17.
//

#include <gtest/gtest.h>
#include <LineSegment.h>


TEST(StraightLineTest, ThrowExceptionWhenPointsSameInCtor) {
    ASSERT_THROW(LineSegment(Point(1, 1), Point(1, 1)), std::invalid_argument);
}


TEST(StraightLineTest, OneSolutionWhenNotParralelLines) {
    LineSegment first(Point(1, 1), Point(2, 2));
    LineSegment second(Point(2, 0), Point(0, 2));

    ASSERT_TRUE(first.hasIntersection(second));
    ASSERT_TRUE(second.hasIntersection(first));
}

TEST(StraightLineTest, NoIntersect) {
    LineSegment first(Point(1, 1), Point(2, 2));
    LineSegment second(Point(-1, 0), Point(2, -1));

    ASSERT_FALSE(first.hasIntersection(second));
    ASSERT_FALSE(second.hasIntersection(first));
}

TEST(StraightLineTest, ThrowExceptionWhenNoneSolutionsInIntersectMethod) {
    LineSegment first(Point(-2, 1), Point(-3, 5));
    LineSegment second(Point(-3, 0), Point(-4, 4));

    ASSERT_THROW(first.intersectionPoint(second), std::invalid_argument);
    ASSERT_THROW(second.intersectionPoint(first), std::invalid_argument);
}

TEST(StraightLineTest, ThrowExceptionWhenManySolutionsInIntersectMethod) {
    LineSegment first(Point(-1, -1), Point(5, 5));
    LineSegment second(Point(1, 1), Point(2, 2));

    ASSERT_THROW(first.intersectionPoint(second), std::invalid_argument);
    ASSERT_THROW(second.intersectionPoint(first), std::invalid_argument);
}

TEST(StraightLineTest, CommonPointOkWhenOneSolution) {
    LineSegment first(Point(1, 1), Point(2, 2));
    LineSegment second(Point(5, 5), Point(5, 11));
    LineSegment third(Point(6, -1), Point(10, -1));

    ASSERT_EQ((std::pair<float, float>(5, 5)), first.intersectionPoint(second));
    ASSERT_EQ((std::pair<float, float>(5, 5)), second.intersectionPoint(first));

    ASSERT_EQ((std::pair<float, float>(-1, -1)), first.intersectionPoint(third));
    ASSERT_EQ((std::pair<float, float>(-1, -1)), third.intersectionPoint(first));

    ASSERT_EQ((std::pair<float, float>(5, -1)), third.intersectionPoint(second));
    ASSERT_EQ((std::pair<float, float>(5, -1)), second.intersectionPoint(third));
}

TEST(StraightLineTest, parralelLinesIntersect) {
    LineSegment first(Point(1, 1), Point(2, 2));
    LineSegment second(Point(0, 0), Point(3, 3));

    ASSERT_TRUE(first.hasIntersection(second));
    ASSERT_TRUE(second.hasIntersection(first));

    LineSegment third(Point(0, 0), Point(1, 1));
    LineSegment fourth(Point(0, 0), Point(1, 1));

    ASSERT_TRUE(third.hasIntersection(fourth));
    ASSERT_TRUE(fourth.hasIntersection(third));
}

TEST(StraightLineTest, parralelLinesNotIntersect) {
    LineSegment first(Point(1, 1), Point(2, 2));
    LineSegment second(Point(3, 3), Point(4, 4));

    ASSERT_FALSE(first.hasIntersection(second));
    ASSERT_FALSE(second.hasIntersection(first));
}
