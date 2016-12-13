//
// Created by Aleksander on 29.10.2016.
//

#include "Point.h"

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point() : x(0), y(0) {}

int Point::getX() const {
    return x;
}

void Point::setX(int x) {
    Point::x = x;
}

int Point::getY() const {
    return y;
}

void Point::setY(int y) {
    Point::y = y;
}

bool Point::operator==(const Point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}

Point& Point::operator-=(const Point &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Point& Point::operator+=(const Point &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

const Point Point::operator-(const Point &rhs) const {
    Point result = *this;
    result -= rhs;
    return result;
}

const Point Point::operator+(const Point &rhs) const {
    Point result = *this;
    result += rhs;
    return result;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "x: " << point.x << " y: " << point.y;
    return os;
}

