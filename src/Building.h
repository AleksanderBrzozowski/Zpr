//
// Created by aleksander on 06.01.17.
//

#ifndef ZPR_BUILDING_H
#define ZPR_BUILDING_H


#include "Point.h"
#include "StraightLine.h"

class Building {

public:
    Building(const Point &upperLeft, const Point &lowerRight);

    bool isCommonPointInsideBuilding(const StraightLine &straightLine) const;
private:
    StraightLine firstDiagonal, secondDiagonal;
    int upperX, lowerX;
    int upperY, lowerY;

    bool isPointInsideBuilding(const std::pair<float, float> &point) const;
};


#endif //ZPR_BUILDING_H
