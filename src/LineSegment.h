#ifndef ZPR_STRAIGHTLINE_H
#define ZPR_STRAIGHTLINE_H


#include "Point.h"

/*!
 * Represents segment line.
 * Stores straight line equation:
 * (y - ya) * (xb - xa) - (yb - ya) * (x - xa) = 0
 * y * (xb - xa) - x * (yb - ya) = ya * (xb - xa) - xa * (yb - ya)
 * and limits of segment line (x and y limits)
 * @author Aleksander Brzozowski
 */
class LineSegment {
public:
    /*!
     * Constructs LineSegment.
     * @param pointA First point of line segment
     * @param pointB Second point of line segment
     */
    LineSegment(const Point &pointA, const Point &pointB);

    /*!
     * Computes intersection point of line segments.
     * @throw              std::invalid_argument when there isn't intersection point
     * @param lineSegment  Line segment used to compute intersection point
     * @return             Intersection point as a pair of x and y (first x, second y)
     */
    std::pair<float, float> intersectionPoint(const LineSegment &lineSegment) const;
    /*!
     * Checks whether line segments have intersection point.
     * @param lineSegment Line segment to check
     * @return            Has line segments intersection point
     */
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
