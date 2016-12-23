//
// Created by Aleksander on 29.10.2016.
//

#include "RouteVector.h"

RouteVector::RouteVector(const Point &begin, const Point &end) {
    if(!(begin.getX() == end.getX() || begin.getY() == end.getY()))
        throw std::invalid_argument("Points must have same x or y");

    int tempX = end.getX() - begin.getX();
    int tempY = end.getY() - begin.getY();

    x = tempX == 0 ? tempX : tempX < 0 ? -1 : 1;
    y = tempY == 0 ? tempY : tempY < 0 ? -1 : 1;
}


RouteVector::RouteVector() : x(0), y(0) {}

RouteVector::RouteVector(int x, int y) : x(x), y(y){}

bool RouteVector::operator==(const RouteVector &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool RouteVector::operator!=(const RouteVector &rhs) const {
    return !(rhs == *this);
}

int RouteVector::getX() const {
    return x;
}

int RouteVector::getY() const {
    return y;
}
