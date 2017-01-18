//
// Created by Aleksander on 29.10.2016.
//

#ifndef ZPR_POINT_H
#define ZPR_POINT_H


#include <ostream>

/*!
 * Represents 2-D point.
 * @author Aleksander Brzozowski
 */
class Point {

private:
    int x,y;
public:
    /*!
     * Constructs point using passed x and y (x, y).
     * @param x Point's x
     * @param y Point's y
     */
    Point(int x, int y);
    /*!
     * Constructs point (0, 0)
     */
    Point();
    /*!
     * Constructs shallow copy of passed point.
     * @param point Used point to create copy
     */
    Point(const Point &point);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;

    Point& operator-=(const Point &rhs);
    Point& operator+=(const Point &rhs);
    const Point operator-(const Point &rhs) const;
    const Point operator+(const Point &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};


#endif //ZPR_POINT_H
