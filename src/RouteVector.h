#ifndef ZPR_VECTOR_H
#define ZPR_VECTOR_H


#include "Point.h"
#include <stdexcept>

/*!
 * Represents vector.
 * @author Aleksander Brzozowski
 */
class RouteVector{

private:
    int x,y;
public:
    /*!
     * Constructs vector between two points.
     * Normalizes vector to 1.
     * Possible vectors are:
     * [-1, 0], [1, 0], [0, -1], [0, 1], [0, 0]
     * @param begin First point
     * @param end   Second point
     */
    RouteVector(const Point& begin, const Point& end);
    /*!
     * Constructs [0, 0] vector.
     */
    RouteVector();
    /*!
     * Constructs vector using passed x and y [x, y]
     * @param x Vector's x
     * @param y Vector's y
     */
    RouteVector(int x, int y);

    bool operator==(const RouteVector &rhs) const;

    bool operator!=(const RouteVector &rhs) const;

    int getX() const;

    int getY() const;
};


#endif //ZPR_VECTOR_H
