//
// Created by aleksander on 06.01.17.
//

#include <stdexcept>
#include "LineSegment.h"


LineSegment::LineSegment(const Point &pointA, const Point &pointB) {
    if (pointA == pointB)
        throw std::invalid_argument("Points cannot be same");
    a0 = pointB.getX() - pointA.getX();
    a1 = pointB.getY() - pointA.getY();
    b = pointA.getY() * a0 - pointA.getX() * a1;

    upperX = std::max(pointA.getX(), pointB.getX());
    lowerX = std::min(pointA.getX(), pointB.getX());

    upperY = std::max(pointA.getY(), pointB.getY());
    lowerY = std::min(pointA.getY(), pointB.getY());
}
std::pair<float, float> LineSegment::intersectionPoint(const LineSegment &lineSegment) const {
    int mainDet = calculateDet(a0, lineSegment.a0, a1, lineSegment.a1);
    if(mainDet == 0)
        throw std::invalid_argument("Lines have none or many common points");
    int yDet = calculateDet(b, lineSegment.b, a1, lineSegment.a1);
    int xDet = calculateDet(b, lineSegment.b, a0, lineSegment.a0);

    return std::pair<float, float>((float)xDet / mainDet, (float)yDet / mainDet);
}

int LineSegment::calculateDet(int a00, int a10, int a01, int a11) const {
    return a00 * a11 - a10 * a01;
}

bool LineSegment::hasIntersection(const LineSegment &lineSegment) const {
    if(calculateDet(a0, lineSegment.a0, a1, lineSegment.a1) == 0){
        if (calculateDet(a0, lineSegment.a0, b, lineSegment.b) == 0) {
            //many solutions
            return isInBounds(lineSegment.upperX, lineSegment.upperY) ||
                   isInBounds(lineSegment.lowerX, lineSegment.lowerY) ||
                   lineSegment.isInBounds(this->upperX, this->upperY) ||
                   lineSegment.isInBounds(this->lowerX, this->lowerY);

        }
        else //no solutions
            return false;
    }
    // one solution
    auto intersectPoint = intersectionPoint(lineSegment);
    return isInBounds(intersectPoint.first, intersectPoint.second)
            && lineSegment.isInBounds(intersectPoint.first, intersectPoint.second);
}

bool LineSegment::isInBounds(float x, float y) const{
    return lowerX <= x && x <= upperX && lowerY <= y && y <= upperY;
}
