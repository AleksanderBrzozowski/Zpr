//
// Created by Aleksander on 29.10.2016.
//

#ifndef ZPR_POINT_H
#define ZPR_POINT_H


#include <ostream>

class Point {

private:
    int x,y;
public:
    Point(int x, int y);
    Point();

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int absDistance(const Point &point) const;

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;

    Point& operator-=(const Point &rhs);
    Point& operator+=(const Point &rhs);
    const Point operator-(const Point &rhs) const;
    const Point operator+(const Point &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};


#endif //ZPR_POINT_H
