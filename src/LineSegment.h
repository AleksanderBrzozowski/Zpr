//
// Created by aleksander on 06.01.17.
//

#ifndef ZPR_STRAIGHTLINE_H
#define ZPR_STRAIGHTLINE_H


#include "Point.h"

/**
 * Represents straight line equation:
 * (y - ya) * (xb - xa) - (yb - ya) * (x - xa) = 0
 * y * (xb - xa) - x * (yb - ya) = ya * (xb - xa) - xa * (yb - ya)
 */
class LineSegment {
public:
    LineSegment(const Point &pointA, const Point &pointB);

    std::pair<float, float> intersectionPoint(const LineSegment &lineSegment) const;
    bool hasIntersection(const LineSegment &lineSegment) const;
private:
    int a0; // xb - xa
    int a1; // yb - ya
    int b;  // ya * (xb - xa) - xa * (yb - ya)

    int upperX;
    int lowerX;
    int upperY;
    int lowerY;

    int calculateDet(int a00, int a10, int a01, int a11) const;
    bool isInBounds(float x, float y) const;
};


#endif //ZPR_STRAIGHTLINE_H
