//
// Created by Aleksander on 12.12.2016.
//

#ifndef ZPR_ROUTE2_H
#define ZPR_ROUTE2_H


#include "RouteVector.h"
#include "Point.h"

class Route2 {
public:
    RouteVector getRouteVector(const Point& point) const;
    int getDistance(const Point& point) const;
    virtual bool nextPoint() = 0;
    virtual bool isLastPoint(const Point &point) = 0;
private:
    virtual const Point &getActualPoint() const = 0;
};


#endif //ZPR_ROUTE2_H
