//
// Created by aleksander on 06.01.17.
//

#ifndef ZPR_BUILDING_H
#define ZPR_BUILDING_H


#include "Point.h"
#include "LineSegment.h"

class Building {

public:
    Building(const Point &upperLeft, const Point &lowerRight);

    bool hasIntersection(const LineSegment &straightLine) const;
private:
    LineSegment firstDiagonal, secondDiagonal;
    int upperX, lowerX;
    int upperY, lowerY;

};


#endif //ZPR_BUILDING_H
