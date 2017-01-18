#ifndef ZPR_BUILDING_H
#define ZPR_BUILDING_H


#include "Point.h"
#include "LineSegment.h"

/*!
 * This class represents building as rectangle.
 * @author Aleksander Brzozowski
 */
class Building {

public:
    /*!
     * Constructs building using two points of rectangle's diagonal.
     * @param upperLeft     Point in the upper left of rectangle
     * @param lowerRight    Point in the lower right of rectangle
     */
    Building(const Point &upperLeft, const Point &lowerRight);

    /*!
     * Checks whether line segment has intersection inside building.
     * @param lineSegment   Line segment to check
     * @return              Is line intersection inside building
     */
    bool hasIntersection(const LineSegment &lineSegment) const;
private:
    LineSegment firstDiagonal, secondDiagonal;
    int upperX, lowerX;
    int upperY, lowerY;

};


#endif //ZPR_BUILDING_H
