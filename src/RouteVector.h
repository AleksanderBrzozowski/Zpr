//
// Created by Aleksander on 29.10.2016.
//

#ifndef ZPR_VECTOR_H
#define ZPR_VECTOR_H


#include "Point.h"
#include <stdexcept>


class RouteVector{

private:
    int x,y;
public:
    RouteVector(const Point& begin, const Point& end);

    bool operator==(const RouteVector &rhs) const;

    bool operator!=(const RouteVector &rhs) const;
};


#endif //ZPR_VECTOR_H
