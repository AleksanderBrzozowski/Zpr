//
// Created by Aleksander on 30.10.2016.
//

#ifndef ZPR_MOVABLE_H
#define ZPR_MOVABLE_H


#include "Point.h"
#include "Route.h"

class Movable {
private:
    Point actualPoint;
    const int maxSpeed;
    Route *route;
    RouteVector routeVector;

public:
    Movable(Point actualPoint, const int speed, std::vector<Point *> &route);
    virtual ~Movable();

    bool move();
    const Point &getActualPoint() const;

};


#endif //ZPR_MOVABLE_H
