//
// Created by aleksander on 06.01.17.
//

#include <gtest/gtest.h>
#include <StraightLine.h>


TEST(StraightLineTest, ThrowExceptionWhenPointsSameInCtor) {
    ASSERT_THROW(StraightLine(Point(1, 1), Point(1, 1)), std::invalid_argument);
}

TEST(StraightLineTest, ManySolutionsWhenSameLines) {
    StraightLine first(Point(0, 0), Point(1, 1));
    StraightLine second(Point(0, 0), Point(1, 1));
    StraightLine third(Point(0, 0), Point(2, 2));
    StraightLine fourth(Point(1, 1), Point(-1, -1));

    std::vector<StraightLine> lines{first, second, third, fourth};

    //checks all possible permutations between lines to have many solutions
    for (StraightLine &line : lines) {
        for(StraightLine &innerLine : lines)
            ASSERT_EQ(StraightLine::Solution::MANY, line.hasSolution(innerLine));
    }
}


TEST(StraightLineTest, NoSolutionsWhenParallelAndNoSame) {
    StraightLine first(Point(-2, 1), Point(-3, 5));
    StraightLine second(Point(-3, 0), Point(-4, 4));
    StraightLine third(Point(0, 3), Point(-1, 7));

    ASSERT_EQ(StraightLine::Solution::NONE, first.hasSolution(second));
    ASSERT_EQ(StraightLine::Solution::NONE, second.hasSolution(first));

    ASSERT_EQ(StraightLine::Solution::NONE, first.hasSolution(third));
    ASSERT_EQ(StraightLine::Solution::NONE, third.hasSolution(first));

    ASSERT_EQ(StraightLine::Solution::NONE, third.hasSolution(second));
    ASSERT_EQ(StraightLine::Solution::NONE, second.hasSolution(third));
}


TEST(StraightLineTest, OneSolutionWhenNotParralelLines) {
    StraightLine first(Point(1, 1), Point(2, 2));
    StraightLine second(Point(5, 5), Point(5, 11));
    StraightLine third(Point(6, -1), Point(10, -1));

    ASSERT_EQ(StraightLine::Solution::ONE, first.hasSolution(second));
    ASSERT_EQ(StraightLine::Solution::ONE, second.hasSolution(first));

    ASSERT_EQ(StraightLine::Solution::ONE, first.hasSolution(third));
    ASSERT_EQ(StraightLine::Solution::ONE, third.hasSolution(first));

    ASSERT_EQ(StraightLine::Solution::ONE, third.hasSolution(second));
    ASSERT_EQ(StraightLine::Solution::ONE, second.hasSolution(third));
}

TEST(StraightLineTest, ThrowExceptionWhenNoneSolutionsInCommonPoint) {
    StraightLine first(Point(-2, 1), Point(-3, 5));
    StraightLine second(Point(-3, 0), Point(-4, 4));

    ASSERT_THROW(first.commonPoint(second), std::invalid_argument);
    ASSERT_THROW(second.commonPoint(first), std::invalid_argument);
}

TEST(StraightLineTest, ThrowExceptionWhenManySolutionsInCommonPoint) {
    StraightLine first(Point(-1, -1), Point(5, 5));
    StraightLine second(Point(1, 1), Point(2, 2));

    ASSERT_THROW(first.commonPoint(second), std::invalid_argument);
    ASSERT_THROW(second.commonPoint(first), std::invalid_argument);
}

TEST(StraightLineTest, CommonPointOkWhenOneSolution) {
    StraightLine first(Point(1, 1), Point(2, 2));
    StraightLine second(Point(5, 5), Point(5, 11));
    StraightLine third(Point(6, -1), Point(10, -1));

    ASSERT_EQ((std::pair<float, float>(5, 5)), first.commonPoint(second));
    ASSERT_EQ((std::pair<float, float>(5, 5)), second.commonPoint(first));

    ASSERT_EQ((std::pair<float, float>(-1, -1)), first.commonPoint(third));
    ASSERT_EQ((std::pair<float, float>(-1, -1)), third.commonPoint(first));

    ASSERT_EQ((std::pair<float, float>(5, -1)), third.commonPoint(second));
    ASSERT_EQ((std::pair<float, float>(5, -1)), second.commonPoint(third));
}
