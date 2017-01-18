//
// Created by aleksander on 06.01.17.
//

#include <gtest/gtest.h>
#include <Building.h>


TEST(BuildingTest, intersectionPointInsideBuildingWhenLineSameAsBuildingDiagonal) {
    Building building(Point(0, 3), Point(2, 0));

    LineSegment first(Point(0, 0), Point(2, 3));
    LineSegment second(Point(0, 3), Point(2, 0));

    ASSERT_TRUE(building.hasIntersection(first));
    ASSERT_TRUE(building.hasIntersection(second));
}


TEST(BuildingTest, commonPointInsideBuilding) {
    Building building(Point(0, 3), Point(2, 0));

    LineSegment first(Point(-1, 2), Point(2, 5));
    LineSegment second(Point(-1, 1), Point(1, -1));

    ASSERT_TRUE(building.hasIntersection(first));
    ASSERT_TRUE(building.hasIntersection(second));
}


TEST(BuildingTest, commonPointNotInsideBuilding) {
    Building building(Point(0, 3), Point(2, 0));

    LineSegment first(Point(-1, 3), Point(5, 5));
    LineSegment second(Point(-1, 5), Point(0, -1));

    ASSERT_FALSE(building.hasIntersection(first));
    ASSERT_FALSE(building.hasIntersection(second));
}
