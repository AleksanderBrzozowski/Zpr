//
// Created by aleksander on 06.01.17.
//

#include "Building.h"

Building::Building(const Point &upperLeft, const Point &lowerRight) :
        firstDiagonal(LineSegment(upperLeft, lowerRight)),
        secondDiagonal(
                LineSegment(
                        Point(upperLeft.getX(), lowerRight.getY()),
                        Point(lowerRight.getX(), upperLeft.getY()))
        ),
        upperX(lowerRight.getX()), lowerX(upperLeft.getX()), upperY(upperLeft.getY()), lowerY(lowerRight.getY())
{}

bool Building::hasIntersection(const LineSegment &lineSegment) const{
    return firstDiagonal.hasIntersection(lineSegment) || secondDiagonal.hasIntersection(lineSegment);
}


