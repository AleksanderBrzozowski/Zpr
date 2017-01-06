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
class StraightLine {
public:
    StraightLine(const Point &pointA, const Point &pointB);

    enum Solution{ONE, MANY, NONE};

    Solution hasSolution(const StraightLine &straightLine) const;
    std::pair<float, float> commonPoint(const StraightLine &straightLine) const;
private:
    int a0; // xb - xa
    int a1; // yb - ya
    int b;  // ya * (xb - xa) - xa * (yb - ya)

    int calculateDet(int a00, int a10, int a01, int a11) const;
};


#endif //ZPR_STRAIGHTLINE_H
