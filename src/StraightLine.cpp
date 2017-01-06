//
// Created by aleksander on 06.01.17.
//

#include <stdexcept>
#include "StraightLine.h"


StraightLine::StraightLine(const Point &pointA, const Point &pointB) {
    if (pointA == pointB)
        throw std::invalid_argument("Points cannot be same");
    a0 = pointB.getX() - pointA.getX();
    a1 = pointB.getY() - pointA.getY();
    b = pointA.getY() * a0 - pointA.getX() * a1;
}

StraightLine::Solution StraightLine::hasSolution(const StraightLine &straightLine) const {
    if(calculateDet(a0, straightLine.a0, a1, straightLine.a1) == 0){
        if(calculateDet(a0, straightLine.a0, b, straightLine.b) == 0)
            return MANY;
        else
            return NONE;
    }
    return ONE;

}

std::pair<float, float> StraightLine::commonPoint(const StraightLine &straightLine) const {
    int mainDet = calculateDet(a0, straightLine.a0, a1, straightLine.a1);
    if(mainDet == 0)
        throw std::invalid_argument("Lines have none or many common points");
    int yDet = calculateDet(b, straightLine.b, a1, straightLine.a1);
    int xDet = calculateDet(b, straightLine.b, a0, straightLine.a0);

    return std::pair<float, float>((float)xDet / mainDet, (float)yDet / mainDet);
}

int StraightLine::calculateDet(int a00, int a10, int a01, int a11) const {
    return a00 * a11 - a10 * a01;
}
