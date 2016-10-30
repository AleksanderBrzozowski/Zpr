//
// Created by Aleksander on 29.10.2016.
//

#ifndef ZPR_ROUTE_H
#define ZPR_ROUTE_H


#include <vector>
#include "Point.h"
#include "RouteVector.h"
#include <stdexcept>
#include <cstdlib>

class Route {

private:
    std::vector<Point*>& points;

public:
    Route(std::vector<Point*> &points);
    RouteVector getVector(const Point &point) const;
    int getDistance(const Point &point) const;
    bool isEnd() const;
    void nextPoint();

    void checkIsAnyPointToGo() const;
};


#endif //ZPR_ROUTE_H
