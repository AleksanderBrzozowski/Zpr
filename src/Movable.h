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
    const unsigned int id;
    Route *route;
    RouteVector routeVector;

public:
    Movable(Point actualPoint, const int speed, std::vector<Point *> &route, const unsigned int id);
    virtual ~Movable();

    bool move();
    const Point &getActualPoint() const;
    const unsigned int getId() const;
};


#endif //ZPR_MOVABLE_H
