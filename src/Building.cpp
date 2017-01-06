//
// Created by aleksander on 06.01.17.
//

#include "Building.h"

Building::Building(const Point &upperLeft, const Point &lowerRight) :
        firstDiagonal(StraightLine(upperLeft, lowerRight)),
        secondDiagonal(
                StraightLine(
                        Point(upperLeft.getX(), lowerRight.getY()),
                        Point(lowerRight.getX(), upperLeft.getY()))
        ),
        upperX(lowerRight.getX()), lowerX(upperLeft.getX()), upperY(upperLeft.getY()), lowerY(lowerRight.getY())
{}

bool Building::isCommonPointInsideBuilding(const StraightLine &straightLine) const{
    StraightLine::Solution firstSolution = firstDiagonal.hasSolution(straightLine);
    StraightLine::Solution secondSolution = secondDiagonal.hasSolution(straightLine);

    if(firstSolution == StraightLine::Solution::MANY || secondSolution == StraightLine::Solution::MANY)
        return true;
    else if(firstSolution == StraightLine::Solution::ONE || secondSolution == StraightLine::Solution::ONE) {
        std::pair<float, float> firstCommonPoint = firstDiagonal.commonPoint(straightLine);
        std::pair<float, float> secondCommonPoint = secondDiagonal.commonPoint(straightLine);
        return isPointInsideBuilding(firstCommonPoint) || isPointInsideBuilding(secondCommonPoint);
    }
    else
        return false;
}

bool Building::isPointInsideBuilding(const std::pair<float, float> &point) const {
    return point.first >= lowerX && point.first <= upperX &&
           point.second >= lowerY && point.second <= upperY;
}


